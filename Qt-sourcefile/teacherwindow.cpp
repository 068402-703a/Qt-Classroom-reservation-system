#include "teacherwindow.h"
#include "ui_teacherwindow.h"
#include <QMessageBox>
#include <QTextEdit>
#include <QVector>
#include <QString>
#include <QInputDialog>
TeacherWindow::TeacherWindow(Teacher * tea,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherWindow)
{
    ui->setupUi(this);
    ui->setupUi(this);
    this->setFixedSize(800,500);
    this->setWindowTitle("欢迎登陆机房预约系统");
    //点击注销登录按钮后返回主界面
    connect(ui->exitButton,&QPushButton::clicked,[=](){
        this->hide();
        emit teacherWindowBack();
    });
    //点击查看所有预约按钮查看所有预约
    connect(ui->checkallpushButton,&QPushButton::clicked,[=](){
        of=new OrderFile;
       showAllOrder(of);
    });
    //在取消预约界面选择返回按钮就返回学生主界面
    connect(ui->exitpushButton,&QPushButton::clicked,[=](){
        delete of;
        of=NULL;
       ui->stackedWidget->setCurrentIndex(0);
       ui->textEdit->clear();

    });

    //连接审核预约界面的选择按钮

    connect(ui->choosepushButton,&QPushButton::clicked,[=](){

      ValidOrder(of);
    });
    //在学生主界面点击取消预约按钮去到取消预约的界面
    connect(ui->shenhepushButton,&QPushButton::clicked,[=](){
          of = new OrderFile;
        configValidOrder(of);
    });

}

TeacherWindow::~TeacherWindow()
{
    delete ui;
}
void  TeacherWindow::showAllOrder(OrderFile * of)
{
    QMessageBox msgBox;
    QMainWindow * wid = new QMainWindow(this);
    wid->setWindowTitle("所有预约信息");
    wid->setFixedSize(320,500);
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
            s="预约日期："+ of->m_orderData[i][0] + " 时间段： "+of->m_orderData[i][1]+" 学号： "+of->m_orderData[i][2]+"\n 机房号： "+of->m_orderData[i][3]+"   预约状态： "+of->m_orderData[i][4]+"\n";
            edit->append(s);
            s="*********************\n";
            edit->append(s);
           /*
            string status = " 状态：";
            // 1 审核中 2 已预约  -1预约失败  0 取消预约
            if (of.m_orderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            else if (of.m_orderData[i]["status"] == "2")
            {
                status += "预约成功";
            }
            else if (of.m_orderData[i]["status"] == "-1")
            {
                status += "预约失败，审核未通过";
            }
            else
            {
                status += "预约已取消";
            }
            cout << status << endl;
            */
        }
        wid->show();
        edit->show();
    }

     delete of;
       of=NULL;
}
 void TeacherWindow::ValidOrder(OrderFile * of)
 {
      QVector<int>v; //存放在最大容器中的下标编号
      for (int i = 0; i < of->m_Size; i++)
      {

              //再筛选状态  审核中
              if (of->m_orderData[i][4] == "审核中" )
              {
                  v.push_back(i);
              }
       }

     QMessageBox msgBox;
     bool ok;
     int i = QInputDialog::getInt(this, "输入要审核的记录", "记录编号:",1, 1, v.size(),1, &ok);
           if (ok)
           {

         int ret = QMessageBox::question(this, "记录审核", "是否通过该预约?", QMessageBox::Yes| QMessageBox::No);
        QString s;
         switch (ret) {
             case QMessageBox::Yes:
                 // Save was clicked
             s="预约成功";

            of->m_orderData[v[i - 1]][4] =s ;

                 break;
         case QMessageBox::No:
                 // Don't Save was clicked
              s=" 预约失败，审核未通过";

            of->m_orderData[v[i - 1]][4] =s ;

                 break;
           }
             of->updateOrder();

             msgBox.setText("审核完毕");
             msgBox.exec();
             delete of;
             of=NULL;
             //一旦审核完毕就将界面返回到老师主界面，并将文本框中的内容清空
             ui->stackedWidget->setCurrentIndex(0);
             ui->textEdit->clear();





           }


 }
//审核预约
void TeacherWindow::configValidOrder(OrderFile * of)
{

       QMessageBox msgBox;
        if (of->m_Size == 0)
        {
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("无预约记录");
            msgBox.exec();
            delete of;
            of=NULL;
        }
        else
        {

            int index = 1;
            QString s;
            for (int i = 0; i < of->m_Size; i++)
            {
                if (of->m_orderData[i][4] == "审核中")
                {

                    s.append(QString::number(index));
                    index++;

                    QString t = ": 预约日期: "+of->m_orderData[i][0]+" 时间段： "+of->m_orderData[i][1]+"  学生学号  " +of->m_orderData[i][2]+" 机房编号： "+of->m_orderData[i][3]+" 状态： "+of->m_orderData[i][4]+"\n";
                    s.append(t);
                   ui->textEdit->append(s);
                   s.clear();

                }
            }
            if(index==1)
            {
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("没有需要审核的预约记录");
                msgBox.exec();
                delete of;
                of=NULL;
            }
            else
            {
                //当审核预约界面配置好以后,就可以让它显示出来了
                ui->stackedWidget->setCurrentIndex(1);
            }

        }


}
