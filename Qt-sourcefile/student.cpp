#include "student.h"
#include <QMessageBox>
#include <QTextStream>
Student::Student(QObject *parent) : QObject(parent)
{

}
//有参构造  参数：学号、姓名、密码
Student::Student(QString name, QString pwd)
{
    this->m_Name = name;
    this->m_Pwd = pwd;
    //初始化机房信息,如果机房信息文件还不存在,就先创建并初始化
    QFile ifs("computerRoom.txt");
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





