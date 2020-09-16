#include "registerinterface.h"
#include "ui_registerinterface.h"
#include <QPainter>
#include <QFont>
RegisterInterface::RegisterInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterInterface)
{
    ui->setupUi(this);
    this->setFixedSize(800,500);
    this->setWindowTitle("欢迎登陆机房预约系统");
    ui->stackedWidget->move(this->width()*0.5-ui->stackedWidget->width()*0.5,this->height()*0.3);
    ui->widget_10->move(this->width()*0.5-ui->widget_10->width()*0.5,this->height()*0.5);
    //连接学生按钮与学生登录信息输入框
    connect(ui->studentButton,&QRadioButton::clicked,[=](){
       ui->stackedWidget->setCurrentIndex(0);
    });
    //连接老师按钮与老师登录信息输入框
    connect(ui->teacherButton,&QRadioButton::clicked,[=](){
       ui->stackedWidget->setCurrentIndex(1);
    });
    //连接管理员按钮与管理员登录信息输入框
    connect(ui->adminButton,&QRadioButton::clicked,[=](){
       ui->stackedWidget->setCurrentIndex(2);
    });

}
void RegisterInterface::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(26);
    painter.setFont(font);
    QString str = QString("欢迎登录机房预约系统");
    //绘制文字
    QFontMetrics metrics(font);
    int charWidth = metrics.width(str);//得到键的宽度
    painter.drawText(QRect((this->width()-charWidth)/2, this->height()*0.1,500, 50),str);
}
RegisterInterface::~RegisterInterface()
{
    delete ui;
}
