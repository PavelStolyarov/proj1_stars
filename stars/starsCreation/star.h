// star.h
#include "cmath"
#include <QPainter>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

// ОПТИМИЗАЦИЯ: OpenMP для многопоточности
#ifdef _OPENMP
#include <omp.h>
#endif

#ifndef STAR_H
#define STAR_H

const int dim = 2;
const int numStars = 300;
const int borderMassC = 10;
const double G = 6.67408e-11, dt = 1000;  // ИСПРАВЛЕНО: 1000 сек (16.6 мин) вместо 10000
const double systemRadius = 1e12;

// ============================================
// ОПТИМИЗАЦИЯ: SPATIAL GRID
// ============================================

// Массы небесных тел (кг)
const double massSun     = 1.98892e30;
const double massMercury = 3.3011e23;
const double massVenus   = 4.8675e24;
const double massEarth   = 5.9742e24;
const double massMars    = 6.4171e23;
const double massJupiter = 1.8986e27;
const double massSaturn  = 5.6834e26;

// Радиусы орбит (м)
const double orbitMercury = 5.79e10;
const double orbitVenus   = 1.082e11;
const double orbitEarth   = 1.496e11;
const double orbitMars    = 2.279e11;
const double orbitJupiter = 7.786e11;
const double orbitSaturn  = 1.433e12;

// Для совместимости
const double massJup  = massJupiter;
const double massUran = 86.832e24;

const double borderMass[] = {borderMassC*massEarth, borderMassC*massUran, borderMassC*massJup, borderMassC*massSun};
const QColor colStar[] = {Qt::cyan, Qt::darkGreen, Qt::magenta, Qt::yellow, Qt::white};
const int nColor = sizeof(colStar) / sizeof(colStar[0]);

// ОПТИМИЗАЦИЯ: Пространственная сетка для быстрого поиска соседей

// Forward declaration класса star
class star;

// ЗАДАНИЕ 5: Структура для топ-3 объектов
struct ObjectInfo {
    double mass;
    double x, y;
    double speed;
};

// ОПТИМИЗАЦИЯ: Пространственная сетка для ускорения N-body симуляции
class SpatialGrid {
public:
    static const int MAX_GRID_SIZE = 100;  // Максимальный размер сетки
    std::vector<int> cells[MAX_GRID_SIZE][MAX_GRID_SIZE];  // Списки объектов в ячейках

    double cellSize;        // Размер одной ячейки
    double sysRad;          // Радиус системы (НЕ конфликтует с глобальной константой!)
    int gridSizeX;          // Количество ячеек по X
    int gridSizeY;          // Количество ячеек по Y

    SpatialGrid() : cellSize(0), sysRad(0), gridSizeX(0), gridSizeY(0) {}

    // Построение сетки из массива объектов
    void build(star** stars, int num, double sysRadius, double cutoff);

    // Очистка сетки
    void clear();

    // Получить список объектов в 9 соседних ячейках (3×3 вокруг объекта i)
    void getNeighbors(int objectIndex, star** stars, std::vector<int>& neighbors) const;

    // Получить индексы ячейки для координат
    inline void getCellIndices(double x, double y, int& cellX, int& cellY) const {
        cellX = (int)((x + sysRad) / cellSize);
        cellY = (int)((y + sysRad) / cellSize);

        // Защита от выхода за границы
        if(cellX < 0) cellX = 0;
        if(cellY < 0) cellY = 0;
        if(cellX >= gridSizeX) cellX = gridSizeX - 1;
        if(cellY >= gridSizeY) cellY = gridSizeY - 1;
    }
};

class star {
public:
    static int starCounter;
    double x[dim];
    double v[dim];
    double m;
    double f[dim];
    QColor col;
    int radius;           // Визуальный радиус для отрисовки (пиксели)
    double physicalRadius; // Физический радиус (метры)

    star(double *coord, double *speed, double mass);
    ~star() { starCounter--; }

    // ЗАДАНИЕ 4: Изменение цвета по градации
    void updateColor();

    // ЗАДАНИЕ 4: Изменение размера по градации (10 ступеней)
    void updateSize();

    // Обновление физического радиуса на основе массы
    void updatePhysicalRadius();

    // ЗАДАНИЕ 3: Перегрузка оператора + для слияния
    star operator+(const star& other) const;
};

int star::starCounter = 0;

star::star(double *coord, double *speed, double mass) {
    for(int i = 0; i < dim; ++i) {
        x[i] = coord[i];
        v[i] = speed[i];
        f[i] = 0;
    }
    m = mass;
    starCounter++;

    updateColor();
    updateSize();
    updatePhysicalRadius();
}

// ЗАДАНИЕ 4: Изменение цвета по градации (10 цветов)
void star::updateColor() {
    const QColor colorGradations[10] = {
        QColor(0, 0, 255),      // Синий (маленькие)
        QColor(0, 85, 255),
        QColor(0, 170, 255),
        QColor(0, 255, 255),    // Голубой
        QColor(85, 255, 170),
        QColor(170, 255, 85),
        QColor(255, 255, 0),    // Желтый
        QColor(255, 170, 0),
        QColor(255, 85, 0),
        QColor(255, 0, 0)       // Красный (большие)
    };

    double logMass = log10(m);
    double minLogMass = log10(massEarth * 0.001);
    double maxLogMass = log10(massSun * 0.5);
    double normalized = (logMass - minLogMass) / (maxLogMass - minLogMass);
    normalized = qMax(0.0, qMin(1.0, normalized));

    int index = static_cast<int>(normalized * 9.999);
    col = colorGradations[index];
}

// ЗАДАНИЕ 4: Изменение размера по градации (10 ступеней)
// ОПТИМАЛЬНЫЕ РАЗМЕРЫ: от 2 до 12 пикселей
void star::updateSize() {
    const int minSize = 2;   // Минимум 2 пикселя
    const int maxSize = 12;  // Максимум 12 пикселей
    const int numGradations = 10;

    double logMass = log10(m);
    double minLogMass = log10(massEarth * 0.001);
    double maxLogMass = log10(massSun * 0.5);
    double normalized = (logMass - minLogMass) / (maxLogMass - minLogMass);
    normalized = qMax(0.0, qMin(1.0, normalized));

    // Линейная интерполяция между minSize и maxSize
    radius = minSize + (int)(normalized * (maxSize - minSize));
}

// Обновление физического радиуса на основе массы
// Формула: R = R_earth * (M / M_earth)^(1/3)
// Предполагаем одинаковую плотность, радиус ~ масса^(1/3)
void star::updatePhysicalRadius() {
    const double earthRadius = 6.371e6;  // Радиус Земли в метрах
    const double sunRadius = 6.96e8;     // Радиус Солнца в метрах

    // Для малых объектов (< Юпитера) используем формулу плотности Земли
    if(m < massJupiter) {
        physicalRadius = earthRadius * pow(m / massEarth, 1.0/3.0);
    }
    // Для больших объектов (> Юпитера) используем формулу плотности Солнца
    else {
        physicalRadius = sunRadius * pow(m / massSun, 1.0/3.0);
    }

    // Минимальный радиус - 50000 км (чтобы планеты не "проскакивали" друг друга)
    if(physicalRadius < 5e7) physicalRadius = 5e7;
}

// ЗАДАНИЕ 3: Перегрузка оператора + для слияния объектов
star star::operator+(const star& other) const {
    // Законы сохранения массы и импульса
    double newMass = this->m + other.m;

    // Новая скорость (сохранение импульса)
    double newVel[dim];
    for(int k = 0; k < dim; ++k) {
        newVel[k] = (this->m * this->v[k] + other.m * other.v[k]) / newMass;
    }

    // Новая позиция (центр масс)
    double newCoord[dim];
    for(int k = 0; k < dim; ++k) {
        newCoord[k] = (this->m * this->x[k] + other.m * other.x[k]) / newMass;
    }

    // Создаем новый объект
    return star(newCoord, newVel, newMass);
}

class galaxy {
public:
    star **stars;
    int num;
    double sysRadius;
    double distConnect;
    int mergeCount; // ЗАДАНИЕ 3: Счетчик слияний
    double currentDt; // Текущий шаг времени (можно менять динамически)

    // ОПТИМИЗАЦИЯ: Параметры производительности
    int stepsPerFrame;           // Шагов физики на 1 кадр отрисовки (default: 5)
    double cutoffDistance;       // Расстояние отсечки для гравитации (default: 1e11 м = 100 млн км)
    double cutoffDistanceSquared; // Квадрат расстояния (для быстрого сравнения)

    // Пространственная сетка для оптимизации
    SpatialGrid grid;
    bool useGrid;                // Использовать ли сетку (true для всех систем)

    // Кэш для дорогих вычислений
    mutable double cachedPotentialEnergy;
    mutable int energyCacheFrame;
    int currentFrame;

    galaxy(int n = numStars, double distConn = 1e9, double sysRad = systemRadius);
    ~galaxy();

    void move();

    // ЗАДАНИЕ 2: Кинетическая энергия
    double getKineticEnergy() const;

    // ЗАДАНИЕ 3: Геттер и сеттер для расстояния слияния
    double getDistConnect() const { return distConnect; }
    void setDistConnect(double newDist) { distConnect = newDist; }

    // Изменение шага времени динамически
    double getDt() const { return currentDt; }
    void setDt(double newDt) { if(newDt > 0) currentDt = newDt; }

    // ОПТИМИЗАЦИЯ: Геттеры и сеттеры для параметров производительности
    int getStepsPerFrame() const { return stepsPerFrame; }
    void setStepsPerFrame(int steps) { if(steps > 0 && steps <= 100) stepsPerFrame = steps; }

    double getCutoffDistance() const { return cutoffDistance; }
    void setCutoffDistance(double dist) {
        if(dist > 0) {
            cutoffDistance = dist;
            cutoffDistanceSquared = dist * dist;
        }
    }

    // ОПТИМИЗАЦИЯ: Управление сеткой
    bool isUsingGrid() const { return useGrid; }
    void setUseGrid(bool use) { useGrid = use; }

    // Добавление нового объекта
    bool addStar(double* coord, double* vel, double mass);

    // Удаление случайного объекта
    bool removeRandomStar();

    // ЗАДАНИЕ 5: Топ-3 самых массивных объектов
    std::vector<ObjectInfo> getTop3MassiveObjects() const;

    // ЗАДАНИЕ 6: Полная энергия и законы сохранения
    double getPotentialEnergy() const;
    std::pair<double, double> getTotalMomentum() const;
    double getAngularMomentum() const;

    // ЗАДАНИЕ 7: Перегрузка операторов << и >> для файлов
    friend std::ofstream& operator<<(std::ofstream& out, const galaxy& g);
    friend std::ifstream& operator>>(std::ifstream& in, galaxy& g);

    // ЗАДАНИЕ 8: Создание тестовых систем
    static galaxy* createSolarSystem(double distConn = 1e9);
    static galaxy* createDualSolarSystem(double distConn = 1e9);
    static galaxy* createLargeSystem(int variant, double distConn = 1e9);

    // НОВОЕ: Создание системы с произвольным количеством объектов
    static galaxy* createCustomSystem(int numObjects, double distConn = 1e9);
};

// ==================== SPATIAL GRID IMPLEMENTATION ====================

// Построение сетки
void SpatialGrid::build(star** stars, int num, double sysRadius, double cutoff) {
    sysRad = sysRadius;  // Присваиваем аргумент полю класса

    // ОПТИМИЗАЦИЯ: Размер ячейки = cutoff расстояние
    // Это гарантирует что все объекты в соседних ячейках в пределах cutoff!
    cellSize = cutoff;

    // Защита от деления на ноль
    if(cellSize < 1e6) cellSize = 1e6;  // Минимум 1000 км

    // Вычисляем размер сетки
    gridSizeX = (int)((2.0 * sysRad) / cellSize) + 1;
    gridSizeY = (int)((2.0 * sysRad) / cellSize) + 1;

    // Ограничиваем размер сетки
    if(gridSizeX > MAX_GRID_SIZE) gridSizeX = MAX_GRID_SIZE;
    if(gridSizeY > MAX_GRID_SIZE) gridSizeY = MAX_GRID_SIZE;
    if(gridSizeX < 1) gridSizeX = 1;
    if(gridSizeY < 1) gridSizeY = 1;

    // Очищаем старые данные
    clear();

    // Раскладываем объекты по ячейкам
    for(int i = 0; i < num; ++i) {
        if(!stars[i]) continue;

        int cellX, cellY;
        getCellIndices(stars[i]->x[0], stars[i]->x[1], cellX, cellY);
        cells[cellX][cellY].push_back(i);
    }
}

// Очистка сетки
void SpatialGrid::clear() {
    for(int x = 0; x < MAX_GRID_SIZE; ++x) {
        for(int y = 0; y < MAX_GRID_SIZE; ++y) {
            cells[x][y].clear();
        }
    }
}

// Получить соседей объекта (9 ячеек: 3×3 вокруг объекта)
void SpatialGrid::getNeighbors(int objectIndex, star** stars, std::vector<int>& neighbors) const {
    neighbors.clear();

    if(!stars[objectIndex]) return;

    // Находим ячейку объекта
    int cellX, cellY;
    getCellIndices(stars[objectIndex]->x[0], stars[objectIndex]->x[1], cellX, cellY);

    // Проверяем 9 соседних ячеек (включая текущую)
    for(int dx = -1; dx <= 1; ++dx) {
        for(int dy = -1; dy <= 1; ++dy) {
            int nx = cellX + dx;
            int ny = cellY + dy;

            // Проверка границ
            if(nx < 0 || nx >= gridSizeX || ny < 0 || ny >= gridSizeY) continue;

            // Добавляем все объекты из ячейки
            for(int idx : cells[nx][ny]) {
                if(idx != objectIndex) {  // Не добавляем сам объект
                    neighbors.push_back(idx);
                }
            }
        }
    }
}

// ==================== GALAXY IMPLEMENTATION ====================

galaxy::galaxy(int n, double distConn, double sysRad)
    : num(n), distConnect(distConn), sysRadius(sysRad), mergeCount(0), currentDt(dt),
    stepsPerFrame(5), cutoffDistance(3e12), cutoffDistanceSquared(9e24),
    useGrid(true),
    cachedPotentialEnergy(0), energyCacheFrame(-1), currentFrame(0)
{
    stars = new star*[num];
    srand(time(NULL));

    // ПЕРВЫЙ ОБЪЕКТ - ЦЕНТРАЛЬНОЕ СОЛНЦЕ
    double sunCoord[dim] = {0, 0};
    double sunVel[dim] = {0, 0};
    stars[0] = new star(sunCoord, sunVel, massSun);

    // ОСТАЛЬНЫЕ ОБЪЕКТЫ - ПЛАНЕТЫ
    for(int i = 1; i < num; ++i) {
        double coord[dim], speed[dim];

        // Случайная позиция
        for(int j = 0; j < dim; ++j) {
            coord[j] = sysRadius * (2.0 * rand() / RAND_MAX - 1.0);
        }


        // ✅ ИСПРАВЛЕНО: Орбитальная скорость для круговой орбиты
        double distance = sqrt(coord[0]*coord[0] + coord[1]*coord[1]);

        // Защита от деления на ноль (если планета слишком близко к центру)
        if(distance < 1e9) distance = 1e11;  // Минимум 100 млн км

        // Орбитальная скорость: v = sqrt(G * M / r)
        double orbitalSpeed = sqrt(G * massSun / distance);

        // Направление скорости: перпендикулярно радиус-вектору (для круговой орбиты)
        // Перпендикуляр к вектору (x, y) это (-y, x)
        speed[0] = -orbitalSpeed * coord[1] / distance;
        speed[1] = orbitalSpeed * coord[0] / distance;

        // Случайная масса (от маленьких планет до больших)
        double mass = massEarth * (0.01 + 0.99 * rand() / RAND_MAX);
        stars[i] = new star(coord, speed, mass);
    }

    // ОПТИМИЗАЦИЯ: Сетка строится автоматически в move()
}

galaxy::~galaxy() {
    for(int i = 0; i < num; ++i) {
        if(stars[i]) delete stars[i];
    }
    delete[] stars;
}

// ============================================
// GALAXY METHODS
// ============================================

void galaxy::move() {
    // ОПТИМИЗАЦИЯ: Несколько шагов физики за один вызов
    for(int step = 0; step < stepsPerFrame; ++step) {

// Обнуляем силы
#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
        for(int i = 0; i < num; ++i) {
            if(stars[i]) {
                stars[i]->f[0] = 0;
                stars[i]->f[1] = 0;
            }
        }

        // ОПТИМИЗАЦИЯ: Строим пространственную сетку
        if(useGrid) {
            grid.build(stars, num, sysRadius, cutoffDistance);
        }

        // ОПТИМИЗАЦИЯ: Предвычисление констант
        const double softeningSquared = 1e13;
        const double cutoffSq = cutoffDistanceSquared;

        // Вычисляем силы и проверяем слияния
        if(useGrid) {
// ============================================
// С СЕТКОЙ: Проверяем только соседей!
// ОПТИМИЗАЦИЯ: Многопоточность с OpenMP
// ============================================

#ifdef _OPENMP
#pragma omp parallel
            {
                std::vector<int> neighbors;  // Локальный для каждого потока

#pragma omp for schedule(dynamic, 10)
                for(int i = 0; i < num - 1; ++i) {
                    if(!stars[i]) continue;

                    const double xi0 = stars[i]->x[0];
                    const double xi1 = stars[i]->x[1];
                    const double mi = stars[i]->m;
                    const double ri = stars[i]->physicalRadius;

                    // ОПТИМИЗАЦИЯ: Получаем только соседей из 9 ячеек (вместо всех 10000!)
                    grid.getNeighbors(i, stars, neighbors);

                    // Перебираем только соседей
                    for(int j : neighbors) {
                        if(i >= j || !stars[j]) continue;

                        // ОПТИМИЗАЦИЯ: Избегаем sqrt()
                        const double dx = stars[j]->x[0] - xi0;
                        const double dy = stars[j]->x[1] - xi1;
                        const double distSquared = dx * dx + dy * dy;

                        // ОПТИМИЗАЦИЯ: Cutoff - дополнительная фильтрация
                        if(distSquared > cutoffSq) continue;

                        // Только здесь считаем sqrt
                        const double dist = sqrt(distSquared);

                        // Проверка физического столкновения
                        const double sumRadii = ri + stars[j]->physicalRadius;
                        if(dist < sumRadii) {
#pragma omp critical
                            {
                                if(stars[i] && stars[j]) {  // Проверяем еще раз (другой поток мог уже слить)
                                    star* merged = new star(*stars[i] + *stars[j]);
                                    delete stars[i];
                                    delete stars[j];
                                    stars[i] = merged;
                                    stars[j] = nullptr;
                                    mergeCount++;
                                }
                            }
                            continue;
                        }

                        // Дополнительное слияние на пользовательском расстоянии
                        if(distConnect > sumRadii && dist < distConnect) {
#pragma omp critical
                            {
                                if(stars[i] && stars[j]) {  // Проверяем еще раз
                                    star* merged = new star(*stars[i] + *stars[j]);
                                    delete stars[i];
                                    delete stars[j];
                                    stars[i] = merged;
                                    stars[j] = nullptr;
                                    mergeCount++;
                                }
                            }
                            continue;
                        }

                        // ОПТИМИЗАЦИЯ: Inline вычисление силы
                        const double mj = stars[j]->m;
                        const double distCubed = (distSquared + softeningSquared) * sqrt(distSquared + softeningSquared);
                        const double forceMagnitude = G * mi * mj / distCubed;

                        const double fx = forceMagnitude * dx;
                        const double fy = forceMagnitude * dy;

// КРИТИЧЕСКАЯ СЕКЦИЯ: запись в силы (защита от гонок)
#pragma omp atomic
                        stars[i]->f[0] += fx;
#pragma omp atomic
                        stars[i]->f[1] += fy;
#pragma omp atomic
                        stars[j]->f[0] -= fx;
#pragma omp atomic
                        stars[j]->f[1] -= fy;
                    }
                }
            }
#else
            // БЕЗ OPENMP: Однопоточная версия
            std::vector<int> neighbors;

            for(int i = 0; i < num - 1; ++i) {
                if(!stars[i]) continue;

                const double xi0 = stars[i]->x[0];
                const double xi1 = stars[i]->x[1];
                const double mi = stars[i]->m;
                const double ri = stars[i]->physicalRadius;

                // ОПТИМИЗАЦИЯ: Получаем только соседей из 9 ячеек (вместо всех 10000!)
                grid.getNeighbors(i, stars, neighbors);

                // Перебираем только соседей
                for(int j : neighbors) {
                    if(i >= j || !stars[j]) continue;

                    // ОПТИМИЗАЦИЯ: Избегаем sqrt()
                    const double dx = stars[j]->x[0] - xi0;
                    const double dy = stars[j]->x[1] - xi1;
                    const double distSquared = dx * dx + dy * dy;

                    // ОПТИМИЗАЦИЯ: Cutoff - дополнительная фильтрация
                    if(distSquared > cutoffSq) continue;

                    // Только здесь считаем sqrt
                    const double dist = sqrt(distSquared);

                    // Проверка физического столкновения
                    const double sumRadii = ri + stars[j]->physicalRadius;
                    if(dist < sumRadii) {
                        star* merged = new star(*stars[i] + *stars[j]);
                        delete stars[i];
                        delete stars[j];
                        stars[i] = merged;
                        stars[j] = nullptr;
                        mergeCount++;
                        continue;
                    }

                    // Дополнительное слияние на пользовательском расстоянии
                    if(distConnect > sumRadii && dist < distConnect) {
                        star* merged = new star(*stars[i] + *stars[j]);
                        delete stars[i];
                        delete stars[j];
                        stars[i] = merged;
                        stars[j] = nullptr;
                        mergeCount++;
                        continue;
                    }

                    // ОПТИМИЗАЦИЯ: Inline вычисление силы
                    const double mj = stars[j]->m;
                    const double distCubed = (distSquared + softeningSquared) * sqrt(distSquared + softeningSquared);
                    const double forceMagnitude = G * mi * mj / distCubed;

                    const double fx = forceMagnitude * dx;
                    const double fy = forceMagnitude * dy;

                    stars[i]->f[0] += fx;
                    stars[i]->f[1] += fy;
                    stars[j]->f[0] -= fx;
                    stars[j]->f[1] -= fy;
                }
            }
#endif
        } else {
            // ============================================
            // БЕЗ СЕТКИ: Старый алгоритм (для малых систем)
            // ============================================
            for(int i = 0; i < num - 1; ++i) {
                if(!stars[i]) continue;

                const double xi0 = stars[i]->x[0];
                const double xi1 = stars[i]->x[1];
                const double mi = stars[i]->m;
                const double ri = stars[i]->physicalRadius;

                for(int j = i + 1; j < num; ++j) {
                    if(!stars[j]) continue;

                    const double dx = stars[j]->x[0] - xi0;
                    const double dy = stars[j]->x[1] - xi1;
                    const double distSquared = dx * dx + dy * dy;

                    if(distSquared > cutoffSq) continue;

                    const double dist = sqrt(distSquared);

                    const double sumRadii = ri + stars[j]->physicalRadius;
                    if(dist < sumRadii) {
                        star* merged = new star(*stars[i] + *stars[j]);
                        delete stars[i];
                        delete stars[j];
                        stars[i] = merged;
                        stars[j] = nullptr;
                        mergeCount++;
                        continue;
                    }

                    if(distConnect > sumRadii && dist < distConnect) {
                        star* merged = new star(*stars[i] + *stars[j]);
                        delete stars[i];
                        delete stars[j];
                        stars[i] = merged;
                        stars[j] = nullptr;
                        mergeCount++;
                        continue;
                    }

                    const double mj = stars[j]->m;
                    const double distCubed = (distSquared + softeningSquared) * sqrt(distSquared + softeningSquared);
                    const double forceMagnitude = G * mi * mj / distCubed;

                    const double fx = forceMagnitude * dx;
                    const double fy = forceMagnitude * dy;

                    stars[i]->f[0] += fx;
                    stars[i]->f[1] += fy;
                    stars[j]->f[0] -= fx;
                    stars[j]->f[1] -= fy;
                }
            }
        }

        // ОПТИМИЗАЦИЯ: Обновляем позиции и скорости (inline)
        // МНОГОПОТОЧНОСТЬ: Каждый объект обновляется независимо - нет гонок!
        const double dt_local = currentDt;

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
        for(int i = 0; i < num; ++i) {
            if(stars[i]) {
                const double inv_mass = 1.0 / stars[i]->m;
                stars[i]->v[0] += dt_local * stars[i]->f[0] * inv_mass;
                stars[i]->v[1] += dt_local * stars[i]->f[1] * inv_mass;
                stars[i]->x[0] += dt_local * stars[i]->v[0];
                stars[i]->x[1] += dt_local * stars[i]->v[1];
            }
        }
    }

    // Увеличиваем счетчик кадров для кэша
    currentFrame++;
}

// ЗАДАНИЕ 2: Кинетическая энергия
double galaxy::getKineticEnergy() const {
    double totalKE = 0.0;
    for(int i = 0; i < num; ++i) {
        if(stars[i]) {
            double v2 = 0;
            for(int k = 0; k < dim; ++k) {
                v2 += stars[i]->v[k] * stars[i]->v[k];
            }
            totalKE += 0.5 * stars[i]->m * v2;
        }
    }
    return totalKE;
}

// ЗАДАНИЕ 5: Топ-3 самых массивных объектов
std::vector<ObjectInfo> galaxy::getTop3MassiveObjects() const {
    std::vector<ObjectInfo> objects;

    for(int i = 0; i < num; ++i) {
        if(stars[i]) {
            ObjectInfo info;
            info.mass = stars[i]->m;
            info.x = stars[i]->x[0];
            info.y = stars[i]->x[1];
            info.speed = sqrt(stars[i]->v[0] * stars[i]->v[0] +
                              stars[i]->v[1] * stars[i]->v[1]);
            objects.push_back(info);
        }
    }

    std::sort(objects.begin(), objects.end(),
              [](const ObjectInfo& a, const ObjectInfo& b) {
                  return a.mass > b.mass;
              });

    if(objects.size() > 3) objects.resize(3);
    return objects;
}

// ЗАДАНИЕ 6: Потенциальная энергия
double galaxy::getPotentialEnergy() const {
    // ОПТИМИЗАЦИЯ: Кэширование - считаем только раз в 10 кадров!
    const int cacheInterval = 10;

    // Если кэш свежий - возвращаем кэшированное значение
    if(currentFrame - energyCacheFrame < cacheInterval) {
        return cachedPotentialEnergy;
    }

    // ОПТИМИЗАЦИЯ: Используем cutoff и для потенциальной энергии
    const double cutoffSq = cutoffDistanceSquared;
    double U = 0;

    for(int i = 0; i < num - 1; ++i) {
        if(!stars[i]) continue;

        const double xi0 = stars[i]->x[0];
        const double xi1 = stars[i]->x[1];
        const double mi = stars[i]->m;

        for(int j = i + 1; j < num; ++j) {
            if(!stars[j]) continue;

            // ОПТИМИЗАЦИЯ: Избегаем sqrt() и используем cutoff
            const double dx = stars[j]->x[0] - xi0;
            const double dy = stars[j]->x[1] - xi1;
            const double distSquared = dx * dx + dy * dy;

            // ОПТИМИЗАЦИЯ: Пропускаем далекие объекты
            if(distSquared > cutoffSq) continue;
            if(distSquared < 1e10) continue; // Избегаем деления на очень малые числа

            // Только здесь считаем sqrt
            const double dist = sqrt(distSquared);
            U -= G * mi * stars[j]->m / dist;
        }
    }

    // Сохраняем в кэш
    cachedPotentialEnergy = U;
    energyCacheFrame = currentFrame;

    return U;
}

// ЗАДАНИЕ 6: Суммарный импульс
std::pair<double, double> galaxy::getTotalMomentum() const {
    double px = 0, py = 0;
    for(int i = 0; i < num; ++i) {
        if(stars[i]) {
            px += stars[i]->m * stars[i]->v[0];
            py += stars[i]->m * stars[i]->v[1];
        }
    }
    return {px, py};
}

// ЗАДАНИЕ 6: Угловой момент
double galaxy::getAngularMomentum() const {
    double L = 0;
    for(int i = 0; i < num; ++i) {
        if(stars[i]) {
            L += stars[i]->m * (stars[i]->x[0] * stars[i]->v[1] -
                                stars[i]->x[1] * stars[i]->v[0]);
        }
    }
    return L;
}

// Добавление нового объекта динамически
bool galaxy::addStar(double* coord, double* vel, double mass) {
    // Ищем первое пустое место
    for(int i = 0; i < num; ++i) {
        if(!stars[i]) {
            stars[i] = new star(coord, vel, mass);
            return true;
        }
    }
    return false; // Нет места для нового объекта
}

// Удаление случайного объекта (кроме центрального солнца)
bool galaxy::removeRandomStar() {
    // Считаем количество активных объектов (кроме солнца)
    int activeCount = 0;
    for(int i = 1; i < num; ++i) {
        if(stars[i]) activeCount++;
    }

    if(activeCount == 0) return false; // Остался только солнце

    // Выбираем случайный активный объект
    int targetIndex = rand() % activeCount;
    int currentIndex = 0;

    for(int i = 1; i < num; ++i) {
        if(stars[i]) {
            if(currentIndex == targetIndex) {
                delete stars[i];
                stars[i] = nullptr;
                return true;
            }
            currentIndex++;
        }
    }

    return false;
}

// ЗАДАНИЕ 7: Перегрузка оператора << для сохранения
std::ofstream& operator<<(std::ofstream& out, const galaxy& g) {
    out.write(reinterpret_cast<const char*>(&g.num), sizeof(g.num));
    out.write(reinterpret_cast<const char*>(&g.sysRadius), sizeof(g.sysRadius));
    out.write(reinterpret_cast<const char*>(&g.distConnect), sizeof(g.distConnect));
    out.write(reinterpret_cast<const char*>(&g.mergeCount), sizeof(g.mergeCount));

    for(int i = 0; i < g.num; ++i) {
        bool exists = (g.stars[i] != nullptr);
        out.write(reinterpret_cast<const char*>(&exists), sizeof(exists));

        if(exists) {
            out.write(reinterpret_cast<const char*>(g.stars[i]->x), sizeof(double) * dim);
            out.write(reinterpret_cast<const char*>(g.stars[i]->v), sizeof(double) * dim);
            out.write(reinterpret_cast<const char*>(&g.stars[i]->m), sizeof(double));
        }
    }

    return out;
}

// ЗАДАНИЕ 7: Перегрузка оператора >> для загрузки
std::ifstream& operator>>(std::ifstream& in, galaxy& g) {
    // Удаляем старые данные
    for(int i = 0; i < g.num; ++i) {
        if(g.stars[i]) delete g.stars[i];
    }
    delete[] g.stars;

    in.read(reinterpret_cast<char*>(&g.num), sizeof(g.num));
    in.read(reinterpret_cast<char*>(&g.sysRadius), sizeof(g.sysRadius));
    in.read(reinterpret_cast<char*>(&g.distConnect), sizeof(g.distConnect));
    in.read(reinterpret_cast<char*>(&g.mergeCount), sizeof(g.mergeCount));

    g.stars = new star*[g.num];
    for(int i = 0; i < g.num; ++i) g.stars[i] = nullptr;

    for(int i = 0; i < g.num; ++i) {
        bool exists;
        in.read(reinterpret_cast<char*>(&exists), sizeof(exists));

        if(exists) {
            double coord[dim], speed[dim], mass;
            in.read(reinterpret_cast<char*>(coord), sizeof(double) * dim);
            in.read(reinterpret_cast<char*>(speed), sizeof(double) * dim);
            in.read(reinterpret_cast<char*>(&mass), sizeof(double));

            g.stars[i] = new star(coord, speed, mass);
        }
    }

    return in;
}

// ЗАДАНИЕ 8: Тест 1 - Солнечная система
galaxy* galaxy::createSolarSystem(double distConn) {
    galaxy* sys = new galaxy(8, distConn, 2e12);

    // Удаляем случайные объекты
    for(int i = 0; i < sys->num; ++i) {
        if(sys->stars[i]) {
            delete sys->stars[i];
            sys->stars[i] = nullptr;
        }
    }

    // Солнце в центре (неподвижное)
    double sunCoord[2] = {0, 0};
    double sunVel[2] = {0, 0};
    sys->stars[0] = new star(sunCoord, sunVel, massSun);

    // Планеты с ПРАВИЛЬНЫМИ орбитальными скоростями
    struct Planet {
        double mass;
        double orbit;
    };

    Planet planets[] = {
        {massMercury, orbitMercury},
        {massVenus, orbitVenus},
        {massEarth, orbitEarth},
        {massMars, orbitMars},
        {massJupiter, orbitJupiter},
        {massSaturn, orbitSaturn}
    };

    for(int i = 0; i < 6; ++i) {
        double angle = 2.0 * M_PI * i / 6.0;  // Равномерно расставляем планеты
        double x = planets[i].orbit * cos(angle);
        double y = planets[i].orbit * sin(angle);

        // ПРАВИЛЬНАЯ орбитальная скорость: v = sqrt(G * M_sun / r)
        double orbitalSpeed = sqrt(G * massSun / planets[i].orbit);

        // Скорость перпендикулярна радиусу (для круговой орбиты)
        double vx = -orbitalSpeed * sin(angle);
        double vy = orbitalSpeed * cos(angle);

        double coord[2] = {x, y};
        double vel[2] = {vx, vy};
        sys->stars[i + 1] = new star(coord, vel, planets[i].mass);
    }

    sys->mergeCount = 0;
    return sys;
}

// ЗАДАНИЕ 8: Тест 2 - Столкновение двух солнечных систем
galaxy* galaxy::createDualSolarSystem(double distConn) {
    galaxy* sys = new galaxy(16, distConn, 3e12);

    for(int i = 0; i < sys->num; ++i) {
        if(sys->stars[i]) {
            delete sys->stars[i];
            sys->stars[i] = nullptr;
        }
    }

    double separation = 2e12;
    double approachSpeed = 5000;

    // Первое солнце слева
    double sun1Coord[2] = {-separation/2, 0};
    double sun1Vel[2] = {approachSpeed, 0};
    sys->stars[0] = new star(sun1Coord, sun1Vel, massSun * 0.8);

    // Планеты первой системы
    for(int i = 0; i < 7; ++i) {
        double angle = 2.0 * M_PI * i / 7.0;
        double orbit = orbitEarth * (1.0 + i * 0.5);
        double x = -separation/2 + orbit * cos(angle);
        double y = orbit * sin(angle);

        double orbitalSpeed = sqrt(G * massSun * 0.8 / orbit);
        double vx = approachSpeed - orbitalSpeed * sin(angle);
        double vy = orbitalSpeed * cos(angle);

        double coord[2] = {x, y};
        double vel[2] = {vx, vy};
        sys->stars[i + 1] = new star(coord, vel, massEarth * (0.5 + i * 0.2));
    }

    // Второе солнце справа
    double sun2Coord[2] = {separation/2, 0};
    double sun2Vel[2] = {-approachSpeed, 0};
    sys->stars[8] = new star(sun2Coord, sun2Vel, massSun * 1.2);

    // Планеты второй системы
    for(int i = 0; i < 7; ++i) {
        double angle = 2.0 * M_PI * i / 7.0 + M_PI/7.0;
        double orbit = orbitEarth * (1.0 + i * 0.5);
        double x = separation/2 + orbit * cos(angle);
        double y = orbit * sin(angle);

        double orbitalSpeed = sqrt(G * massSun * 1.2 / orbit);
        double vx = -approachSpeed - orbitalSpeed * sin(angle);
        double vy = orbitalSpeed * cos(angle);

        double coord[2] = {x, y};
        double vel[2] = {vx, vy};
        sys->stars[i + 9] = new star(coord, vel, massEarth * (0.5 + i * 0.2));
    }

    sys->mergeCount = 0;
    return sys;
}

// ЗАДАНИЕ 8: Тест 3 - Большая система (УМЕНЬШЕНО ДО 10000 объектов)
galaxy* galaxy::createLargeSystem(int variant, double distConn) {
    int totalObjects = 10000;
    galaxy* sys = new galaxy(totalObjects, distConn, 3e12);

    srand(time(NULL) + variant);

    // ПОЛНОСТЬЮ ПЕРЕСОЗДАЕМ ВСЕ ОБЪЕКТЫ!

    // Удаляем старые случайные объекты
    for(int i = 0; i < sys->num; ++i) {
        if(sys->stars[i]) {
            delete sys->stars[i];
            sys->stars[i] = nullptr;
        }
    }

    // СУПЕР-МАССИВНОЕ центральное солнце (неподвижное)
    double sunCoord[2] = {0, 0};
    double sunVel[2] = {0, 0};
    sys->stars[0] = new star(sunCoord, sunVel, massSun * 10000);  // В 10000 раз тяжелее!

    // Создаем планеты НА КРУГОВЫХ ОРБИТАХ с нуля
    for(int i = 1; i < sys->num; ++i) {
        // Случайная орбита от 3e11 м до 1.2e12 м (300-1200 млн км)
        // Это ГОРАЗДО меньше чем cutoff (3000 млн км) - гравитация сильная!
        double orbit = 3e11 + (9e11) * ((double)rand() / RAND_MAX);

        // Случайный угол
        double angle = 2.0 * M_PI * ((double)rand() / RAND_MAX);

        // Позиция на орбите
        double coord[2];
        coord[0] = orbit * cos(angle);
        coord[1] = orbit * sin(angle);

        // ПРАВИЛЬНАЯ орбитальная скорость для СУПЕР-МАССИВНОГО солнца
        double orbitalSpeed = sqrt(G * massSun * 10000 / orbit);

        // Скорость перпендикулярна радиусу (круговая орбита)
        double vel[2];
        vel[0] = -orbitalSpeed * sin(angle);
        vel[1] = orbitalSpeed * cos(angle);

        // Случайная масса от Меркурия до Земли
        double mass = massMercury + ((double)rand() / RAND_MAX) * (massEarth - massMercury);

        // СОЗДАЕМ НОВЫЙ ОБЪЕКТ С ПРАВИЛЬНЫМИ ПАРАМЕТРАМИ
        sys->stars[i] = new star(coord, vel, mass);
    }

    sys->mergeCount = 0;
    return sys;
}

// НОВОЕ: Создание системы с произвольным количеством объектов
galaxy* galaxy::createCustomSystem(int numObjects, double distConn) {
    // Минимум 1 объект (солнце), максимум 50000
    if(numObjects < 1) numObjects = 1;
    if(numObjects > 50000) numObjects = 50000;

    galaxy* sys = new galaxy(numObjects, distConn, 3e12);

    srand(time(NULL));

    // Удаляем старые случайные объекты
    for(int i = 0; i < sys->num; ++i) {
        if(sys->stars[i]) {
            delete sys->stars[i];
            sys->stars[i] = nullptr;
        }
    }

    // Центральное солнце
    double sunCoord[2] = {0, 0};
    double sunVel[2] = {0, 0};

    // Масса солнца зависит от количества объектов
    double centralMass = massSun;
    if(numObjects > 100) centralMass = massSun * (numObjects / 10.0);
    if(centralMass > massSun * 10000) centralMass = massSun * 10000;

    sys->stars[0] = new star(sunCoord, sunVel, centralMass);

    // Если только солнце - вернем
    if(numObjects == 1) {
        sys->mergeCount = 0;
        return sys;
    }

    // Создаем планеты на орбитах
    for(int i = 1; i < sys->num; ++i) {
        // Орбиты от 300 до 1200 млн км
        double orbit = 3e11 + (9e11) * ((double)rand() / RAND_MAX);

        // Случайный угол
        double angle = 2.0 * M_PI * ((double)rand() / RAND_MAX);

        // Позиция
        double coord[2];
        coord[0] = orbit * cos(angle);
        coord[1] = orbit * sin(angle);

        // Орбитальная скорость
        double orbitalSpeed = sqrt(G * centralMass / orbit);

        // Скорость перпендикулярна радиусу
        double vel[2];
        vel[0] = -orbitalSpeed * sin(angle);
        vel[1] = orbitalSpeed * cos(angle);

        // Случайная масса
        double mass = massMercury + ((double)rand() / RAND_MAX) * (massEarth - massMercury);

        sys->stars[i] = new star(coord, vel, mass);
    }

    sys->mergeCount = 0;
    return sys;
}

#endif // STAR_H
