// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QToolTip>
#include <fstream>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool ellipse = false;
    const QString textB[2] = {"Start", "Stop"};
    QTimer *timer = new QTimer(this);
    // ЗАДАНИЕ 1: Счетчики шага и времени
    int stepCount = 0;
    double systemTime = 0.0;
    // ЗАДАНИЕ 8: Начальное количество объектов для статистики
    int initialObjectCount;

    // ДОПОЛНИТЕЛЬНОЕ ЗАДАНИЕ: Tooltip при наведении на планету
    QPoint lastMousePos;  // Последняя позиция курсора
    int hoveredObjectIndex = -1;  // Индекс объекта под курсором (-1 если нет)

protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void buttonText();
    void paintEvent(QPaintEvent *e);
    // ЗАДАНИЕ 3: Изменение расстояния слияния
    void updateMergeDistance();
    // Управление шагом времени
    void updateTimestep();
    void multiplyTimestep();
    void divideTimestep();
    // Управление объектами
    void addObject();
    void removeObject();
    // ОПТИМИЗАЦИЯ: Управление производительностью
    void updateStepsPerFrame();
    void updateCutoffDistance();
    void toggleGrid(bool enabled);
    // ЗАДАНИЕ 7: Файловые операции
    void saveState();
    void loadState();
    // ЗАДАНИЕ 8: Тесты
    void runTest1();
    void runTest2();
    void runTest3();
    // НОВОЕ: Создание своей системы
    void createCustomSystem();
private:
    Ui::MainWindow *ui;

    // ДОПОЛНИТЕЛЬНОЕ ЗАДАНИЕ: Поиск планеты под курсором
    int findObjectUnderCursor(const QPoint& cursorPos);
};
#endif // MAINWINDOW_H
