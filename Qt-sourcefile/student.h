#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QString>
#include <QVector>
#include "computerRoom.h"
#include <QFile>
#include "orderFile.h"
class Student : public QObject
{
    Q_OBJECT
public:
    //默认构造
     Student(QObject *parent = nullptr);

    //有参构造  参数：学号、姓名、密码
    Student(QString name,QString pwd);



    //申请预约
    void applyOrder();

    //查看自身预约
    void showMyOrder();

    //查看所有预约
    void showAllOrder();

    //取消预约
    void cancelOrder();

    //学生学号
    QString m_Name;
    //学生密码

      QString m_Pwd;

    //机房容器
    QVector<ComputerRoom> vCom;

signals:

public slots:
};

#endif // STUDENT_H
