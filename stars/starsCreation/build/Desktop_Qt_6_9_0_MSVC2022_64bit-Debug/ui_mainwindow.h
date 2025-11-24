/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButtonStart;
    QGroupBox *groupBox_timeStep;
    QLabel *label_step;
    QLabel *label_time;
    QGroupBox *groupBox_kineticEnergy;
    QLabel *label_kineticEnergy;
    QGroupBox *groupBox_merging;
    QLabel *label_distConnect;
    QLineEdit *lineEdit_distConnect;
    QPushButton *pushButton_updateDist;
    QLabel *label_mergeCount;
    QGroupBox *groupBox_timestep;
    QLabel *label_dt;
    QLineEdit *lineEdit_dt;
    QPushButton *pushButton_updateDt;
    QPushButton *pushButton_dtX2;
    QPushButton *pushButton_dtDiv2;
    QLabel *label_currentDt;
    QGroupBox *groupBox_objects;
    QPushButton *pushButton_addObject;
    QPushButton *pushButton_removeObject;
    QLabel *label_objectMass;
    QLineEdit *lineEdit_objectMass;
    QGroupBox *groupBox_top3;
    QLabel *label_top1;
    QLabel *label_top2;
    QLabel *label_top3;
    QGroupBox *groupBox_conservation;
    QLabel *label_totalEnergy;
    QLabel *label_momentum;
    QLabel *label_angularMomentum;
    QLabel *label_potentialEnergy;
    QGroupBox *groupBox_fileOps;
    QPushButton *pushButton_save;
    QPushButton *pushButton_load;
    QGroupBox *groupBox_tests;
    QPushButton *pushButton_test1;
    QPushButton *pushButton_test2;
    QPushButton *pushButton_test3;
    QLabel *label_customSystem;
    QLineEdit *lineEdit_customObjects;
    QPushButton *pushButton_createCustom;
    QLabel *label_customHint;
    QLabel *label_objectCount;
    QLabel *label_statistics;
    QLineEdit *lineEdit_initialObjects;
    QGroupBox *groupBox_optimization;
    QLabel *label_stepsPerFrame;
    QLineEdit *lineEdit_stepsPerFrame;
    QPushButton *pushButton_updateSteps;
    QLabel *label_cutoffDistance;
    QLineEdit *lineEdit_cutoffDistance;
    QPushButton *pushButton_updateCutoff;
    QLabel *label_perfInfo;
    QCheckBox *checkBox_useGrid;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(1210, 10, 720, 1020));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, -430, 703, 1450));
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 1450));
        pushButtonStart = new QPushButton(scrollAreaWidgetContents);
        pushButtonStart->setObjectName("pushButtonStart");
        pushButtonStart->setGeometry(QRect(10, 10, 680, 60));
        groupBox_timeStep = new QGroupBox(scrollAreaWidgetContents);
        groupBox_timeStep->setObjectName("groupBox_timeStep");
        groupBox_timeStep->setGeometry(QRect(10, 80, 680, 100));
        label_step = new QLabel(groupBox_timeStep);
        label_step->setObjectName("label_step");
        label_step->setGeometry(QRect(10, 30, 660, 30));
        label_time = new QLabel(groupBox_timeStep);
        label_time->setObjectName("label_time");
        label_time->setGeometry(QRect(10, 60, 660, 30));
        groupBox_kineticEnergy = new QGroupBox(scrollAreaWidgetContents);
        groupBox_kineticEnergy->setObjectName("groupBox_kineticEnergy");
        groupBox_kineticEnergy->setGeometry(QRect(10, 190, 680, 80));
        label_kineticEnergy = new QLabel(groupBox_kineticEnergy);
        label_kineticEnergy->setObjectName("label_kineticEnergy");
        label_kineticEnergy->setGeometry(QRect(10, 30, 660, 40));
        label_kineticEnergy->setWordWrap(true);
        groupBox_merging = new QGroupBox(scrollAreaWidgetContents);
        groupBox_merging->setObjectName("groupBox_merging");
        groupBox_merging->setGeometry(QRect(10, 280, 680, 110));
        label_distConnect = new QLabel(groupBox_merging);
        label_distConnect->setObjectName("label_distConnect");
        label_distConnect->setGeometry(QRect(10, 30, 300, 30));
        lineEdit_distConnect = new QLineEdit(groupBox_merging);
        lineEdit_distConnect->setObjectName("lineEdit_distConnect");
        lineEdit_distConnect->setGeometry(QRect(310, 30, 250, 30));
        pushButton_updateDist = new QPushButton(groupBox_merging);
        pushButton_updateDist->setObjectName("pushButton_updateDist");
        pushButton_updateDist->setGeometry(QRect(570, 30, 100, 30));
        label_mergeCount = new QLabel(groupBox_merging);
        label_mergeCount->setObjectName("label_mergeCount");
        label_mergeCount->setGeometry(QRect(10, 70, 660, 30));
        groupBox_timestep = new QGroupBox(scrollAreaWidgetContents);
        groupBox_timestep->setObjectName("groupBox_timestep");
        groupBox_timestep->setGeometry(QRect(10, 400, 680, 110));
        label_dt = new QLabel(groupBox_timestep);
        label_dt->setObjectName("label_dt");
        label_dt->setGeometry(QRect(10, 30, 200, 30));
        lineEdit_dt = new QLineEdit(groupBox_timestep);
        lineEdit_dt->setObjectName("lineEdit_dt");
        lineEdit_dt->setGeometry(QRect(210, 30, 150, 30));
        pushButton_updateDt = new QPushButton(groupBox_timestep);
        pushButton_updateDt->setObjectName("pushButton_updateDt");
        pushButton_updateDt->setGeometry(QRect(370, 30, 100, 30));
        pushButton_dtX2 = new QPushButton(groupBox_timestep);
        pushButton_dtX2->setObjectName("pushButton_dtX2");
        pushButton_dtX2->setGeometry(QRect(480, 30, 90, 30));
        pushButton_dtDiv2 = new QPushButton(groupBox_timestep);
        pushButton_dtDiv2->setObjectName("pushButton_dtDiv2");
        pushButton_dtDiv2->setGeometry(QRect(580, 30, 90, 30));
        label_currentDt = new QLabel(groupBox_timestep);
        label_currentDt->setObjectName("label_currentDt");
        label_currentDt->setGeometry(QRect(10, 70, 660, 30));
        groupBox_objects = new QGroupBox(scrollAreaWidgetContents);
        groupBox_objects->setObjectName("groupBox_objects");
        groupBox_objects->setGeometry(QRect(10, 520, 680, 110));
        pushButton_addObject = new QPushButton(groupBox_objects);
        pushButton_addObject->setObjectName("pushButton_addObject");
        pushButton_addObject->setGeometry(QRect(10, 30, 220, 35));
        pushButton_removeObject = new QPushButton(groupBox_objects);
        pushButton_removeObject->setObjectName("pushButton_removeObject");
        pushButton_removeObject->setGeometry(QRect(240, 30, 220, 35));
        label_objectMass = new QLabel(groupBox_objects);
        label_objectMass->setObjectName("label_objectMass");
        label_objectMass->setGeometry(QRect(10, 75, 200, 25));
        lineEdit_objectMass = new QLineEdit(groupBox_objects);
        lineEdit_objectMass->setObjectName("lineEdit_objectMass");
        lineEdit_objectMass->setGeometry(QRect(210, 75, 250, 25));
        groupBox_top3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_top3->setObjectName("groupBox_top3");
        groupBox_top3->setGeometry(QRect(10, 640, 680, 160));
        label_top1 = new QLabel(groupBox_top3);
        label_top1->setObjectName("label_top1");
        label_top1->setGeometry(QRect(10, 30, 660, 35));
        label_top1->setWordWrap(true);
        label_top2 = new QLabel(groupBox_top3);
        label_top2->setObjectName("label_top2");
        label_top2->setGeometry(QRect(10, 70, 660, 35));
        label_top2->setWordWrap(true);
        label_top3 = new QLabel(groupBox_top3);
        label_top3->setObjectName("label_top3");
        label_top3->setGeometry(QRect(10, 110, 660, 35));
        label_top3->setWordWrap(true);
        groupBox_conservation = new QGroupBox(scrollAreaWidgetContents);
        groupBox_conservation->setObjectName("groupBox_conservation");
        groupBox_conservation->setGeometry(QRect(10, 810, 680, 170));
        label_totalEnergy = new QLabel(groupBox_conservation);
        label_totalEnergy->setObjectName("label_totalEnergy");
        label_totalEnergy->setGeometry(QRect(10, 30, 660, 30));
        label_totalEnergy->setWordWrap(true);
        label_momentum = new QLabel(groupBox_conservation);
        label_momentum->setObjectName("label_momentum");
        label_momentum->setGeometry(QRect(10, 65, 660, 30));
        label_momentum->setWordWrap(true);
        label_angularMomentum = new QLabel(groupBox_conservation);
        label_angularMomentum->setObjectName("label_angularMomentum");
        label_angularMomentum->setGeometry(QRect(10, 100, 660, 30));
        label_angularMomentum->setWordWrap(true);
        label_potentialEnergy = new QLabel(groupBox_conservation);
        label_potentialEnergy->setObjectName("label_potentialEnergy");
        label_potentialEnergy->setGeometry(QRect(10, 135, 660, 30));
        label_potentialEnergy->setWordWrap(true);
        groupBox_fileOps = new QGroupBox(scrollAreaWidgetContents);
        groupBox_fileOps->setObjectName("groupBox_fileOps");
        groupBox_fileOps->setGeometry(QRect(10, 990, 680, 80));
        pushButton_save = new QPushButton(groupBox_fileOps);
        pushButton_save->setObjectName("pushButton_save");
        pushButton_save->setGeometry(QRect(10, 30, 330, 40));
        pushButton_load = new QPushButton(groupBox_fileOps);
        pushButton_load->setObjectName("pushButton_load");
        pushButton_load->setGeometry(QRect(350, 30, 320, 40));
        groupBox_tests = new QGroupBox(scrollAreaWidgetContents);
        groupBox_tests->setObjectName("groupBox_tests");
        groupBox_tests->setGeometry(QRect(10, 1080, 680, 180));
        pushButton_test1 = new QPushButton(groupBox_tests);
        pushButton_test1->setObjectName("pushButton_test1");
        pushButton_test1->setGeometry(QRect(10, 30, 210, 35));
        pushButton_test2 = new QPushButton(groupBox_tests);
        pushButton_test2->setObjectName("pushButton_test2");
        pushButton_test2->setGeometry(QRect(230, 30, 210, 35));
        pushButton_test3 = new QPushButton(groupBox_tests);
        pushButton_test3->setObjectName("pushButton_test3");
        pushButton_test3->setGeometry(QRect(450, 30, 220, 35));
        label_customSystem = new QLabel(groupBox_tests);
        label_customSystem->setObjectName("label_customSystem");
        label_customSystem->setGeometry(QRect(10, 72, 120, 25));
        lineEdit_customObjects = new QLineEdit(groupBox_tests);
        lineEdit_customObjects->setObjectName("lineEdit_customObjects");
        lineEdit_customObjects->setGeometry(QRect(130, 72, 100, 25));
        lineEdit_customObjects->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_createCustom = new QPushButton(groupBox_tests);
        pushButton_createCustom->setObjectName("pushButton_createCustom");
        pushButton_createCustom->setGeometry(QRect(240, 72, 120, 25));
        label_customHint = new QLabel(groupBox_tests);
        label_customHint->setObjectName("label_customHint");
        label_customHint->setGeometry(QRect(370, 72, 300, 25));
        label_objectCount = new QLabel(groupBox_tests);
        label_objectCount->setObjectName("label_objectCount");
        label_objectCount->setGeometry(QRect(10, 100, 660, 25));
        label_statistics = new QLabel(groupBox_tests);
        label_statistics->setObjectName("label_statistics");
        label_statistics->setGeometry(QRect(10, 125, 660, 25));
        lineEdit_initialObjects = new QLineEdit(groupBox_tests);
        lineEdit_initialObjects->setObjectName("lineEdit_initialObjects");
        lineEdit_initialObjects->setGeometry(QRect(10, 160, 660, 30));
        lineEdit_initialObjects->setReadOnly(true);
        groupBox_optimization = new QGroupBox(scrollAreaWidgetContents);
        groupBox_optimization->setObjectName("groupBox_optimization");
        groupBox_optimization->setGeometry(QRect(10, 1270, 680, 150));
        label_stepsPerFrame = new QLabel(groupBox_optimization);
        label_stepsPerFrame->setObjectName("label_stepsPerFrame");
        label_stepsPerFrame->setGeometry(QRect(10, 30, 200, 25));
        lineEdit_stepsPerFrame = new QLineEdit(groupBox_optimization);
        lineEdit_stepsPerFrame->setObjectName("lineEdit_stepsPerFrame");
        lineEdit_stepsPerFrame->setGeometry(QRect(210, 30, 100, 25));
        pushButton_updateSteps = new QPushButton(groupBox_optimization);
        pushButton_updateSteps->setObjectName("pushButton_updateSteps");
        pushButton_updateSteps->setGeometry(QRect(320, 30, 100, 25));
        label_cutoffDistance = new QLabel(groupBox_optimization);
        label_cutoffDistance->setObjectName("label_cutoffDistance");
        label_cutoffDistance->setGeometry(QRect(10, 65, 200, 25));
        lineEdit_cutoffDistance = new QLineEdit(groupBox_optimization);
        lineEdit_cutoffDistance->setObjectName("lineEdit_cutoffDistance");
        lineEdit_cutoffDistance->setGeometry(QRect(210, 65, 100, 25));
        pushButton_updateCutoff = new QPushButton(groupBox_optimization);
        pushButton_updateCutoff->setObjectName("pushButton_updateCutoff");
        pushButton_updateCutoff->setGeometry(QRect(320, 65, 100, 25));
        label_perfInfo = new QLabel(groupBox_optimization);
        label_perfInfo->setObjectName("label_perfInfo");
        label_perfInfo->setGeometry(QRect(10, 100, 660, 40));
        label_perfInfo->setWordWrap(true);
        checkBox_useGrid = new QCheckBox(groupBox_optimization);
        checkBox_useGrid->setObjectName("checkBox_useGrid");
        checkBox_useGrid->setGeometry(QRect(430, 30, 240, 25));
        checkBox_useGrid->setChecked(true);
        scrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\223\321\200\320\260\320\262\320\270\321\202\320\260\321\206\320\270\320\276\320\275\320\275\320\260\321\217 \321\201\320\270\320\274\321\203\320\273\321\217\321\206\320\270\321\217 N-\321\202\320\265\320\273", nullptr));
        scrollArea->setStyleSheet(QCoreApplication::translate("MainWindow", "QScrollArea { border: none; background-color: rgb(240, 240, 245); }", nullptr));
        pushButtonStart->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"    background-color: rgb(50, 150, 250);\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    border-radius: 10px;\n"
"    font-size: 18pt;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgb(70, 170, 255);\n"
"}", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("MainWindow", "\342\226\266 Start", nullptr));
        groupBox_timeStep->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; }", nullptr));
        groupBox_timeStep->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276 \321\201\320\270\320\274\321\203\320\273\321\217\321\206\320\270\320\270", nullptr));
        label_step->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 11pt;", nullptr));
        label_step->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263 \321\200\320\260\321\201\321\207\320\265\321\202\320\260: 0", nullptr));
        label_time->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 11pt;", nullptr));
        label_time->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \321\201\320\270\321\201\321\202\320\265\320\274\321\213: 0.0 \321\201", nullptr));
        groupBox_kineticEnergy->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; }", nullptr));
        groupBox_kineticEnergy->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\270\320\275\320\265\321\202\320\270\321\207\320\265\321\201\320\272\320\260\321\217 \321\215\320\275\320\265\321\200\320\263\320\270\321\217", nullptr));
        label_kineticEnergy->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 11pt;", nullptr));
        label_kineticEnergy->setText(QCoreApplication::translate("MainWindow", "\320\232\320\270\320\275\320\265\321\202\320\270\321\207\320\265\321\201\320\272\320\260\321\217 \321\215\320\275\320\265\321\200\320\263\320\270\321\217: 0.0 \320\224\320\266", nullptr));
        groupBox_merging->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; }", nullptr));
        groupBox_merging->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\320\273\320\270\321\217\320\275\320\270\321\217 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262", nullptr));
#if QT_CONFIG(tooltip)
        label_distConnect->setToolTip(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\212\320\265\320\272\321\202\321\213 \320\262\321\201\320\265\320\263\320\264\320\260 \321\201\320\273\320\270\320\262\320\260\321\216\321\202\321\201\321\217 \320\277\321\200\320\270 \320\272\320\260\321\201\320\260\320\275\320\270\320\270 (\321\204\320\270\320\267\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \321\200\320\260\320\264\320\270\321\203\321\201\321\213). \320\255\321\202\320\276 \320\277\320\276\320\273\320\265 - \320\264\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\320\276\320\265 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\264\320\273\321\217 \321\215\320\272\321\201\320\277\320\265\321\200\320\270\320\274\320\265\320\275\321\202\320\276\320\262.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_distConnect->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_distConnect->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\277. \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \321\201\320\273\320\270\321\217\320\275\320\270\321\217 (\320\274):", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_distConnect->setToolTip(QCoreApplication::translate("MainWindow", "0 = \321\202\320\276\320\273\321\214\320\272\320\276 \321\204\320\270\320\267\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \321\201\321\202\320\276\320\273\320\272\320\275\320\276\320\262\320\265\320\275\320\270\321\217. \320\243\320\262\320\265\320\273\320\270\321\207\321\214\321\202\320\265 \320\264\320\273\321\217 \321\201\320\273\320\270\321\217\320\275\320\270\321\217 \320\275\320\260 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\270.", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEdit_distConnect->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        lineEdit_distConnect->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_updateDist->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        pushButton_updateDist->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        label_mergeCount->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt; color: rgb(200, 100, 50);", nullptr));
        label_mergeCount->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\201\320\273\320\270\321\217\320\275\320\270\320\271: 0", nullptr));
        groupBox_timestep->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; }", nullptr));
        groupBox_timestep->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\321\214\321\216 \321\201\320\270\320\274\321\203\320\273\321\217\321\206\320\270\320\270", nullptr));
        label_dt->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_dt->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263 \320\262\321\200\320\265\320\274\320\265\320\275\320\270 (dt):", nullptr));
        lineEdit_dt->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        lineEdit_dt->setText(QCoreApplication::translate("MainWindow", "10000", nullptr));
        pushButton_updateDt->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        pushButton_updateDt->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pushButton_dtX2->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        pushButton_dtX2->setText(QCoreApplication::translate("MainWindow", "\303\2272 \320\221\321\213\321\201\321\202\321\200\320\265\320\265", nullptr));
        pushButton_dtDiv2->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        pushButton_dtDiv2->setText(QCoreApplication::translate("MainWindow", "\303\2672 \320\234\320\265\320\264\320\273\320\265\320\275\320\275\320\265\320\265", nullptr));
        label_currentDt->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt; color: rgb(100, 100, 100);", nullptr));
        label_currentDt->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 dt: 10000 \321\201", nullptr));
        groupBox_objects->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; }", nullptr));
        groupBox_objects->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\276\320\261\321\212\320\265\320\272\321\202\320\260\320\274\320\270", nullptr));
        pushButton_addObject->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt; background-color: rgb(100, 200, 100);", nullptr));
        pushButton_addObject->setText(QCoreApplication::translate("MainWindow", " \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202", nullptr));
        pushButton_removeObject->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt; background-color: rgb(255, 150, 150);", nullptr));
        pushButton_removeObject->setText(QCoreApplication::translate("MainWindow", " \320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\201\320\273\321\203\321\207\320\260\320\271\320\275\321\213\320\271", nullptr));
        label_objectMass->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        label_objectMass->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\201\320\260 (\303\227 \320\274\320\260\321\201\321\201\320\260 \320\227\320\265\320\274\320\273\320\270):", nullptr));
        lineEdit_objectMass->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        lineEdit_objectMass->setText(QCoreApplication::translate("MainWindow", "1.0", nullptr));
        groupBox_top3->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; }", nullptr));
        groupBox_top3->setTitle(QCoreApplication::translate("MainWindow", "\320\242\320\276\320\277-3 \321\201\320\260\320\274\321\213\321\205 \320\274\320\260\321\201\321\201\320\270\320\262\320\275\321\213\321\205 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262", nullptr));
        label_top1->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_top1->setText(QCoreApplication::translate("MainWindow", "1\357\270\217\342\203\243 \320\234\320\260\321\201\321\201\320\260: - | \320\237\320\276\320\267\320\270\321\206\320\270\321\217: - | \320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214: -", nullptr));
        label_top2->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_top2->setText(QCoreApplication::translate("MainWindow", "2\357\270\217\342\203\243 \320\234\320\260\321\201\321\201\320\260: - | \320\237\320\276\320\267\320\270\321\206\320\270\321\217: - | \320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214: -", nullptr));
        label_top3->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_top3->setText(QCoreApplication::translate("MainWindow", "3\357\270\217\342\203\243 \320\234\320\260\321\201\321\201\320\260: - | \320\237\320\276\320\267\320\270\321\206\320\270\321\217: - | \320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214: -", nullptr));
        groupBox_conservation->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; }", nullptr));
        groupBox_conservation->setTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\320\276\320\275\321\213 \321\201\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217", nullptr));
        label_totalEnergy->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_totalEnergy->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\320\275\320\260\321\217 \321\215\320\275\320\265\321\200\320\263\320\270\321\217: 0.0 \320\224\320\266", nullptr));
        label_momentum->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_momentum->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\320\277\321\203\320\273\321\214\321\201: (0.0, 0.0) \320\272\320\263\302\267\320\274/\321\201", nullptr));
        label_angularMomentum->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_angularMomentum->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\273\320\276\320\262\320\276\320\271 \320\274\320\276\320\274\320\265\320\275\321\202: 0.0 \320\272\320\263\302\267\320\274\302\262/\321\201", nullptr));
        label_potentialEnergy->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_potentialEnergy->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\202\320\265\320\275\321\206\320\270\320\260\320\273\321\214\320\275\320\260\321\217 \321\215\320\275\320\265\321\200\320\263\320\270\321\217: 0.0 \320\224\320\266", nullptr));
        groupBox_fileOps->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; }", nullptr));
        groupBox_fileOps->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273\320\276\320\262\321\213\320\265 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
        pushButton_save->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        pushButton_save->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\201\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
        pushButton_load->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        pushButton_load->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\201\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
        groupBox_tests->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; }", nullptr));
        groupBox_tests->setTitle(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202\321\213 \320\270 \321\201\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        pushButton_test1->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        pushButton_test1->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202 1: \320\241\320\276\320\273\320\275\320\265\321\207\320\275\320\260\321\217", nullptr));
        pushButton_test2->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        pushButton_test2->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202 2: \320\241\321\202\320\276\320\273\320\272\320\275\320\276\320\262\320\265\320\275\320\270\320\265", nullptr));
        pushButton_test3->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        pushButton_test3->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202 3: \320\221\320\276\320\273\321\214\321\210\320\260\321\217", nullptr));
        label_customSystem->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt; font-weight: bold;", nullptr));
        label_customSystem->setText(QCoreApplication::translate("MainWindow", "\320\241\320\262\320\276\321\217 \321\201\320\270\321\201\321\202\320\265\320\274\320\260:", nullptr));
        lineEdit_customObjects->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        lineEdit_customObjects->setText(QCoreApplication::translate("MainWindow", "1000", nullptr));
        lineEdit_customObjects->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        pushButton_createCustom->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt; background-color: rgb(50, 150, 50); color: white; font-weight: bold;", nullptr));
        pushButton_createCustom->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        label_customHint->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 8pt; color: rgb(100, 100, 100);", nullptr));
        label_customHint->setText(QCoreApplication::translate("MainWindow", "(\320\276\321\202 1 \320\264\320\276 50000 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262)", nullptr));
        label_objectCount->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        label_objectCount->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\265\320\265 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262: 0", nullptr));
        label_statistics->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt; color: rgb(100, 100, 100);", nullptr));
        label_statistics->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\265: - | \320\243\320\264\320\260\320\273\320\265\320\275\320\276: - | \320\241\320\276\320\267\320\264\320\260\320\275\320\276 \321\201\320\273\320\270\321\217\320\275\320\270\320\265\320\274: -", nullptr));
        lineEdit_initialObjects->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 8pt; background-color: rgb(245, 245, 245);", nullptr));
        groupBox_optimization->setStyleSheet(QCoreApplication::translate("MainWindow", "QGroupBox { font-weight: bold; font-size: 11pt; color: rgb(200, 50, 50); }", nullptr));
        groupBox_optimization->setTitle(QCoreApplication::translate("MainWindow", "\320\236\320\277\321\202\320\270\320\274\320\270\320\267\320\260\321\206\320\270\321\217 \320\277\321\200\320\276\320\270\320\267\320\262\320\276\320\264\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\320\270", nullptr));
#if QT_CONFIG(tooltip)
        label_stepsPerFrame->setToolTip(QCoreApplication::translate("MainWindow", "\320\221\320\276\320\273\321\214\321\210\320\265 \321\210\320\260\320\263\320\276\320\262 = \320\261\321\213\321\201\321\202\321\200\320\265\320\265 \320\262\320\270\320\267\321\203\320\260\320\273\321\214\320\275\320\276, \320\275\320\276 \320\274\320\265\320\275\320\265\320\265 \320\277\320\273\320\260\320\262\320\275\320\276", nullptr));
#endif // QT_CONFIG(tooltip)
        label_stepsPerFrame->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt; color: black;", nullptr));
        label_stepsPerFrame->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263\320\276\320\262 \321\204\320\270\320\267\320\270\320\272\320\270/\320\272\320\260\320\264\321\200:", nullptr));
        lineEdit_stepsPerFrame->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        lineEdit_stepsPerFrame->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        pushButton_updateSteps->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        pushButton_updateSteps->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
#if QT_CONFIG(tooltip)
        label_cutoffDistance->setToolTip(QCoreApplication::translate("MainWindow", "\320\230\320\263\320\275\320\276\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202\321\213 \320\264\320\260\320\273\321\214\321\210\320\265 \321\215\321\202\320\276\320\263\320\276 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\321\217 (0 = \320\276\321\202\320\272\320\273\321\216\321\207\320\265\320\275\320\276)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_cutoffDistance->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt; color: black;", nullptr));
        label_cutoffDistance->setText(QCoreApplication::translate("MainWindow", "Cutoff \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\265 (\320\274):", nullptr));
        lineEdit_cutoffDistance->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt;", nullptr));
        lineEdit_cutoffDistance->setText(QCoreApplication::translate("MainWindow", "1e11", nullptr));
        pushButton_updateCutoff->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt;", nullptr));
        pushButton_updateCutoff->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        label_perfInfo->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 9pt; color: rgb(100, 100, 100);", nullptr));
        label_perfInfo->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202 1-2: cutoff = 3\303\22710\302\271\302\262 \320\274, \321\210\320\260\320\263\320\276\320\262 = 1-5 | \320\242\320\265\321\201\321\202 3: cutoff = 3\303\22710\302\271\302\262 \320\274, \321\210\320\260\320\263\320\276\320\262 = 10-20", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_useGrid->setToolTip(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\321\214 \320\277\321\200\320\276\321\201\321\202\321\200\320\260\320\275\321\201\321\202\320\262\320\265\320\275\320\275\321\203\321\216 \321\201\320\265\321\202\320\272\321\203 \320\264\320\273\321\217 \321\203\321\201\320\272\320\276\321\200\320\265\320\275\320\270\321\217 (\321\200\320\265\320\272\320\276\320\274\320\265\320\275\320\264\321\203\320\265\321\202\321\201\321\217)", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_useGrid->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 10pt; color: black; font-weight: bold;", nullptr));
        checkBox_useGrid->setText(QCoreApplication::translate("MainWindow", "Spatial Grid", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
