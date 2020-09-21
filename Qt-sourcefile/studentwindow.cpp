#include "studentwindow.h"
#include "ui_studentwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextEdit>
#include <QPainter>
#include <QPixmap>
#include <QInputDialog>
StudentWindow::StudentWindow(Student* stu,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,500);
    this->setWindowTitle("欢迎登陆机房预约系统");
    ui->reservepushButton->setFixedSize(200,60);
     ui->checkMyresepushButton->setFixedSize(200,60);
      ui->checkallrespushButton->setFixedSize(200,60);
       ui->cancelpushButton->setFixedSize(200,60);
        ui->exitButton->setFixedSize(200,60);
        ui->configpushButton_5->setFixedSize(200,60);
        ui->exitpushButton_6->setFixedSize(200,60);
        ui->cancelexitpushButton->setFixedSize(200,60);
        ui->choosepushButton->setFixedSize(200,60);
    //进来时，默认是学生主界面
    ui->stackedWidget->setCurrentIndex(0);
    //点击注销登录按钮后返回主界面
    connect(ui->exitButton,&QPushButton::clicked,[=](){
        this->hide();
        emit studentWindowBack();
    });
    //点击预约机房按钮，进到预约机房界面
    connect(ui->reservepushButton,&QPushButton::clicked,[=](){
        ui->computerroom1radioButton->setChecked(true);
        ui->stackedWidget->setCurrentIndex(1);
    });
    //配置预约周几的下拉框
    QStringList dates;
    dates << "周一" << "周二" << "周三" << "周四"<<"周五";
    ui->datecomboBox->addItems(dates);
    //配置预约时间段的下拉框
    dates.clear();
    dates << "上午"<<"下午";
    ui->intervalcomboBox->addItems(dates);
    //点击预约机房界面返回按钮，即可返回学生主界面
    connect(ui->exitpushButton_6,&QPushButton::clicked,[=](){
       ui->stackedWidget->setCurrentIndex(0);
    });
    //在申请预约界面点击确认按钮完成对机房的申请
    connect(ui->configpushButton_5,&QPushButton::clicked,[=](){
        applyOrder(stu);
    });
    //在申请预约界面点击查看我的预约按钮完成对我的预约的查看
    connect(ui->checkMyresepushButton,&QPushButton::clicked,[=](){

       showMyOrder(of,stu);
    });
    //在申请预约界面点击查看所有预约按钮完成对所有预约的查看
    connect(ui->checkallrespushButton,&QPushButton::clicked,[=](){

       showAllOrder(of);
    });
    //在学生主界面点击取消预约按钮去到取消预约的界面
    connect(ui->cancelpushButton,&QPushButton::clicked,[=](){
        QMessageBox msgBox;
        QFile ex;

        if(!ex.exists("order.txt"))
        {
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("无预约记录");
            msgBox.exec();
        }
        else
        {
            of = new OrderFile;
            configCancelOrder(of,stu);

        }


    });
    //在取消预约界面选择返回按钮就返回学生主界面
    connect(ui->cancelexitpushButton,&QPushButton::clicked,[=](){
        delete of;
        of=NULL;
       ui->stackedWidget->setCurrentIndex(0);
       ui->textEdit->clear();

    });
    QFont fon;
    fon.setFamily("华文新魏");
    fon.setPointSize(15);
    ui->textEdit->setFont(fon);
    //在切换到页面后，就连接选择按钮

    connect(ui->choosepushButton,&QPushButton::clicked,[=](){

        CancelOrder(of, stu);
    });

}
void StudentWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/new/prefix1/images/computerRoomSystem2.jpg");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
//申请预约
void StudentWindow::applyOrder(Student* stu)
{
    //申请预约

        QString date;  //日期
        QString interval ; //时间段
        int room = 0; //机房编号

        date=ui->datecomboBox->currentText();
        interval=ui->intervalcomboBox->currentText();
        if(ui->computerroom1radioButton->isChecked())
        {
            room=1;
        }
        else if(ui->commputerroom2radioButton->isChecked())
        {
            room=2;
        }
        else
        {
            room=3;
        }
        QString status="审核中";
        QString s= date + " "+ interval + " "+ stu->m_Name + " "+ QString::number(room) + " "+status;

        QFile ifs;

         bool flag=false;
         if(ifs.exists("order.txt"))
         {
             ifs.setFileName("order.txt");
             QMessageBox msgBox;

                  if (!ifs.open(QIODevice::ReadOnly | QIODevice::Text))
                  {
                      msgBox.setIcon(QMessageBox::Critical);
                      msgBox.setText("打开文件失败");
                      msgBox.exec();
                      exit(0);
                  }



                  QTextStream in(&ifs);
                  while (!in.atEnd()) {
                      QString line = in.readLine();

                      if(s==line)
                      {
                          flag=true;
                          break;
                      }

                  }

         }

             QMessageBox msgBox;
             if(flag)
             {
                 msgBox.setText("你已申请过相同的预约,无法再申请" );
                 msgBox.exec();
             }
             else
             {

                 msgBox.setText("预约成功！请等待审核" );
                 msgBox.exec();
                 //相当于预约完一次后就回到主界面
                 ui->stackedWidget->setCurrentIndex(0);
                 QFile ofs("order.txt");
                 if(!ofs.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
                 {
                     msgBox.setIcon(QMessageBox::Critical);
                     msgBox.setText("打开文件失败");
                     msgBox.exec();
                     exit(0);
                 }
                 QTextStream out(&ofs);

                 out << date << " "<< interval << " "<< stu->m_Name << " "<< room << " "<<status<<"\n";
                 ofs.close();
             }



}
//查看自身预约
void StudentWindow::showMyOrder(OrderFile*of,Student* stu)
{
    QFile ex;
    QMessageBox msgBox;
    if(!ex.exists("order.txt"))
    {
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("无预约记录");
        msgBox.exec();
    }
    else
    {
        of=new OrderFile;
        QMainWindow * wid = new QMainWindow(this);
        wid->setWindowTitle("我的预约信息");
        wid->setFixedSize(800,500);
        QTextEdit * edit = new QTextEdit(wid);
        edit->setFixedSize(wid->width(),wid->height());



                QString s;
                bool flag=false;
                for (int i = 0; i < of->m_Size; i++)
                {
                    if (stu->m_Name == of->m_orderData[i][2]) //找到自身预约
                    {
                        flag=true;
                        s="预约日期："+ of->m_orderData[i][0] + "| 时间段:"+of->m_orderData[i][1]+" | 机房编号:"+of->m_orderData[i][3]+" | 预约状态:"+of->m_orderData[i][4]+"\n";
                        edit->append(s);
                        s="*******************************************************\n";
                        edit->append(s);
                    }
                }
                if(flag)
                {
                    QFont fon;
                    fon.setFamily("华文新魏");
                    fon.setPointSize(15);
                    edit->setFont(fon);
                     edit->setReadOnly(true);
                    wid->show();
                    edit->show();


                }
                else
                {
                    msgBox.setIcon(QMessageBox::Information);
                    msgBox.setText("无预约记录");
                    msgBox.exec();
                }

            delete of;
            of=NULL;


    }


}
void StudentWindow::CancelOrder(OrderFile*of,Student* stu)
{

     QVector<int>v; //存放在最大容器中的下标编号
     for (int i = 0; i < of->m_Size; i++)
     {
         //先判断是自身学号
         if (stu->m_Name== of->m_orderData[i][2])
         {
             //再筛选状态  审核中或预约成功
             if (of->m_orderData[i][4] == "审核中" || of->m_orderData[i][4] == "预约成功")
             {
                 v.push_back(i);
             }
         }
     }
    QMessageBox msgBox;
    bool ok;
    int i = QInputDialog::getInt(this, "输入要取消的记录", "记录编号:",1, 1, v.size(),1, &ok);
          if (ok)
          {

               QString s="预约已取消";

              of->m_orderData[v[i - 1]][4] =s ;

              of->updateOrder();
              msgBox.setText("成功取消预约");
              msgBox.exec();
              delete of;
              of=NULL;
              //一旦成功取消了某个预约就将界面返回到学生主界面，并将文本框中的内容清空
              ui->stackedWidget->setCurrentIndex(0);
              ui->textEdit->clear();
          }

}

//取消预约
void StudentWindow::configCancelOrder( OrderFile  * of,Student* stu)
{


          int index = 1;
          QString s;
          for (int i = 0; i < of->m_Size; i++)
          {
              //先判断是自身学号
              if (stu->m_Name== of->m_orderData[i][2])
              {
                  //再筛选状态  审核中或预约成功
                  if (of->m_orderData[i][4] == "审核中" || of->m_orderData[i][4] == "预约成功")
                  {

                      s.append(QString::number(index));

                      index++;
                      QString t = ": 预约日期:"+of->m_orderData[i][0]+" | 时间段:"+of->m_orderData[i][1]+" | 机房编号:"+of->m_orderData[i][3]+" | 状态:"+of->m_orderData[i][4]+"\n";
                      s.append(t);
                     ui->textEdit->append(s);
                     s.clear();
                  }
              }
          }

          if(index==1)
          {
              QMessageBox msgBox;
              msgBox.setIcon(QMessageBox::Information);
              msgBox.setText("无可以取消的预约记录");
              msgBox.exec();
              delete of;
              of=NULL;
          }
          else
          {
              ui->textEdit->setReadOnly(true);
              //只有在有可以取消的预约记录情况下才显示页面
              ui->stackedWidget->setCurrentIndex(2);
          }






}

//查看所有预约
void StudentWindow::showAllOrder(OrderFile*of)
{

    QFile ex;
    QMessageBox msgBox;
    if(!ex.exists("order.txt"))
    {
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("无预约记录");
        msgBox.exec();
    }
    else
    {

        of=new OrderFile;
       QMessageBox msgBox;
       QMainWindow * wid = new QMainWindow(this);
       wid->setWindowTitle("所有预约信息");
       wid->setFixedSize(800,500);
       QTextEdit * edit = new QTextEdit(wid);
       edit->setFixedSize(wid->width(),wid->height());
       if (of->m_Size == 0)
       {
           msgBox.setIcon(QMessageBox::Information);
           msgBox.setText("无预约记录");
           msgBox.exec();

       }
       else
       {
           QString s;
           for (int i = 0; i < of->m_Size; i++)
           {
               s="预约日期："+ of->m_orderData[i][0] + " | 时间段:"+of->m_orderData[i][1]+" | 学号:"+of->m_orderData[i][2]+" | 机房号:"+of->m_orderData[i][3]+" | 预约状态:"+of->m_orderData[i][4]+"\n";
               edit->append(s);
               s="****************************************************\n";
               edit->append(s);
           }
           QFont fon;
           fon.setFamily("华文新魏");
           fon.setPointSize(15);
           edit->setFont(fon);
            edit->setReadOnly(true);
           wid->show();
           edit->show();
       }

        delete of;
          of=NULL;
    }


}
StudentWindow::~StudentWindow()
{
    delete ui;
}
