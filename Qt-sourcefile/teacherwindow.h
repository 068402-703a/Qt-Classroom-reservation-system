#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>

#include "orderfile.h"
#include "teacher.h"
namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    OrderFile * of=NULL;
    explicit TeacherWindow(QWidget *parent = 0);
    void showAllOrder(OrderFile * of);
    //审核预约
    void configValidOrder(OrderFile * of);
    void ValidOrder(OrderFile * of);
    void paintEvent(QPaintEvent *event);
    ~TeacherWindow();
signals:
     void teacherWindowBack();
private:
    Ui::TeacherWindow *ui;
};

#endif // TEACHERWINDOW_H
