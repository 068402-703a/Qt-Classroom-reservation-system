#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>

#include "teacher.h"
namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherWindow(Teacher * tea,QWidget *parent = 0);
    ~TeacherWindow();
signals:
     void teacherWindowBack();
private:
    Ui::TeacherWindow *ui;
};

#endif // TEACHERWINDOW_H
