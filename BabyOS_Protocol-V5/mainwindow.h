#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "b_protocol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    int ShowLog(bProtoID_t id, uint8_t cmd, uint8_t *param, bProtoLen_t param_len);
    ~MainWindow();


private slots:
    void on_comBUTTON_clicked();

    void on_refreshButton_clicked();

    void on_clearButton_clicked();

    void on_pushButton_clicked();

    void TimerTimeout(void);

    void on_pushButtonSetTime_clicked();

    void AnalyzeData(uint8_t *param, bProtoLen_t param_len);//数据读取

    void setupPlot();//初始化


    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_Save_File_clicked();





private:
    Ui::MainWindow *ui;
    QTimer *quartTimer;
    QString FilePath;//记录文件的路径
    QString Sreal_imag;
    bool OpenSeleteFile();//弹出选择文件对话框
    int NumParam;
};
#endif // MAINWINDOW_H
