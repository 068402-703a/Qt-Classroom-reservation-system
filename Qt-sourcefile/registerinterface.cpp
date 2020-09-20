#include "registerinterface.h"
#include "ui_registerinterface.h"
#include <QPainter>
#include <QFont>
#include <QFile>
#include <QPixmap>
#include <QMessageBox>
#include <QTextStream>
#include "student.h"
#include "teacher.h"
#include "manager.h"
RegisterInterface::RegisterInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterInterface)
{
    ui->setupUi(this);
    this->setFixedSize(800,500);
    this->setWindowTitle("欢迎来到机房预约系统");
    createManagerInfo();
    ui->stackedWidget->move(this->width()*0.5-ui->stackedWidget->width()*0.5,this->height()*0.3);
    ui->widget_10->move(this->width()*0.5-ui->widget_10->width()*0.5,this->height()*0.5);
    //配置登录按钮

    ui->LoginButton->setFixedSize(200,60);
    ui->LoginButton->move(this->width()*0.2-ui->exitButton->width()*0.5,this->height()*0.7);
    //配置退出按钮
    ui->exitButton->setFixedSize(200,60);
    ui->exitButton->move(this->width()*0.5+ui->exitButton->width()*0.5,this->height()*0.7);
    connect(ui->exitButton,&QPushButton::clicked,[=](){

            this-close();


    });
    //一开始将按钮选中到学生界面
     ui->studentButton->setChecked(true);
     ui->stackedWidget->setCurrentIndex(0);
    //为学号输入框设置提示
    ui->XuehaoLineEdit->setPlaceholderText("请输入学号");
    //为职工号输入框设置提示
    ui->tealineEdit->setPlaceholderText("请输入职工号");
    //为用户民输入框设置提示
    ui->userlineEdit->setPlaceholderText("请输入用户名");
    //为密码输入框设置提示
    ui->stupassWordlineEdit1->setPlaceholderText("请输入密码");
    ui->teapasswordLineEdit2->setPlaceholderText("请输入密码");
    ui->adminpassWordlineEdit3->setPlaceholderText("请输入密码");

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
    //连接登录按钮与登录函数
    connect(ui->LoginButton,&QPushButton::clicked,[=](){
        switch(ui->stackedWidget->currentIndex())
        {
        case 0://表示以学生身份登录
            LoginIn("student.txt",0);
            break;
        case 1://表示以老师身份登录
            LoginIn("teacher.txt",1);
            break;
        case 2://表示以管理员身份登录
            LoginIn("admin.txt",2);
            break;
        }
    });



}
void RegisterInterface::createManagerInfo()
{
    QFile tempFile;
    if(!tempFile.exists("admin.txt"))
    {
        tempFile.setFileName("admin.txt");
        if(!tempFile.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("打开文件失败");
            msgBox.exec();
            exit(0);
        }
        QTextStream out(&tempFile);
        out << "manager1" <<"&"<< "123"<<"\n";

        tempFile.close();
    }

}
void RegisterInterface::paintEvent(QPaintEvent *event)
{


    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/new/prefix1/images/computerRoomSystem2.jpg");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
RegisterInterface::~RegisterInterface()
{
    delete ui;
}
//登录功能   参数1  操作文件名   参数2  操作身份类型
void RegisterInterface::LoginIn(QString fileName, int type)
{
    //如果是还没有录入学生和老师的信息，则无法登录
    QFile ifs;
    QMessageBox msgBox;
    if(!ifs.exists(fileName))
    {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("还没有录入学生和老师的信息!!");
        msgBox.exec();

    }
    else
    {
        ifs.setFileName(fileName);
       if(!ifs.open(QIODevice::ReadOnly|QIODevice::Text))
        {

            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("打开文件失败");
            msgBox.exec();
            exit(0);
        }

        //准备接受用户的信息
        QString id;
        QString pwd;


        //判断身份
        if (type == 0) //学生身份
        {
            id=ui->XuehaoLineEdit->text();
            pwd=ui->stupassWordlineEdit1->text();
        }
        else if (type == 1)
        {
            id=ui->tealineEdit->text();
            pwd=ui->teapasswordLineEdit2->text();
        }
        else
        {
            id=ui->userlineEdit->text();
            pwd=ui->adminpassWordlineEdit3->text();
        }
         QString userinput_account = id + "&" + pwd;
         QTextStream in(&ifs);
         QString linedata;
         bool flag=false;
            while (!in.atEnd())
            {

                linedata = in.readLine();
                if (linedata == userinput_account)
                {
                    flag=true;
                    break;
                }
            }

            if (!flag)//登录失败
            {
                msgBox.setText("账号密码有误，重新输入！！");
                msgBox.exec();

            }
            else
            {
                //学生身份成功登录
                if(type==0)
                {
                    msgBox.setText("学生验证登录成功！");
                    msgBox.exec();
                    Student * stu = new Student(id, pwd);
                    //登录成功后就清空输入框中的内容
                    ui->XuehaoLineEdit->clear();
                    ui->stupassWordlineEdit1->clear();
                    this->hide();
                    stuWindow=new StudentWindow(stu);
                    stuWindow->setGeometry(this->geometry());
                    stuWindow->show();
                    //监听从学生界面返回的信号
                    connect(stuWindow,&StudentWindow::studentWindowBack,[=](){
                        this->setGeometry(stuWindow->geometry());
                        this->show();
                       delete stuWindow;
                        stuWindow=NULL;
                        delete stu;

                    });

                } //老师身份成功登录
                else if(type==1)
                {

                    msgBox.setText("老师验证登录成功！");
                    msgBox.exec();
                    Teacher * tea = new Teacher(id, pwd);
                    //登录成功后就清空输入框中的内容
                    ui->tealineEdit->clear();
                    ui->teapasswordLineEdit2->clear();
                    this->hide();
                    //进入老师界面
                    teaWindow=new TeacherWindow(tea);
                    teaWindow->setGeometry(this->geometry());
                    teaWindow->show();
                    //监听从老师界面返回的信号
                    connect(teaWindow,&TeacherWindow::teacherWindowBack,[=](){
                        this->setGeometry(teaWindow->geometry());

                        this->show();
                       delete teaWindow;
                        teaWindow=NULL;
                        delete tea;

                    });

                } else //管理员身份成功登录
                    {

                    msgBox.setText("管理员验证登录成功！");
                    msgBox.exec();

                    Manager * man = new Manager(id, pwd);
                    ui->userlineEdit->clear();
                    ui->adminpassWordlineEdit3->clear();
                    this->hide();
                    //进入管理员界面

                    manWindow=new ManagerWindow(man);
                    manWindow->setGeometry(this->geometry());
                    manWindow->show();
                    //监听从管理员界面返回的信号
                    connect(manWindow,&ManagerWindow::managerWindowBack,[=](){
                        this->setGeometry(manWindow->geometry());
                        this->show();
                       delete manWindow;
                        manWindow=NULL;
                        delete man;

                    });

                    }


            }
    }


}
