#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "student.h"
#include "orderfile.h"
namespace Ui {
class StudentWindow;
}

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
     OrderFile *  of = NULL;
    explicit StudentWindow(Student* stu,QWidget *parent = 0);
    //申请预约
    void applyOrder(Student* stu);
    //查看自身预约
    void showMyOrder(OrderFile*of,Student* stu);

    //查看所有预约
    void showAllOrder(OrderFile*of);

    //取消预约
    void configCancelOrder( OrderFile  * of,Student* stu);
    void CancelOrder(OrderFile *of,Student* stu);
    void paintEvent(QPaintEvent *event);
    ~StudentWindow();
signals:
    void studentWindowBack();

private:
    Ui::StudentWindow *ui;

};

#endif // STUDENTWINDOW_H
