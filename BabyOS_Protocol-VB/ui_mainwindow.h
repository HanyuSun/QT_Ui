/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *recTEXT;
    QPushButton *clearButton;
    QGroupBox *groupBox_5;
    QCheckBox *checkBoxBPS;
    QComboBox *comboBox;
    QPushButton *refreshButton;
    QPushButton *comBUTTON;
    QCheckBox *encryptBox;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLabel *label_8;
    QPushButton *Save_File;
    QTabWidget *tabWidget;
    QWidget *tab;
    QCustomPlot *widget;
    QWidget *tab_2;
    QCustomPlot *widget_2;
    QWidget *tab_3;
    QCustomPlot *widget_3;
    QWidget *tab_4;
    QCustomPlot *widget_4;
    QWidget *tab_5;
    QCustomPlot *widget_5;
    QGroupBox *groupBox;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLineEdit *line_StartFreq;
    QLineEdit *line_NumFreq;
    QLabel *label_6;
    QLabel *label_5;
    QLineEdit *line_FreqInc;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_2;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *line_Wx;
    QLabel *label_2;
    QLineEdit *line_Wy;
    QLabel *label_3;
    QLineEdit *line_I;
    QPushButton *pushButton_Modify;
    QGroupBox *groupBox_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1097, 668);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        recTEXT = new QTextBrowser(centralwidget);
        recTEXT->setObjectName(QString::fromUtf8("recTEXT"));
        recTEXT->setGeometry(QRect(30, 260, 501, 251));
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(470, 600, 71, 21));
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(30, 20, 501, 80));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        groupBox_5->setFont(font1);
        checkBoxBPS = new QCheckBox(groupBox_5);
        checkBoxBPS->setObjectName(QString::fromUtf8("checkBoxBPS"));
        checkBoxBPS->setGeometry(QRect(380, 50, 71, 16));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        checkBoxBPS->setFont(font2);
        comboBox = new QComboBox(groupBox_5);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(20, 30, 111, 21));
        refreshButton = new QPushButton(groupBox_5);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(280, 30, 75, 23));
        refreshButton->setFont(font2);
        comBUTTON = new QPushButton(groupBox_5);
        comBUTTON->setObjectName(QString::fromUtf8("comBUTTON"));
        comBUTTON->setGeometry(QRect(140, 22, 121, 41));
        comBUTTON->setFont(font1);
        encryptBox = new QCheckBox(groupBox_5);
        encryptBox->setObjectName(QString::fromUtf8("encryptBox"));
        encryptBox->setGeometry(QRect(380, 20, 81, 21));
        encryptBox->setFont(font2);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(550, 20, 191, 80));
        groupBox_4->setFont(font1);
        layoutWidget = new QWidget(groupBox_4);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 40, 171, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font2);

        horizontalLayout->addWidget(pushButton_2);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setMaximumSize(QSize(133, 16777215));

        horizontalLayout->addWidget(lineEdit);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font2);

        horizontalLayout->addWidget(label_8);

        Save_File = new QPushButton(centralwidget);
        Save_File->setObjectName(QString::fromUtf8("Save_File"));
        Save_File->setGeometry(QRect(470, 570, 71, 21));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(550, 110, 521, 511));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        widget = new QCustomPlot(tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 471, 431));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        widget_2 = new QCustomPlot(tab_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(20, 20, 471, 441));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        widget_3 = new QCustomPlot(tab_3);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(20, 20, 471, 431));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        widget_4 = new QCustomPlot(tab_4);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(20, 20, 471, 431));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        widget_5 = new QCustomPlot(tab_5);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(20, 20, 471, 431));
        tabWidget->addTab(tab_5, QString());
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 100, 501, 151));
        groupBox->setFont(font1);
        groupBox->setFlat(false);
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 30, 261, 108));
        gridLayout = new QGridLayout(layoutWidget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setEnabled(true);
        label_4->setFont(font2);
        label_4->setLineWidth(1);

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        line_StartFreq = new QLineEdit(layoutWidget_2);
        line_StartFreq->setObjectName(QString::fromUtf8("line_StartFreq"));
        line_StartFreq->setEnabled(true);

        gridLayout->addWidget(line_StartFreq, 0, 1, 1, 1);

        line_NumFreq = new QLineEdit(layoutWidget_2);
        line_NumFreq->setObjectName(QString::fromUtf8("line_NumFreq"));
        line_NumFreq->setEnabled(true);

        gridLayout->addWidget(line_NumFreq, 2, 1, 1, 1);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setEnabled(true);
        label_6->setFont(font2);

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setEnabled(true);
        label_5->setFont(font2);

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        line_FreqInc = new QLineEdit(layoutWidget_2);
        line_FreqInc->setObjectName(QString::fromUtf8("line_FreqInc"));
        line_FreqInc->setEnabled(true);

        gridLayout->addWidget(line_FreqInc, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(290, 50, 81, 61));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(380, 50, 111, 61));
        pushButton_3->setFont(font1);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 520, 411, 101));
        groupBox_2->setFont(font1);
        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(310, 30, 91, 51));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 21, 21));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        label->setFont(font3);
        line_Wx = new QLineEdit(groupBox_2);
        line_Wx->setObjectName(QString::fromUtf8("line_Wx"));
        line_Wx->setGeometry(QRect(40, 30, 61, 20));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 30, 21, 21));
        label_2->setFont(font3);
        line_Wy = new QLineEdit(groupBox_2);
        line_Wy->setObjectName(QString::fromUtf8("line_Wy"));
        line_Wy->setGeometry(QRect(140, 30, 61, 20));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 30, 16, 21));
        label_3->setFont(font3);
        line_I = new QLineEdit(groupBox_2);
        line_I->setObjectName(QString::fromUtf8("line_I"));
        line_I->setGeometry(QRect(230, 30, 61, 20));
        pushButton_Modify = new QPushButton(groupBox_2);
        pushButton_Modify->setObjectName(QString::fromUtf8("pushButton_Modify"));
        pushButton_Modify->setGeometry(QRect(120, 60, 75, 23));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(750, 20, 321, 80));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        groupBox_3->setFont(font4);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1097, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "User Interface", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Port Set", nullptr));
        checkBoxBPS->setText(QCoreApplication::translate("MainWindow", "9600bps", nullptr));
        refreshButton->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        comBUTTON->setText(QCoreApplication::translate("MainWindow", "Open Port", nullptr));
        encryptBox->setText(QCoreApplication::translate("MainWindow", "Encrypted ", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Internal Temperature", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Measure", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Celcius", nullptr));
        Save_File->setText(QCoreApplication::translate("MainWindow", "Download", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Nyquist", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Impedance", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Phase", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Real Part", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Imaginary Part", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Sweep Parameters", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Start Frequency [Hz]", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Number of Frequencies", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Frequency Increment [Hz]", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Start Sweep", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Classification", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Judge", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Wx", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Wy", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "I", nullptr));
        pushButton_Modify->setText(QCoreApplication::translate("MainWindow", "Modify", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Temperature Control", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
