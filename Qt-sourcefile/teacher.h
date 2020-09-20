#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>
#include <QString>
#include <QVector>

class Teacher : public QObject
{
    Q_OBJECT
public: //默认构造
    Teacher(QObject *parent = nullptr);

    //有参构造
    Teacher( QString name, QString pwd);


   QString m_Name;
   QString m_Pwd;


signals:

public slots:
};

#endif // TEACHER_H
