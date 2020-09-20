#include "teacher.h"

Teacher::Teacher(QObject *parent) : QObject(parent)
{

}

//有参构造
Teacher::Teacher( QString name, QString pwd)
{
    //初始化属性

    this->m_Name = name;
    this->m_Pwd = pwd;
}

