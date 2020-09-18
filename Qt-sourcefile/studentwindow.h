#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include "student.h"
namespace Ui {
class StudentWindow;
}

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(Student* stu,QWidget *parent = 0);
    ~StudentWindow();
signals:
    void studentWindowBack();
private:
    Ui::StudentWindow *ui;

};

#endif // STUDENTWINDOW_H
