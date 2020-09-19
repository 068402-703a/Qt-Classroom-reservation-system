#ifndef ORDERFILE_H
#define ORDERFILE_H

#include <QObject>
#include <QFile>
#include <QMap>
#include <QString>
#include <QVector>
class OrderFile : public QObject
{
    Q_OBJECT
public:
     OrderFile(QObject *parent = nullptr);
    //更新预约记录
    void updateOrder();

    //记录预约条数
    int m_Size;

    //记录所有预约信息的容器  key记录条数   value 具体记录键值对信息
    QMap<int, QVector<QString>> m_orderData;

signals:

public slots:
};

#endif // ORDERFILE_H
