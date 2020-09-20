#include "studentwindow.h"
#include "ui_studentwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextEdit>

#include <QInputDialog>
StudentWindow::StudentWindow(Student* stu,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,500);
    this->setWindowTitle("欢迎登陆机房预约系统");
    //进来时，默认是学生主界面
    ui->stackedWidget->setCurrentIndex(0);
    //点击注销登录按钮后返回主界面
    connect(ui->exitButton,&QPushButton::clicked,[=](){
        this->hide();
        emit studentWindowBack();
    });
    //点击预约机房按钮，进到预约机房界面
    connect(ui->reservepushButton,&QPushButton::clicked,[=](){
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
        of=new OrderFile;
       showMyOrder(of,stu);
    });
    //在申请预约界面点击查看所有预约按钮完成对所有预约的查看
    connect(ui->checkallrespushButton,&QPushButton::clicked,[=](){
        of=new OrderFile;
       showAllOrder(of);
    });
    //在学生主界面点击取消预约按钮去到取消预约的界面
    connect(ui->cancelpushButton,&QPushButton::clicked,[=](){
          of = new OrderFile;
        configCancelOrder(of,stu);
    });
    //在取消预约界面选择返回按钮就返回学生主界面
    connect(ui->cancelexitpushButton,&QPushButton::clicked,[=](){
        delete of;
        of=NULL;
       ui->stackedWidget->setCurrentIndex(0);
       ui->textEdit->clear();

    });

    //在切换到页面后，就连接选择按钮

    connect(ui->choosepushButton,&QPushButton::clicked,[=](){

        CancelOrder(of, stu);
    });

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
      QMessageBox msgBox;

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
        QString status="审核中";
        out << date << " "<< interval << " "<< stu->m_Name << " "<< room << " "<<status<<"\n";
        ofs.close();
}
//查看自身预约
void StudentWindow::showMyOrder(OrderFile*of,Student* stu)
{
    QMainWindow * wid = new QMainWindow(this);
    wid->setWindowTitle("我的预约信息");
    wid->setFixedSize(320,500);
    QTextEdit * edit = new QTextEdit(wid);
    edit->setFixedSize(wid->width(),wid->height());

        QMessageBox msgBox;
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
                if (stu->m_Name == of->m_orderData[i][2]) //找到自身预约
                {
                    s="预约日期："+ of->m_orderData[i][0] + "  时间段： "+of->m_orderData[i][1]+"   机房编号： "+of->m_orderData[i][3]+"\n 预约状态： "+of->m_orderData[i][4]+"\n";
                    edit->append(s);
                    s="************************\n";
                    edit->append(s);
                    /*
                    string status = "状态： ";
                    // 1 审核中  2 已预约  -1 预约失败  0 取消预约
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
            }
            wid->show();
            edit->show();

        }
        delete of;
        of=NULL;


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
                //先判断是自身学号
                if (stu->m_Name== of->m_orderData[i][2])
                {
                    //再筛选状态  审核中或预约成功
                    if (of->m_orderData[i][4] == "审核中" || of->m_orderData[i][4] == "预约成功")
                    {

                        s.append(QString::number(index));

                        index++;
                        QString t = ": 预约日期: "+of->m_orderData[i][0]+" 时间段： "+of->m_orderData[i][1]+" 机房编号： "+of->m_orderData[i][3]+" 状态： "+of->m_orderData[i][4]+"\n";
                        s.append(t);
                       ui->textEdit->append(s);
                       s.clear();
                    }
                }
            }

            if(index==1)
            {
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("无可以取消的预约记录");
                msgBox.exec();
                delete of;
                of=NULL;
            }
            else
            {
                //只有在有可以取消的预约记录情况下才显示页面
                ui->stackedWidget->setCurrentIndex(2);
            }
        }




}

//查看所有预约
void StudentWindow::showAllOrder(OrderFile*of)
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
StudentWindow::~StudentWindow()
{
    delete ui;
}
