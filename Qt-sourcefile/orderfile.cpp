#include "orderfile.h"
#include <QFile>
#include<QTextStream>
#include<QMessageBox>
#include <QDebug>
OrderFile::OrderFile(QObject *parent) : QObject(parent)
{
   QFile ifs("order.txt");
   QMessageBox msgBox;
   if(!ifs.open(QIODevice::ReadOnly|QIODevice::Text))
    {

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
        exit(0);
    }
    this->m_Size = 0; //记录条数
    QTextStream in(&ifs);
          while (!in.atEnd()) {
              QVector<QString>m;
              QString line = in.readLine();
              QStringList list = line.split(' ',QString::SkipEmptyParts);
              m.push_back(list[0]);
              m.push_back(list[1]);
              m.push_back(list[2]);
              m.push_back(list[3]);
              m.push_back(list[4]);
                  //将小vector容器放入到大的map容器中

                  this->m_orderData.insert(this->m_Size, m);
                  this->m_Size++;
          }
    ifs.close();

    //测试最大map容器
    //for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
    //{
    //	cout << "条数为： " << it->first << " value = " << endl;
    //	for (map<string, string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
    //	{
    //		cout << " key = " << mit->first << " value = " << mit->second << " ";
    //	}
    //	cout << endl;
    //}

}



//更新预约记录
void OrderFile::updateOrder()
{
    if (this->m_Size == 0)
    {
        return; //预约记录0条，直接return
    }
    QFile ofs("order.txt");
    QMessageBox msgBox;
    if(!ofs.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
        exit(0);
    }
    QTextStream out(&ofs);
    for (int i = 0; i < this->m_Size; i++)
    {
        out << this->m_orderData[i][0]<< " ";
        out << this->m_orderData[i][1] << " ";
        out <<this->m_orderData[i][2] << " ";
        out << this->m_orderData[i][3] << " ";
        out << this->m_orderData[i][4] << "\n";

    }

    ofs.close();
}
