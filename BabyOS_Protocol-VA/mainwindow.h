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
    bool BinaryClassification();




    void on_pushButton_4_clicked();


    void on_pushButton_Modify_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *quartTimer;
    QString FilePath;//记录文件的路径
    QString Sreal_imag;
    QString Sreal_imag2;
    int64_t Real[1000];
    int64_t Imag[1000];
    int32_t Imped[1000];
    float Phase[1000];
    bool OpenSeleteFile();//弹出选择文件对话框
    int NumParam;
    int INumF;
    int32_t Frequency[1000];
    uint32_t IStartF;
    uint16_t IIncF;
    bool Modify;
    float wx;
    float wy;
    float intercept;

};
#endif // MAINWINDOW_H
