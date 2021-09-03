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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
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
    QCustomPlot *widget;
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
    QPushButton *pushButton_3;
    QPushButton *Save_File;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1117, 668);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        recTEXT = new QTextBrowser(centralwidget);
        recTEXT->setObjectName(QString::fromUtf8("recTEXT"));
        recTEXT->setGeometry(QRect(40, 130, 451, 471));
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(520, 570, 81, 23));
        widget = new QCustomPlot(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(620, 130, 451, 471));
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(30, 20, 491, 80));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        groupBox_5->setFont(font);
        checkBoxBPS = new QCheckBox(groupBox_5);
        checkBoxBPS->setObjectName(QString::fromUtf8("checkBoxBPS"));
        checkBoxBPS->setGeometry(QRect(380, 50, 71, 16));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        checkBoxBPS->setFont(font1);
        comboBox = new QComboBox(groupBox_5);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(20, 30, 111, 21));
        refreshButton = new QPushButton(groupBox_5);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(280, 30, 75, 23));
        refreshButton->setFont(font1);
        comBUTTON = new QPushButton(groupBox_5);
        comBUTTON->setObjectName(QString::fromUtf8("comBUTTON"));
        comBUTTON->setGeometry(QRect(140, 22, 121, 41));
        comBUTTON->setFont(font);
        encryptBox = new QCheckBox(groupBox_5);
        encryptBox->setObjectName(QString::fromUtf8("encryptBox"));
        encryptBox->setGeometry(QRect(380, 20, 81, 21));
        encryptBox->setFont(font1);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(540, 20, 251, 80));
        groupBox_4->setFont(font);
        layoutWidget = new QWidget(groupBox_4);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 40, 231, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font1);

        horizontalLayout->addWidget(pushButton_2);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setMaximumSize(QSize(133, 16777215));

        horizontalLayout->addWidget(lineEdit);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);

        horizontalLayout->addWidget(label_8);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(500, 180, 111, 61));
        pushButton_3->setFont(font);
        Save_File = new QPushButton(centralwidget);
        Save_File->setObjectName(QString::fromUtf8("Save_File"));
        Save_File->setGeometry(QRect(500, 280, 111, 51));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(510, 360, 91, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1117, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

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
        label_8->setText(QCoreApplication::translate("MainWindow", "Degree Celcius", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Start Sweep", nullptr));
        Save_File->setText(QCoreApplication::translate("MainWindow", "Download Data", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Judge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
