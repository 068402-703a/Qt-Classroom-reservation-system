#include "manager.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
Manager::Manager(QObject *parent) : QObject(parent)
{

}


//有参构造
Manager::Manager(QString name, QString pwd)
{
    //初始化管理员信息
    this->m_Name = name;
    this->m_Pwd = pwd;

    //初始化容器 获取到所有文件中 学生、老师信息
    this->initVector();  
    //初始化机房信息,如果机房信息文件还不存在,就先创建并初始化
    QFile ifs;
    if(!ifs.exists("computerRoom.txt"))
    {
        creatComputerRoom();
    }
     ifs.setFileName("computerRoom.txt");
     if(!ifs.open(QIODevice::ReadOnly|QIODevice::Text))
     {
         QMessageBox msgBox;
         msgBox.setIcon(QMessageBox::Critical);
         msgBox.setText("打开文件失败");
         msgBox.exec();
         exit(0);
     }
     ComputerRoom com;
     QTextStream in(&ifs);
           while (!in.atEnd()) {

               QString line = in.readLine();

               QStringList list=line.split('&',QString::SkipEmptyParts);

               line=list[0];
               com.m_ComId=line.toInt();
               line=list[1];
               com.m_MaxNum=line.toInt();
               vCom.push_back(com);
           }
    ifs.close();

}
void Manager::creatComputerRoom()
{
    QFile tempFile("computerRoom.txt");

        if(!tempFile.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("打开文件失败");
            msgBox.exec();
            exit(0);
        }
        QTextStream out(&tempFile);
        out << "1" <<"&"<< "50"<<"\n";
        out << "2" <<"&"<< "70"<<"\n";
        out << "3" <<"&"<< "100"<<"\n";

        tempFile.close();
}


QString Manager::printStudent(Student * t)
{
    QString s =QString("学号：%1  密码：%2\n").arg(t->m_Name).arg(t->m_Pwd);
    return s;

}
QString Manager::printTeacher(Teacher * t)
{
    QString s =QString("职工号：%1  密码：%2\n").arg(t->m_Name).arg(t->m_Pwd);
    return s;
}







//初始化容器
void Manager::initVector()
{
    //确保容器清空状态
    vStu.clear();
    vTea.clear();
    QMessageBox msgBox;
    //读取信息   学生
    QFile ifs("student.txt");
    if(!ifs.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
    }
    Student * s;
    QTextStream in(&ifs);
         while (!in.atEnd()) {
             s=new Student;
             QString line = in.readLine();

             QStringList list = line.split('&',QString::SkipEmptyParts);
             s->m_Name=list[0];
             s->m_Pwd=list[1];
             vStu.push_back(s);
         }
            ifs.close();


    //读取信息   老师
           QFile ofs("teacher.txt");
            if(!ofs.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setText("打开文件失败");
                msgBox.exec();
            }
            Teacher* t;
            QTextStream on(&ofs);
                 while (!on.atEnd()) {
                     t=new Teacher;
                     QString line = on.readLine();

                     QStringList list = line.split('&',QString::SkipEmptyParts);
                     t->m_Name=list[0];
                     t->m_Pwd=list[1];
                     vTea.push_back(t);
                 }
            ofs.close();
}

//检测重复 参数1 检测学号/职工号  参数2  检测类型
bool Manager::checkRepeat(QString name, int type)
{

    if (type == 0)
    {
        //检测学生
        for (int i = 0; i < vStu.size(); ++i) {
              if (vStu.at(i)->m_Name == name)
                 return true;
          }
    }
    else
    {
        //检测老师
        for (int i = 0; i < vTea.size(); ++i) {
              if (vTea.at(i)->m_Name == name)
                 return true;
          }

    }

   return false;
}
