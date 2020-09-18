#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(Student* stu,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,500);
    this->setWindowTitle("欢迎登陆机房预约系统");
    //点击注销登录按钮后返回主界面
    connect(ui->exitButton,&QPushButton::clicked,[=](){
        this->hide();
        emit studentWindowBack();
    });
}

StudentWindow::~StudentWindow()
{
    delete ui;
}
