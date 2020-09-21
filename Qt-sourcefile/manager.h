#ifndef MANAGER_H
#define MANAGER_H
#include <QObject>
#include <QString>
#include <QFile>
#include <QVector>
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"
class Manager : public QObject
{
    Q_OBJECT
public:
     Manager(QObject *parent = nullptr);

    //有参构造
    Manager(QString name ,QString pwd);

    QString printStudent(Student * t);
    QString printTeacher(Teacher * t);


    //初始化容器
    void initVector();

    //检测重复 参数1 检测学号/职工号  参数2  检测类型
    bool checkRepeat(QString name , int type);
    //在机房信息文件还不存在时创建机房文件并给一定的初始信息
   void creatComputerRoom();
    //学生容器
    QVector<Student*>vStu;

    //教师容器
    QVector<Teacher*>vTea;

    //机房信息容器
    QVector<ComputerRoom>vCom;
    //管理员的用户名和密码
    QString m_Name ;
    QString m_Pwd ;

signals:

public slots:
};

#endif // MANAGER_H
