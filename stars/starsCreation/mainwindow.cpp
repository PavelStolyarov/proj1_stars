// mainwindow.cpp
#include "mainwindow.h"
#include "star.h"
#include "math.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QMouseEvent>
#include <QToolTip>

// Константы для области симуляции
const int topX0 = 50;   // Отступ слева
const int topY0 = 50;   // Отступ сверху
const int h = 920;      // Высота области симуляции
const int length = 920; // Ширина области симуляции (квадрат)

galaxy *galactika = new galaxy;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ДОПОЛНИТЕЛЬНОЕ ЗАДАНИЕ: Включаем отслеживание мыши
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);

    // Подключаем кнопки и сигналы
    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::buttonText);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));

    // ЗАДАНИЕ 3: Изменение расстояния слияния
    connect(ui->pushButton_updateDist, &QPushButton::clicked, this, &MainWindow::updateMergeDistance);

    // Управление шагом времени
    connect(ui->pushButton_updateDt, &QPushButton::clicked, this, &MainWindow::updateTimestep);
    connect(ui->pushButton_dtX2, &QPushButton::clicked, this, &MainWindow::multiplyTimestep);
    connect(ui->pushButton_dtDiv2, &QPushButton::clicked, this, &MainWindow::divideTimestep);

    // Управление объектами
    connect(ui->pushButton_addObject, &QPushButton::clicked, this, &MainWindow::addObject);
    connect(ui->pushButton_removeObject, &QPushButton::clicked, this, &MainWindow::removeObject);

    // ОПТИМИЗАЦИЯ: Управление производительностью
    connect(ui->pushButton_updateSteps, &QPushButton::clicked, this, &MainWindow::updateStepsPerFrame);
    connect(ui->pushButton_updateCutoff, &QPushButton::clicked, this, &MainWindow::updateCutoffDistance);
    connect(ui->checkBox_useGrid, &QCheckBox::toggled, this, &MainWindow::toggleGrid);

    // ЗАДАНИЕ 7: Файловые операции
    connect(ui->pushButton_save, &QPushButton::clicked, this, &MainWindow::saveState);
    connect(ui->pushButton_load, &QPushButton::clicked, this, &MainWindow::loadState);

    // ЗАДАНИЕ 8: Тесты
    connect(ui->pushButton_test1, &QPushButton::clicked, this, &MainWindow::runTest1);
    connect(ui->pushButton_test2, &QPushButton::clicked, this, &MainWindow::runTest2);
    connect(ui->pushButton_test3, &QPushButton::clicked, this, &MainWindow::runTest3);
    connect(ui->pushButton_createCustom, &QPushButton::clicked, this, &MainWindow::createCustomSystem);

    timer->start(1);

    // Инициализация начальных значений
    initialObjectCount = galactika->num;
    ui->lineEdit_initialObjects->setText(QString::number(initialObjectCount));
    ui->lineEdit_dt->setText(QString::number(galactika->currentDt, 'f', 0));
    ui->label_currentDt->setText(
        QString("Текущий dt: %1 с × %2 шагов = %3 с/кадр")
            .arg(galactika->currentDt, 0, 'f', 0)
            .arg(galactika->stepsPerFrame)
            .arg(galactika->currentDt * galactika->stepsPerFrame, 0, 'f', 0)
        );

    // ОПТИМИЗАЦИЯ: Инициализация параметров производительности
    ui->lineEdit_stepsPerFrame->setText(QString::number(galactika->stepsPerFrame));
    ui->lineEdit_cutoffDistance->setText(QString::number(galactika->cutoffDistance, 'e', 1));
    ui->checkBox_useGrid->setChecked(galactika->useGrid);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete galactika;
}

// ДОПОЛНИТЕЛЬНОЕ ЗАДАНИЕ: Отслеживание движения мыши
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    lastMousePos = event->pos();

    // Ищем объект под курсором
    int objectIndex = findObjectUnderCursor(lastMousePos);

    if(objectIndex != -1 && objectIndex != hoveredObjectIndex) {
        // Нашли новый объект под курсором
        hoveredObjectIndex = objectIndex;

        // Получаем информацию о планете
        star* obj = galactika->stars[objectIndex];
        if(obj) {
            // Форматируем информацию
            QString info = QString(
                               "<b>Объект #%1</b><br>"
                               "━━━━━━━━━━━━━━━━━━<br>"
                               "<b>Масса:</b> %2 M⊕ (%3 кг)<br>"
                               "<b>Координаты:</b><br>"
                               "  • X: %4 м<br>"
                               "  • Y: %5 м<br>"
                               "<b>Скорость:</b> %6 м/с<br>"
                               "<b>Физ. радиус:</b> %7 км<br>"
                               "<b>Размер:</b> %8 px"
                               )
                               .arg(objectIndex)
                               .arg(obj->m / massEarth, 0, 'f', 3)
                               .arg(obj->m, 0, 'e', 2)
                               .arg(obj->x[0], 0, 'e', 2)
                               .arg(obj->x[1], 0, 'e', 2)
                               .arg(sqrt(obj->v[0]*obj->v[0] + obj->v[1]*obj->v[1]), 0, 'e', 2)
                               .arg(obj->physicalRadius / 1000.0, 0, 'f', 0)
                               .arg(obj->radius);

            // Показываем tooltip чуть правее и ниже курсора
            QPoint tooltipPos = event->globalPosition().toPoint() + QPoint(15, 15);
            QToolTip::showText(tooltipPos, info, this);
        }
    } else if(objectIndex == -1 && hoveredObjectIndex != -1) {
        // Курсор ушел с планеты
        hoveredObjectIndex = -1;
        QToolTip::hideText();
    }

    QMainWindow::mouseMoveEvent(event);
}

// ДОПОЛНИТЕЛЬНОЕ ЗАДАНИЕ: Поиск объекта под курсором
int MainWindow::findObjectUnderCursor(const QPoint& cursorPos)
{
    // ОПТИМИЗАЦИЯ: Проверяем только если курсор в области симуляции
    if(cursorPos.x() < topX0 || cursorPos.x() > topX0 + length ||
        cursorPos.y() < topY0 || cursorPos.y() > topY0 + h) {
        return -1;
    }

    // Коэффициент масштабирования (должен совпадать с paintEvent)
    double coefX = length / 2.0 / 2e12;
    int centerX = length / 2;
    int centerY = h / 2;

    // Радиус поиска в пикселях (чтобы было удобно наводить)
    const int searchRadius = 20;
    const int searchRadiusSq = searchRadius * searchRadius;

    int closestObject = -1;
    int minDistSq = searchRadiusSq + 1;

    // Проверяем все объекты
    for(int i = 0; i < galactika->num; ++i) {
        if(!galactika->stars[i]) continue;

        // Переводим физические координаты в экранные (как в paintEvent)
        int screenX = (int)(galactika->stars[i]->x[0] * coefX) + centerX + topX0;
        int screenY = (int)(galactika->stars[i]->x[1] * coefX) + centerY + topY0;

        // Расстояние от курсора до центра планеты
        int dx = cursorPos.x() - screenX;
        int dy = cursorPos.y() - screenY;
        int distSq = dx*dx + dy*dy;

        // Учитываем радиус планеты (чтобы можно было кликнуть на край)
        int objectRadius = galactika->stars[i]->radius;
        int effectiveDistSq = distSq - objectRadius*objectRadius;
        if(effectiveDistSq < 0) effectiveDistSq = 0;

        // Если это ближайший объект в радиусе поиска
        if(effectiveDistSq < minDistSq) {
            minDistSq = effectiveDistSq;
            closestObject = i;
        }
    }

    return closestObject;
}

void MainWindow::buttonText()
{
    if(ui->pushButtonStart->text() == textB[0]) {
        ui->pushButtonStart->setText(textB[1]);
    } else {
        ui->pushButtonStart->setText(textB[0]);
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);

    // Фон для области симуляции
    painter.fillRect(0, 0, 1200, 1020, QColor(20, 20, 40));

    QPen pen(Qt::black, 1, Qt::SolidLine);
    painter.setPen(pen);

    // ЗАДАНИЕ 1: Обновление шага и времени
    if(ui->pushButtonStart->text() == textB[1]) {
        galactika->move();
        stepCount++;
        // ОПТИМИЗАЦИЯ: Учитываем несколько шагов физики за кадр
        systemTime += galactika->currentDt * galactika->stepsPerFrame;
    }

    ui->label_step->setText("Шаг расчета: " + QString::number(stepCount));
    ui->label_time->setText("Время системы: " + QString::number(systemTime, 'e', 2) + " с");

    // Отображаем текущий шаг времени
    ui->label_currentDt->setText(
        QString("Текущий dt: %1 с × %2 шагов = %3 с/кадр")
            .arg(galactika->currentDt, 0, 'f', 0)
            .arg(galactika->stepsPerFrame)
            .arg(galactika->currentDt * galactika->stepsPerFrame, 0, 'f', 0)
        );

    // ЗАДАНИЕ 2: Кинетическая энергия
    double kineticEnergy = galactika->getKineticEnergy();
    ui->label_kineticEnergy->setText(
        QString("Кинетическая энергия: %1 Дж").arg(kineticEnergy, 0, 'e', 3)
        );

    // ЗАДАНИЕ 3: Количество слияний
    ui->label_mergeCount->setText(
        QString("Количество слияний: %1").arg(galactika->mergeCount)
        );

    // ЗАДАНИЕ 5: Топ-3 объектов
    auto top3 = galactika->getTop3MassiveObjects();
    if(top3.size() > 0) {
        ui->label_top1->setText(QString("1️⃣ Масса: %1 кг | Позиция: (%2, %3) м | Скорость: %4 м/с")
                                    .arg(top3[0].mass, 0, 'e', 2)
                                    .arg(top3[0].x, 0, 'e', 2)
                                    .arg(top3[0].y, 0, 'e', 2)
                                    .arg(top3[0].speed, 0, 'e', 2));
    }
    if(top3.size() > 1) {
        ui->label_top2->setText(QString("2️⃣ Масса: %1 кг | Позиция: (%2, %3) м | Скорость: %4 м/с")
                                    .arg(top3[1].mass, 0, 'e', 2)
                                    .arg(top3[1].x, 0, 'e', 2)
                                    .arg(top3[1].y, 0, 'e', 2)
                                    .arg(top3[1].speed, 0, 'e', 2));
    }
    if(top3.size() > 2) {
        ui->label_top3->setText(QString("3️⃣ Масса: %1 кг | Позиция: (%2, %3) м | Скорость: %4 м/с")
                                    .arg(top3[2].mass, 0, 'e', 2)
                                    .arg(top3[2].x, 0, 'e', 2)
                                    .arg(top3[2].y, 0, 'e', 2)
                                    .arg(top3[2].speed, 0, 'e', 2));
    }

    // ЗАДАНИЕ 6: Полная энергия и законы сохранения
    double potentialEnergy = galactika->getPotentialEnergy();
    double totalEnergy = kineticEnergy + potentialEnergy;

    ui->label_totalEnergy->setText(
        QString("Полная энергия: %1 Дж").arg(totalEnergy, 0, 'e', 3)
        );
    ui->label_potentialEnergy->setText(
        QString("Потенциальная энергия: %1 Дж").arg(potentialEnergy, 0, 'e', 3)
        );

    auto momentum = galactika->getTotalMomentum();
    ui->label_momentum->setText(
        QString("Импульс: (%1, %2) кг·м/с")
            .arg(momentum.first, 0, 'e', 2)
            .arg(momentum.second, 0, 'e', 2)
        );

    double angularMomentum = galactika->getAngularMomentum();
    ui->label_angularMomentum->setText(
        QString("Угловой момент: %1 кг·м²/с").arg(angularMomentum, 0, 'e', 3)
        );

    // ЗАДАНИЕ 8: Статистика объектов
    int currentObjects = 0;
    for(int i = 0; i < galactika->num; ++i) {
        if(galactika->stars[i]) currentObjects++;
    }

    int removedObjects = initialObjectCount - currentObjects;
    int createdByMerge = galactika->mergeCount;
    int totalRemoved = removedObjects + createdByMerge;

    ui->label_objectCount->setText(
        QString("Текущее количество объектов: %1").arg(currentObjects)
        );

    ui->label_statistics->setText(
        QString("Начальное: %1 | Удалено при слиянии: %2 | Создано слиянием: %3")
            .arg(initialObjectCount)
            .arg(totalRemoved)
            .arg(createdByMerge)
        );

    // ОТРИСОВКА ОБЪЕКТОВ
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    // Коэффициент масштабирования (увеличен для лучшей видимости)
    double coefX = length / 2.0 / 2e12;
    int centerX = length / 2;
    int centerY = h / 2;

    for(int i = 0; i < galactika->num; ++i) {
        if(galactika->stars[i]) {
            // Переводим физические координаты в экранные
            int screenX = (int)(galactika->stars[i]->x[0] * coefX) + centerX + topX0;
            int screenY = (int)(galactika->stars[i]->x[1] * coefX) + centerY + topY0;

            // Проверка видимости (не рисуем за границами экрана)
            if(screenX < -50 || screenX > 1200 ||
                screenY < -50 || screenY > 1020) {
                continue;
            }

            // Устанавливаем цвет
            brush.setColor(galactika->stars[i]->col);
            painter.setBrush(brush);

            // ДОПОЛНИТЕЛЬНОЕ ЗАДАНИЕ: Подсвечиваем планету под курсором
            if(i == hoveredObjectIndex) {
                // Рисуем желтое кольцо вокруг планеты
                QPen highlightPen(QColor(255, 255, 0), 2, Qt::SolidLine);
                painter.setPen(highlightPen);
                int radius = galactika->stars[i]->radius;
                painter.drawEllipse(screenX - radius - 3, screenY - radius - 3,
                                    (radius + 3) * 2, (radius + 3) * 2);
                painter.setPen(pen);  // Восстанавливаем стандартный pen
            }

            // Рисуем объект (всегда эллипс для лучшей видимости)
            int radius = galactika->stars[i]->radius;
            painter.drawEllipse(screenX - radius, screenY - radius,
                                radius * 2, radius * 2);
        }
    }
}

// ЗАДАНИЕ 3: Изменение расстояния слияния динамически
void MainWindow::updateMergeDistance()
{
    bool ok;
    double newDist = ui->lineEdit_distConnect->text().toDouble(&ok);

    if(ok && newDist >= 0) {  // Допускаем 0 (только физические столкновения)
        galactika->setDistConnect(newDist);  // Уже в метрах

        // Показываем сообщение в статус-баре
        if(newDist == 0) {
            statusBar()->showMessage(
                "Только физические столкновения (при касании объектов)",
                3000
                );
        } else {
            statusBar()->showMessage(
                QString("Доп. расстояние слияния: %1 м").arg(newDist, 0, 'e', 2),
                3000
                );
        }
    } else {
        statusBar()->showMessage("Ошибка: введите неотрицательное число!", 3000);
    }
}

// Изменение шага времени
void MainWindow::updateTimestep()
{
    bool ok;
    double newDt = ui->lineEdit_dt->text().toDouble(&ok);

    if(ok && newDt > 0) {
        galactika->setDt(newDt);
        ui->label_currentDt->setText(QString("Текущий dt: %1 с").arg(newDt, 0, 'f', 0));
        statusBar()->showMessage(
            QString("Шаг времени обновлен: %1 с").arg(newDt, 0, 'f', 0),
            3000
            );
    } else {
        statusBar()->showMessage("Ошибка: введите положительное число!", 3000);
    }
}

// Умножить шаг времени на 2 (ускорить симуляцию)
void MainWindow::multiplyTimestep()
{
    double newDt = galactika->currentDt * 2.0;
    galactika->setDt(newDt);
    ui->lineEdit_dt->setText(QString::number(newDt, 'f', 0));
    ui->label_currentDt->setText(QString("Текущий dt: %1 с").arg(newDt, 0, 'f', 0));
    statusBar()->showMessage(
        QString("Симуляция ускорена dt = %1 с").arg(newDt, 0, 'f', 0),
        2000
        );
}

// Разделить шаг времени на 2 (замедлить симуляцию)
void MainWindow::divideTimestep()
{
    double newDt = galactika->currentDt / 2.0;
    if(newDt < 1) newDt = 1; // Минимальный dt = 1 секунда

    galactika->setDt(newDt);
    ui->lineEdit_dt->setText(QString::number(newDt, 'f', 0));
    ui->label_currentDt->setText(QString("Текущий dt: %1 с").arg(newDt, 0, 'f', 0));
    statusBar()->showMessage(
        QString("Симуляция замедлена dt = %1 с").arg(newDt, 0, 'f', 0),
        2000
        );
}

// Добавление нового объекта
void MainWindow::addObject()
{
    bool ok;
    double massMultiplier = ui->lineEdit_objectMass->text().toDouble(&ok);

    if(!ok || massMultiplier <= 0) {
        statusBar()->showMessage("Ошибка: введите положительную массу", 3000);
        return;
    }

    // Создаем объект в случайной позиции
    double coord[2], vel[2];
    for(int i = 0; i < 2; ++i) {
        coord[i] = galactika->sysRadius * (2.0 * rand() / RAND_MAX - 1.0);
        vel[i] = 100 * (2.0 * rand() / RAND_MAX - 1.0);
    }
    double mass = massEarth * massMultiplier;

    if(galactika->addStar(coord, vel, mass)) {
        statusBar()->showMessage(
            QString("Объект добавлен! Масса: %1 × Земля").arg(massMultiplier, 0, 'f', 2),
            3000
            );
    } else {
        statusBar()->showMessage("Ошибка: нет свободного места для нового объекта", 3000);
    }
}

// Удаление случайного объекта
void MainWindow::removeObject()
{
    if(galactika->removeRandomStar()) {
        statusBar()->showMessage("Случайный объект удален", 2000);
    } else {
        statusBar()->showMessage("Нельзя удалить: остался только центральный объект", 3000);
    }
}

// ОПТИМИЗАЦИЯ: Изменение количества шагов физики за кадр
void MainWindow::updateStepsPerFrame()
{
    bool ok;
    int newSteps = ui->lineEdit_stepsPerFrame->text().toInt(&ok);

    if(ok && newSteps > 0 && newSteps <= 100) {
        galactika->setStepsPerFrame(newSteps);

        // Обновляем отображение dt
        ui->label_currentDt->setText(
            QString("Текущий dt: %1 с × %2 шагов = %3 с/кадр")
                .arg(galactika->currentDt, 0, 'f', 0)
                .arg(galactika->stepsPerFrame)
                .arg(galactika->currentDt * galactika->stepsPerFrame, 0, 'f', 0)
            );

        statusBar()->showMessage(
            QString("✓ Шагов физики за кадр: %1 (визуальное ускорение в %1x!)").arg(newSteps),
            3000
            );
    } else {
        statusBar()->showMessage("Ошибка: введите число от 1 до 100!", 3000);
    }
}

// ОПТИМИЗАЦИЯ: Изменение cutoff расстояния
void MainWindow::updateCutoffDistance()
{
    bool ok;
    double newCutoff = ui->lineEdit_cutoffDistance->text().toDouble(&ok);

    if(ok && newCutoff > 0) {
        galactika->setCutoffDistance(newCutoff);
        statusBar()->showMessage(
            QString("Cutoff расстояние: %1 м (игнорируем далекие объекты!)").arg(newCutoff, 0, 'e', 1),
            3000
            );
    } else {
        statusBar()->showMessage("Ошибка: введите положительное число!", 3000);
    }
}

// ОПТИМИЗАЦИЯ: Включение/выключение пространственной сетки
void MainWindow::toggleGrid(bool enabled)
{
    galactika->setUseGrid(enabled);

    if(enabled) {
        statusBar()->showMessage(
            "Spatial Grid включена! (ускорение 50-100x для больших систем)",
            3000
            );
    } else {
        statusBar()->showMessage(
            "Spatial Grid выключена (только cutoff)",
            3000
            );
    }
}

// ЗАДАНИЕ 7: Сохранение состояния
void MainWindow::saveState()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Сохранить состояние системы", "", "System Files (*.sys)");

    if(fileName.isEmpty()) return;

    std::ofstream file(fileName.toStdString(), std::ios::binary);
    if(!file) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать файл!");
        return;
    }

    // Используем перегруженный оператор <<
    file << *galactika;

    // Сохраняем дополнительную информацию
    file.write(reinterpret_cast<const char*>(&stepCount), sizeof(stepCount));
    file.write(reinterpret_cast<const char*>(&systemTime), sizeof(systemTime));
    file.write(reinterpret_cast<const char*>(&initialObjectCount), sizeof(initialObjectCount));

    file.close();

    QMessageBox::information(this, "Сохранено",
                             QString("Состояние сохранено в:\n%1").arg(fileName));
}

// ЗАДАНИЕ 7: Загрузка состояния
void MainWindow::loadState()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Загрузить состояние системы", "", "System Files (*.sys)");

    if(fileName.isEmpty()) return;

    std::ifstream file(fileName.toStdString(), std::ios::binary);
    if(!file) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл!");
        return;
    }

    // Используем перегруженный оператор >>
    file >> *galactika;

    // Загружаем дополнительную информацию
    file.read(reinterpret_cast<char*>(&stepCount), sizeof(stepCount));
    file.read(reinterpret_cast<char*>(&systemTime), sizeof(systemTime));
    file.read(reinterpret_cast<char*>(&initialObjectCount), sizeof(initialObjectCount));

    file.close();

    ui->lineEdit_initialObjects->setText(QString::number(initialObjectCount));
    ui->lineEdit_distConnect->setText(
        QString::number(galactika->getDistConnect() / 1000.0)
        );

    update();

    QMessageBox::information(this, "Загружено",
                             QString("Состояние загружено из:\n%1").arg(fileName));
}

// ЗАДАНИЕ 8: Тест 1 - Солнечная система
void MainWindow::runTest1()
{
    delete galactika;
    galactika = galaxy::createSolarSystem();

    // Устанавливаем меньший шаг времени для стабильности орбит
    galactika->setDt(1000);  // 1000 секунд вместо 10000
    ui->lineEdit_dt->setText("1000");
    ui->label_currentDt->setText("Текущий dt: 1000 с");

    // Увеличиваем расстояние слияния (радиус Солнца ~700,000 км)
    // Устанавливаем 1 млн км чтобы планеты сливались до "гравитационной пращи"
    galactika->setDistConnect(1e9);  // 1 млн км = 1e9 метров

    stepCount = 0;
    systemTime = 0.0;
    initialObjectCount = 8; // Солнце + 6 планет

    ui->lineEdit_initialObjects->setText(QString::number(initialObjectCount));
    ui->lineEdit_distConnect->setText(
        QString::number(galactika->getDistConnect() / 1000.0)
        );

    QMessageBox::information(this, "Тест 1 - Солнечная система",
                             "Создана солнечная система\n\n"
                             "Параметры:\n"
                             "• Солнце в центре (масса = 1.99×10³⁰ кг)\n"
                             "• 6 планет на реалистичных орбитах\n"
                             "• Реальные массы и орбитальные скорости\n"
                             "• dt = 1000 с\n"
                             "• Расстояние слияния = 1 млн км\n\n"
                             "Что наблюдать:\n"
                             "• Стабильные круговые орбиты\n"
                             "• Сохранение энергии\n"
                             "• Сохранение импульса\n"
                             "• Сохранение углового момента\n"
                             "• Если планета подлетит близко к Солнцу - сольется с ним\n\n");

    update();
}

// ЗАДАНИЕ 8: Тест 2 - Столкновение двух солнечных систем
void MainWindow::runTest2()
{
    delete galactika;
    galactika = galaxy::createDualSolarSystem();

    stepCount = 0;
    systemTime = 0.0;
    initialObjectCount = 16; // 2 звезды + 14 планет

    ui->lineEdit_initialObjects->setText(QString::number(initialObjectCount));
    ui->lineEdit_distConnect->setText(
        QString::number(galactika->getDistConnect() / 1000.0)
        );

    QMessageBox::information(this, "Тест 2",
                             "Создана система столкновения!\n\n"
                             "Параметры:\n"
                             "• 2 солнца движутся навстречу\n"
                             "• У каждого по 7 планет\n");

    update();
}

// ЗАДАНИЕ 8: Тест 3 - Большая система (вариант 24)
void MainWindow::runTest3()
{
    int variant = 24;
    int totalObjects = 10000;

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Предупреждение",
                                                              QString("ОПТИМИЗИРОВАННАЯ СИМУЛЯЦИЯ\n\n"
                                                                      "Параметры:\n"
                                                                      "• Объектов: %1\n")
                                                                  .arg(totalObjects)
                                                                  .arg((long long)totalObjects * totalObjects / 1000000)
                                                                  .arg((long long)totalObjects * totalObjects / 10000000), // ~10% пар из-за cutoff
                                                              QMessageBox::Yes | QMessageBox::No
                                                              );

    if(reply == QMessageBox::No) return;

    statusBar()->showMessage("Создание оптимизированной системы...", 0);
    QApplication::processEvents();

    delete galactika;
    galactika = galaxy::createLargeSystem(variant, 0);  // distConnect = 0 (только физические)

    // ОПТИМИЗАЦИЯ: Устанавливаем оптимальные параметры для 10000 объектов
    galactika->setStepsPerFrame(10);           // 10 шагов физики за кадр
    galactika->setCutoffDistance(1e11);        // Cutoff = 300 млн км
    galactika->setDt(5000);                    // dt = 5000 секунд

    stepCount = 0;
    systemTime = 0.0;
    initialObjectCount = totalObjects;

    // Обновляем UI
    ui->lineEdit_initialObjects->setText(QString::number(initialObjectCount));
    ui->lineEdit_distConnect->setText(QString::number(galactika->getDistConnect(), 'e', 2));
    ui->lineEdit_dt->setText(QString::number(galactika->currentDt, 'f', 0));
    ui->lineEdit_stepsPerFrame->setText(QString::number(galactika->stepsPerFrame));
    ui->lineEdit_cutoffDistance->setText(QString::number(galactika->cutoffDistance, 'e', 1));

    ui->label_currentDt->setText(
        QString("Текущий dt: %1 с × %2 шагов = %3 с/кадр")
            .arg(galactika->currentDt, 0, 'f', 0)
            .arg(galactika->stepsPerFrame)
            .arg(galactika->currentDt * galactika->stepsPerFrame, 0, 'f', 0)
        );

    statusBar()->showMessage(
        QString("Тест 3: система из %1 объектов готова").arg(totalObjects),
        10000
        );

    QMessageBox::information(this, "Тест 3",
                             QString("Большая система создана\n\n"
                                     "Параметры:\n"
                                     "• Объектов: %1\n"
                                     "• Область: 3×10¹² м\n"
                                     "• Солнце в центре\n\n"
                                     "Оптимизации:\n"
                                     "• Spatial Grid: 30×30 ячеек\n"
                                     "• Шагов физики/кадр: 10\n"
                                     "• Cutoff: 100 млн км\n"
                                     "• dt: 5000 с\n"
                                     "• Кэш энергии: раз в 10 кадров\n\n")
                                 .arg(totalObjects));

    update();
}

// НОВОЕ: Создание системы с произвольным количеством объектов
void MainWindow::createCustomSystem()
{
    bool ok;
    int numObjects = ui->lineEdit_customObjects->text().toInt(&ok);

    if(!ok || numObjects < 1 || numObjects > 50000) {
        QMessageBox::warning(this, "Ошибка",
                             "Введите корректное количество объектов (от 1 до 50000)!");
        return;
    }

    QString message = QString(
                          "СОЗДАНИЕ СВОЕЙ СИСТЕМЫ\n\n"
                          "Параметры:\n"
                          "• Объектов: %1\n"
                          "• 1 центральное солнце + %2 планет\n"
                          "• Орбиты: 300-1200 млн км\n"
                          ).arg(numObjects).arg(numObjects - 1);


    message += "\n\n"
               "Создать систему?";

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Создание системы", message,
                                                              QMessageBox::Yes | QMessageBox::No
                                                              );

    if(reply == QMessageBox::No) return;

    statusBar()->showMessage(
        QString("Создание системы из %1 объектов...").arg(numObjects), 0
        );
    QApplication::processEvents();

    delete galactika;
    galactika = galaxy::createCustomSystem(numObjects, 1e9);

    // Автоматические настройки в зависимости от количества
    if(numObjects <= 100) {
        galactika->setStepsPerFrame(1);
        galactika->setCutoffDistance(3e12);
    } else if(numObjects <= 1000) {
        galactika->setStepsPerFrame(5);
        galactika->setCutoffDistance(3e12);
    } else if(numObjects <= 10000) {
        galactika->setStepsPerFrame(10);
        galactika->setCutoffDistance(3e12);
    } else {
        galactika->setStepsPerFrame(20);
        galactika->setCutoffDistance(3e12);
    }

    stepCount = 0;
    systemTime = 0.0;
    initialObjectCount = numObjects;

    // Обновляем UI
    ui->lineEdit_initialObjects->setText(QString::number(initialObjectCount));
    ui->lineEdit_distConnect->setText(QString::number(galactika->getDistConnect(), 'e', 2));
    ui->lineEdit_dt->setText(QString::number(galactika->currentDt, 'f', 0));
    ui->lineEdit_stepsPerFrame->setText(QString::number(galactika->stepsPerFrame));
    ui->lineEdit_cutoffDistance->setText(QString::number(galactika->cutoffDistance, 'e', 1));

    ui->label_currentDt->setText(
        QString("Текущий dt: %1 с × %2 шагов = %3 с/кадр")
            .arg(galactika->currentDt, 0, 'f', 0)
            .arg(galactika->stepsPerFrame)
            .arg(galactika->currentDt * galactika->stepsPerFrame, 0, 'f', 0)
        );

    statusBar()->showMessage(
        QString("Создана система из %1 объектов!").arg(numObjects),
        5000
        );

    QMessageBox::information(this, "Система создана!",
                             QString("Ваша система из %1 объектов готова!\n\n"
                                     "Центральное солнце + %2 планет\n"
                                     "Все планеты на стабильных орбитах!\n\n"
                                     "🖱️ Наведите мышь на любую планету для просмотра информации:\n"
                                     "   • Масса (в массах Земли)\n"
                                     "   • Координаты X, Y\n"
                                     "   • Скорость\n"
                                     "   • Физический радиус\n"
                                     "   • Размер на экране\n\n"
                                     "Нажмите 'Start' для запуска симуляции!")
                                 .arg(numObjects)
                                 .arg(numObjects - 1));

    update();
}
