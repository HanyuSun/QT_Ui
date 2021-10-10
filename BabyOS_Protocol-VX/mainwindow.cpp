#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uartclass.h"
#include "b_mod_utc.h"
#include "QDateTime"
#include <stdint.h>

#include <QDebug>//用于在控制台输出调试信息
#include <QTime>//定时器
#include <QPainter>//坐标系绘图

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <qmath.h>


uartClass uartModule;
int Protocol_n = -1;

MainWindow* tmpClass;

extern "C" int Dispatch(bProtoID_t id, uint8_t cmd, uint8_t *param, bProtoLen_t param_len);


#define pi 3.1415926

typedef struct
{
    uint32_t    freq;
    uint16_t    realdata;
    uint16_t    imagdata;
    uint32_t    impedance;
    uint16_t    phase;
    uint16_t    temperatue;
}impendance_t;
impendance_t impedance;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    quartTimer = new QTimer(this);
    quartTimer->setSingleShot(true);
    connect(quartTimer, SIGNAL(timeout()), this, SLOT(TimerTimeout()));
    quartTimer->start(100);
    ui->comboBox->addItems(uartModule.uartComAvailable);

    Protocol_n = bProtocolRegist(0x1314, Dispatch);
    tmpClass = this;

    setupPlot();//图形界面初始化函数
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*************************************************************************串口打开刷新*****/
void MainWindow::on_comBUTTON_clicked()
{
    uint32_t bps = 115200;
    if(uartModule.uartGetOpenStatus())
    {
        uartModule.uartClosePort();
        ui->comboBox->setEnabled(true);
        ui->comBUTTON->setText("Open Port");
    }
    else
    {
        if(ui->checkBoxBPS->isChecked())
        {
            bps = 9600;
        }
        if(uartModule.uartOpenPort(ui->comboBox->currentText(), bps))
        {
            ui->comboBox->setEnabled(false);
            ui->comBUTTON->setText("Close Port");
        }
    }
}

void MainWindow::on_refreshButton_clicked()
{
    ui->comboBox->clear();
    uartModule.uartRefreshCOM();
    ui->comboBox->addItems(uartModule.uartComAvailable);
}
/****************************************************************************************/


/***********************************************************************************接收***/
void MainWindow::TimerTimeout()
{
    uint32_t len;
    uint8_t tmp_buf[8192];
    len = uartModule.uartReadBuff(tmp_buf);
    tmp_buf[len] = '\0';
    if(len > 0)
    {
        if(ui->encryptBox->isChecked() == true)
        {
            _bProtocolDecrypt(tmp_buf, len);
        }
        if(0 > bProtocolParse(Protocol_n, tmp_buf, len))
        {
            QString str = QString::fromStdString((char *)tmp_buf);
            ui->recTEXT->append(str);
        }
    }
    AnalyzeData(tmp_buf, len);
    quartTimer->start(100);
}

/****************************************************************************************/
QString hexToString(unsigned char *in, int len)
{
    int i;
    unsigned char inChar,hi,lo;
    QString s;

    for (i=0; i<len; i++)
    {
        inChar = in[i];

        hi = (inChar & 0xF0) >> 4;
        if (hi > 9)
            hi = 'A' + (hi - 0x0A);
        else
            hi += 0x30;
        s.append(hi);

        lo = inChar & 0x0F;
        if (lo > 9)
            lo = 'A' + (lo - 0x0A);
        else
            lo += 0x30;
        s.append(lo);

        s.append(0x20);
    }
    return s;
}

/****************************************************************************************/

/****************************************************************************************/

void MainWindow::AnalyzeData(uint8_t *param, bProtoLen_t param_len)
{
    bool ok;
    int j,i,k;

    QString str = hexToString(param, param_len);
    QString Tem;
    QStringList strList = str.split(" ");
    QString Sreal;
    QString Simag;
    float FImage;
    float FReal;

    int num_s = strList.count();
    NumParam = (num_s-8)/8;
    static int dataInt[20];
    static int forplot[4];
    for (j=0; j<num_s; j++)
    {
        dataInt[j] = strList[j].toInt(&ok, 16);
    }
    if (param[7]==0x07){
        Tem = QString::number(dataInt[8]);
//        Tem = tr("%1").arg(dataInt[7]);
        ui->lineEdit->setText(Tem);
    }
    else if (param[7]==0x03)
        ui->recTEXT->append(strList[8]);
    else if (param[7]==0x06)
    {
        Sreal_imag = "frequency   real   imaginary   Impedance   Phase";
        Sreal_imag = Sreal_imag + "\n";
        for (i=0;i< NumParam;i++) {
            Real[i] = param[8+i*4] + param[8+i*4+1]*256 + param[8+i*4+2]*256*256 + param[8+i*4+3]*256*256*256;
            Imag[i] = param[8+NumParam*4+i*4] + param[8+NumParam*4+i*4+1]*256 + param[8+NumParam*4+i*4+2]*256*256 + param[8+NumParam*4+i*4+3]*256*256*256;
            Imped[i] = sqrt((Real[i])*(Real[i])+(Imag[i])*(Imag[i]));
            FImage = Imag[i];
            FReal = Real[i];
            Phase[i] = 180 + atan(FImage/FReal) * 180/pi;

            Sreal_imag = Sreal_imag + QString::number(Frequency[i]) + "  " + QString::number(Real[i]) + "  " + QString::number(Imag[i]) + "  " + QString::number(Imped[i]) + "  " + QString::number(Phase[i]) + "\n";

//            Imped[i] = 1/(GainFactor[i]*sqrt(Real[i]*Real[i]+Imag[i]*Imag[i]));
//            if(Real[i]>=0 && Imag[i]>0) Phase[i] = atan(Imag[i]/Real[i]) * 180/pi - DeltaFi[i];
//            else if(Real[i]<0 && Imag[i]>=0) Phase[i] = 180 + atan(Imag[i]/Real[i]) * 180/pi - DeltaFi[i];
//            else if(Real[i]<=0 && Imag[i]<0) Phase[i] = 180 + atan(Imag[i]/Real[i]) * 180/pi - DeltaFi[i];
//            else Phase[i] = 180 + atan(Imag[i]/Real[i]) * 180/pi - DeltaFi[i];

//            Realt[i] =  Imped[i] * cos(phase[i]*pi/180);
//            Imagt[i] =  Imped[i] * sin(phase[i]*pi/180);
        }
        ui->recTEXT->append(Sreal_imag);


//        forplot[0] = dataInt[9]*256+dataInt[10];
//        forplot[1] = dataInt[11]*256+dataInt[12];
//        ui->widget->graph(0)->addData(forplot[0],forplot[1]);//添加数据1到曲线1
//        ui->widget->replot();//每次画完曲线一定要更新显示

//        ui->widget->graph(0)->addData(Real[0],Imag[0]);//添加数据1到曲线1
//        ui->widget->replot();//每次画完曲线一定要更新显示

        for (k=0;k< NumParam;k++) {
            ui->widget->graph(0)->addData(Real[k],Imag[k]);//添加数据1到曲线1
            ui->widget->replot();//每次画完曲线一定要更新显示

            ui->widget_2->graph(0)->addData(Frequency[k], Imped[k]);//添加数据1到曲线1
            ui->widget_2->replot();//每次画完曲线一定要更新显示

            ui->widget_3->graph(0)->addData(Frequency[k], Phase[k]);//添加数据1到曲线1
            ui->widget_3->replot();//每次画完曲线一定要更新显示

            ui->widget_4->graph(0)->addData(Frequency[k], Real[k]);//添加数据1到曲线1
            ui->widget_4->replot();//每次画完曲线一定要更新显示

            ui->widget_5->graph(0)->addData(Frequency[k], Imag[k]);//添加数据1到曲线1
            ui->widget_5->replot();//每次画完曲线一定要更新显示

        }

    }

}



int MainWindow::ShowLog(bProtoID_t id, uint8_t cmd, uint8_t *param, bProtoLen_t param_len)
{

    QString str = "r->";
    str = str + "id: " + QString::number(id);
    str = str + "cmd: " + QString::number(cmd);
    str = str + "param: " + hexToString(param, param_len);
    ui->recTEXT->append(str);
    return 0;
}


int Dispatch(bProtoID_t id, uint8_t cmd, uint8_t *param, bProtoLen_t param_len)
{
    tmpClass->ShowLog(id, cmd, param, param_len);
    return 0;
}



void MainWindow::on_clearButton_clicked()
{
    ui->recTEXT->clear();
    ui->widget->removeGraph(0);//1
    ui->widget->replot();
    ui->widget_2->removeGraph(0);//2
    ui->widget_2->replot();
    ui->widget_3->removeGraph(0);//3
    ui->widget_3->replot();
    ui->widget_4->removeGraph(0);//4
    ui->widget_4->replot();
    ui->widget_5->removeGraph(0);//5
    ui->widget_5->replot();
    setupPlot();
}

void MainWindow::on_pushButton_clicked()
{
    if(BinaryClassification())
    {
        ui->recTEXT->append("Positive");
    }
    else ui->recTEXT->append("Negative");
}

void MainWindow::on_pushButtonSetTime_clicked()
{
    uint8_t table[128];
    int len = 0;
    uint32_t utc = 0;
    bUTC_DateTime_t dt;

    dt.year = QDateTime::currentDateTime().date().year();
    dt.month = QDateTime::currentDateTime().date().month();
    dt.day = QDateTime::currentDateTime().date().day();

    dt.hour = QDateTime::currentDateTime().time().hour();
    dt.minute = QDateTime::currentDateTime().time().minute();
    dt.second = QDateTime::currentDateTime().time().second();
    utc = bStruct2UTC(dt);

    len = bProtocolPack(Protocol_n, 0xFFFFFFFF, 0x2, (uint8_t *)&utc, 4, table);
    uartModule.uartSendBuff(table, len);
    // TODO
    uartModule.exp_recv_byte_num = 1;

}

void MainWindow::setupPlot()
{
    //设置曲线一
    ui->widget->addGraph();//添加一条曲线
    QPen pen;
    pen.setWidth(1);//设置画笔线条宽度
    pen.setColor(Qt::blue);
    ui->widget->graph(0)->setPen(pen);//设置画笔颜色
    //ui->widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    ui->widget->graph(0)->setName("real vs imaginary");
    ui->widget->graph(0)->setAntialiasedFill(false);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//曲线画笔
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));//曲线形状

    //设置图表
    ui->widget->xAxis->setLabel(QStringLiteral("real part"));//设置x坐标轴名称
    ui->widget->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    //ui->widget->xAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->xAxis->setTickStep(2);//设置刻度间距5
    ui->widget->xAxis->setRange(0,300000);//设定x轴的范围

    ui->widget->yAxis->setLabel(QStringLiteral("imaginary part"));//设置y坐标轴名称
    ui->widget->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色
    //ui->widget->yAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->yAxis->setTickStep(10);//设置刻度间距1
    ui->widget->yAxis->setRange(-250000,250000);//设定y轴范围

    ui->widget->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->widget->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->widget->legend->setVisible(true);//显示图例

    ui->widget->replot();

    //设置曲线二
    ui->widget_2->addGraph();//添加一条曲线
//    QPen pen;
    pen.setWidth(1);//设置画笔线条宽度
    pen.setColor(Qt::blue);
    ui->widget_2->graph(0)->setPen(pen);//设置画笔颜色
    //ui->widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    ui->widget_2->graph(0)->setName("impedance vs frequency");
    ui->widget_2->graph(0)->setAntialiasedFill(false);
    ui->widget_2->graph(0)->setLineStyle(QCPGraph::lsNone);//曲线画笔
    ui->widget_2->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));//曲线形状

    //设置图表
    ui->widget_2->xAxis->setLabel(QStringLiteral("Frequency(Hz)"));//设置x坐标轴名称
    ui->widget_2->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    //ui->widget->xAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->xAxis->setTickStep(2);//设置刻度间距5
    ui->widget_2->xAxis->setRange(0,120000);//设定x轴的范围

    ui->widget_2->yAxis->setLabel(QStringLiteral("Impedance"));//设置y坐标轴名称
    ui->widget_2->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色
    //ui->widget->yAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->yAxis->setTickStep(10);//设置刻度间距1
    ui->widget_2->yAxis->setRange(0,350000);//设定y轴范围

    ui->widget_2->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->widget_2->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->widget_2->legend->setVisible(true);//显示图例

    ui->widget_2->replot();


    //设置曲线三
    ui->widget_3->addGraph();//添加一条曲线
//    QPen pen;
    pen.setWidth(1);//设置画笔线条宽度
    pen.setColor(Qt::blue);
    ui->widget_3->graph(0)->setPen(pen);//设置画笔颜色
    //ui->widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    ui->widget_3->graph(0)->setName("phase vs frequency");
    ui->widget_3->graph(0)->setAntialiasedFill(false);
    ui->widget_3->graph(0)->setLineStyle(QCPGraph::lsNone);//曲线画笔
    ui->widget_3->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));//曲线形状

    //设置图表
    ui->widget_3->xAxis->setLabel(QStringLiteral("Frequency(Hz)"));//设置x坐标轴名称
    ui->widget_3->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    //ui->widget->xAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->xAxis->setTickStep(2);//设置刻度间距5
    ui->widget_3->xAxis->setRange(0,120000);//设定x轴的范围

    ui->widget_3->yAxis->setLabel(QStringLiteral("Phase"));//设置y坐标轴名称
    ui->widget_3->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色
    //ui->widget->yAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->yAxis->setTickStep(10);//设置刻度间距1
    ui->widget_3->yAxis->setRange(0,180);//设定y轴范围

    ui->widget_3->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->widget_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->widget_3->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->widget_3->legend->setVisible(true);//显示图例

    ui->widget_3->replot();

    //设置曲线四
    ui->widget_4->addGraph();//添加一条曲线
//    QPen pen;
    pen.setWidth(1);//设置画笔线条宽度
    pen.setColor(Qt::blue);
    ui->widget_4->graph(0)->setPen(pen);//设置画笔颜色
    //ui->widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    ui->widget_4->graph(0)->setName("real part vs frequency");
    ui->widget_4->graph(0)->setAntialiasedFill(false);
    ui->widget_4->graph(0)->setLineStyle(QCPGraph::lsNone);//曲线画笔
    ui->widget_4->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));//曲线形状

    //设置图表
    ui->widget_4->xAxis->setLabel(QStringLiteral("Frequency(Hz)"));//设置x坐标轴名称
    ui->widget_4->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    //ui->widget->xAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->xAxis->setTickStep(2);//设置刻度间距5
    ui->widget_4->xAxis->setRange(0,120000);//设定x轴的范围

    ui->widget_4->yAxis->setLabel(QStringLiteral("Real Part"));//设置y坐标轴名称
    ui->widget_4->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色
    //ui->widget->yAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->yAxis->setTickStep(10);//设置刻度间距1
    ui->widget_4->yAxis->setRange(0,300000);//设定y轴范围

    ui->widget_4->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->widget_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->widget_4->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->widget_4->legend->setVisible(true);//显示图例

    ui->widget_4->replot();

    //设置曲线五
    ui->widget_5->addGraph();//添加一条曲线
//    QPen pen;
    pen.setWidth(1);//设置画笔线条宽度
    pen.setColor(Qt::blue);
    ui->widget_5->graph(0)->setPen(pen);//设置画笔颜色
    //ui->widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
    ui->widget_5->graph(0)->setName("imaginary part vs frequency");
    ui->widget_5->graph(0)->setAntialiasedFill(false);
    ui->widget_5->graph(0)->setLineStyle(QCPGraph::lsNone);//曲线画笔
    ui->widget_5->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));//曲线形状

    //设置图表
    ui->widget_5->xAxis->setLabel(QStringLiteral("Frequency(Hz)"));//设置x坐标轴名称
    ui->widget_5->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    //ui->widget->xAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->xAxis->setTickStep(2);//设置刻度间距5
    ui->widget_5->xAxis->setRange(0,120000);//设定x轴的范围

    ui->widget_5->yAxis->setLabel(QStringLiteral("Imaginary Part"));//设置y坐标轴名称
    ui->widget_5->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色
    //ui->widget->yAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->yAxis->setTickStep(10);//设置刻度间距1
    ui->widget_5->yAxis->setRange(-150000,150000);//设定y轴范围

    ui->widget_5->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->widget_5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->widget_5->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->widget_5->legend->setVisible(true);//显示图例

    ui->widget_5->replot();

}

void MainWindow::on_pushButton_3_clicked() // Start Sweep
{
    uint8_t table2[128];
    int len2;
    uint8_t param2[1] = {0};
    len2 = bProtocolPack(Protocol_n, 0x00000001, 0x06, param2, 1, table2);
    if(ui->encryptBox->isChecked() == true)
    {
        _bProtocolEncrypt(table2, len2);
    }
    uartModule.uartSendBuff(table2, len2);
    uartModule.exp_recv_byte_num = INumF*8+9;
}

void MainWindow::on_pushButton_2_clicked() //temperature
{
    uint8_t table2[128];
    int len2;
    uint8_t param2[2] = {0};
    len2 = bProtocolPack(Protocol_n, 0x00000001, 0x07, param2, 1, table2);
    if(ui->encryptBox->isChecked() == true)
    {
        _bProtocolEncrypt(table2, len2);
    }
    uartModule.uartSendBuff(table2, len2);
    // TODO
    uartModule.exp_recv_byte_num = 1;
}

void MainWindow::on_pushButton_4_clicked()   //Confirm registers
{
    QString StartF = ui->line_StartFreq->text();
    QString IncF = ui->line_FreqInc->text();
    QString NumF = ui->line_NumFreq->text();


    bool ok;
    uint8_t table[128];
    int len,i;
    uint8_t param[10];
    uint32_t temp[1];
    QString strFreq = "Frequency: ";

    temp[0] = StartF.toInt(&ok, 10);
    uint32_t IStartF = temp[0];
    param[3] = (temp[0] >> 24) & 0XFF;
    param[2] = (temp[0] >> 16) & 0XFF;
    param[1] = (temp[0] >> 8) & 0XFF;
    param[0] = temp[0] & 0XFF;
    temp[0] = IncF.toInt(&ok, 10);
    uint16_t IIncF = temp[0];
    param[5] = (temp[0] >> 8) & 0XFF;
    param[4] = temp[0] & 0XFF;
    temp[0] = NumF.toInt(&ok, 10);
    INumF = temp[0];
    param[9] = (temp[0] >> 24) & 0XFF;
    param[8] = (temp[0] >> 16) & 0XFF;
    param[7] = (temp[0] >> 8) & 0XFF;
    param[6] = temp[0] & 0XFF;

    for (i=0;i<INumF;i++) {

        Frequency[i] = IStartF + IIncF * i;
        strFreq = strFreq + QString::number(Frequency[i]) + "  ";
    }

    ui->recTEXT->append(strFreq);


    len = bProtocolPack(Protocol_n, 0x00000001, 0x3, param, 10, table);
    if(ui->encryptBox->isChecked() == true)
    {
        _bProtocolEncrypt(table, len);
    }
    uartModule.uartSendBuff(table, len);
    uartModule.exp_recv_byte_num = 10;




}




void MainWindow::on_Save_File_clicked()
{


    if(false == OpenSeleteFile())//弹出选择文件对话框 如果成功选择文件，主线程myWidget类就有对象存储了文件路径
    {
      return;
    }
    if(FilePath == "")//如果没有选择文件，即文件路径为空
    {

     return;
    }
    ui->recTEXT->append(Sreal_imag);
    QFile f(FilePath);
    f.open(QIODevice::WriteOnly);
    f.write(Sreal_imag.toStdString().data());

}

bool MainWindow::OpenSeleteFile()//弹出选择文件对话框
{
    /**
   * @brief strPath
   * 类名::函数名->此时的函数是一个静态函数。例如：getOpenFileName
   * getOpenFileName()函数提供了六个参数：
   *  * 第一个参数的作用是用于指定父组件，基本上构造函数都会提供一个默认的值，即parent = 0;
   *  * 第二个参数的作用是显示的按钮的标题
   *  * 第三个参数的作用是对话框显示时默认打开的目录
   *  * 第四个参数的作用是对话框的后缀名过滤器，过滤掉不需要选择的文件名称
   *  * 第五个参数的作用是默认选择的过滤器
   *  * 第六个参数的作用是对话框的一些参数设定，例如对话框只显示文件夹等信息
   *  ** 注意：还函数有的参数这是可以不需要选择的，例如最后两个参数都是可以省略的，
   *       但是第一个参数和第三个参数当没有特殊要求的时候，将第一个参数置为NULL，
   *       第三个参数置为空字符串。即"";
   */
  QString strPath = QFileDialog::getSaveFileName(NULL,QString::fromUtf8("select file"),"",QObject::tr("txt(*.txt)"));
  if(strPath == "")
  {
    QMessageBox::information(this,QString::fromUtf8("Attention"),QString::fromUtf8("Failed! No file selected"),"OK");
    return false;//用户点击的取消按钮
  }
  FilePath = strPath;
  return true;
}

bool MainWindow::BinaryClassification()
{
    uint8_t feature1,feature2;
    feature1 = Real[16]/100000;
    feature2 = Real[17]/100000;
    float wx = -3.8989;
    float wy = 4.4139;
    float intercept = 9.1881;
    float y;
    y = wx * feature1 + wy * feature2 + intercept;
    if(y>0)
    {
        return false;
    }
    else return true;
}


//bool MainWindow::BinaryClassification(uint8_t *param, bProtoLen_t param_len)
//{
//    //paramater explaination:
//    //param: 读存放完整帧内容的数组；
//    //param_len: param的长度
//    uint8_t feature1,feature2;
//    int NumParam;
//    int i;

//    NumParam = (param_len-8)/8;

//    for (i=0;i< NumParam;i++) {
//        Real[i] = param[8+i*4] + param[8+i*4+1]*256 + param[8+i*4+2]*256*256 + param[8+i*4+3]*256*256*256;
//        Imag[i] = param[8+NumParam*4+i*4] + param[8+NumParam*4+i*4+1]*256 + param[8+NumParam*4+i*4+2]*256*256 + param[8+NumParam*4+i*4+3]*256*256*256;
//    }

//    feature1 = Real[16]/100000;
//    feature2 = Imag[16]/100000;
//    float wx = -3.8989;
//    float wy = 4.4139;
//    float intercept = 9.1881;
//    float y;
//    y = wx * feature1 + wy * feature2 + intercept;
//    if(y>0)
//    {
//        return false;
//    }
//    else return true;
//}


//bool MainWindow::BinaryClassification(int32_t *Real, int32_t *Imag)
//{
//    //主要使用了输入中的Real[16]和Real[17]这两个特征，暂时没用Imag
//    //参数解释
//    //Real:存放所有实部的数组；
//    //Imag:存放所有虚部的数组；
//    //feature1: 对应二维平面上的X轴；
//    //feature2: 对应二维平面上的Y轴；
//    //边界函数: wx * feature1 + wy * feature2 + intercept = 0, 二维平面中，边界函数以上的为Negative，边界函数以下的是Positve
//    uint8_t feature1,feature2;
//    feature1 = Real[16]/100000;
//    feature2 = -1 * Real[17]/100000;
//    float wx = -3.8989;
//    float wy = 4.4139;
//    float intercept = 9.1881;
//    float y;
//    y = wx * feature1 - wy * feature2 + intercept;
//    if(y>0)
//    {
//        return false; //negative
//    }
//    else return true; //positive
//}





