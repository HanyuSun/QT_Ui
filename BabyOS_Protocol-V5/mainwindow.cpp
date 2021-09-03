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
#include <math.h>


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
    uint8_t tmp_buf[1024];
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
    int32_t Real[1000];
    int32_t Imag[1000];
    QString Sreal;
    QString Simag;

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
        Sreal_imag = "real   imaginary";
        Sreal_imag = Sreal_imag + "\n";
        for (i=0;i< NumParam;i++) {
            Real[i] = param[8+i*4] + param[8+i*4+1]*256 + param[8+i*4+2]*256*256 + param[8+i*4+3]*256*256*256;
            Imag[i] = param[8+NumParam*4+i*4] + param[8+NumParam*4+i*4+1]*256 + param[8+NumParam*4+i*4+2]*256*256 + param[8+NumParam*4+i*4+3]*256*256*256;

            Sreal_imag = Sreal_imag + QString::number(Real[i]) + "  " + QString::number(Imag[i]) + "\n";

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
    ui->widget->removeGraph(0);
    ui->widget->replot();
    setupPlot();
}

void MainWindow::on_pushButton_clicked()
{
    uint8_t table[128];
    int len;
    uint8_t param[7] = {11,2,3,4,5,6};
    len = bProtocolPack(Protocol_n, 0x630, 0x2, param, 7, table);
    if(ui->encryptBox->isChecked() == true)
    {
        _bProtocolEncrypt(table, len);
    }
    uartModule.uartSendBuff(table, len);
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
    ui->widget->graph(0)->setName("0-65536");
    ui->widget->graph(0)->setAntialiasedFill(false);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//曲线画笔
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));//曲线形状

    //设置图表
    ui->widget->xAxis->setLabel(QStringLiteral("x"));//设置x坐标轴名称
    ui->widget->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    //ui->widget->xAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->xAxis->setTickStep(2);//设置刻度间距5
    ui->widget->xAxis->setRange(0,65536);//设定x轴的范围

    ui->widget->yAxis->setLabel(QStringLiteral("y"));//设置y坐标轴名称
    ui->widget->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色
    //ui->widget->yAxis->setAutoTickStep(false);//设置是否自动分配刻度间距
    //ui->widget->yAxis->setTickStep(10);//设置刻度间距1
    ui->widget->yAxis->setRange(0,65536);//设定y轴范围

    ui->widget->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->widget->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->widget->legend->setVisible(true);//显示图例

    ui->widget->replot();

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
}

//void MainWindow::on_pushButton_4_clicked()   //Confirm registers
//{
//    QString StartF = ui->line_StartFreq->text();
//    QString EndF = ui->line_EndFreq->text();
//    QString NumF = ui->line_NumFreq->text();

//    uint8_t Vpp = ui->comboBox_3->currentIndex();
//    uint8_t PGAS = ui->comboBox_2->currentIndex();

//    bool ok;
//    uint8_t table[128];
//    int len;
//    uint8_t param[14];
//    uint32_t temp[1];

//    temp[0] = StartF.toInt(&ok, 10);
//    param[3] = (temp[0] >> 24) & 0XFF;
//    param[2] = (temp[0] >> 16) & 0XFF;
//    param[1] = (temp[0] >> 8) & 0XFF;
//    param[0] = temp[0] & 0XFF;
//    temp[0] = EndF.toInt(&ok, 10);
//    param[7] = (temp[0] >> 24) & 0XFF;
//    param[6] = (temp[0] >> 16) & 0XFF;
//    param[5] = (temp[0] >> 8) & 0XFF;
//    param[4] = temp[0] & 0XFF;
//    temp[0] = NumF.toInt(&ok, 10);
//    param[11] = (temp[0] >> 24) & 0XFF;
//    param[10] = (temp[0] >> 16) & 0XFF;
//    param[9] = (temp[0] >> 8) & 0XFF;
//    param[8] = temp[0] & 0XFF;

//    param[12] = Vpp;
//    param[13] = PGAS;


//    len = bProtocolPack(Protocol_n, 0x00000001, 0x3, param, 14, table);
//    if(ui->encryptBox->isChecked() == true)
//    {
//        _bProtocolEncrypt(table, len);
//    }
//    uartModule.uartSendBuff(table, len);




//}




void MainWindow::on_Save_File_clicked()
{

    int i;

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
    f.write("Real");
    f.write("      ");
    f.write("Imaginary");
    f.write("\n");
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

