#ifndef REGISTERINTERFACE_H
#define REGISTERINTERFACE_H

#include <QMainWindow>
#include <QString>
#include "studentwindow.h"
#include "teacherwindow.h"
#include "managerwindow.h"
namespace Ui {
class RegisterInterface;
}

class RegisterInterface : public QMainWindow
{
    Q_OBJECT

public:

    explicit RegisterInterface(QWidget *parent = 0);
    ~RegisterInterface();
    void paintEvent(QPaintEvent *event);
    void LoginIn(QString fileName, int type);
     StudentWindow * stuWindow = NULL;
    TeacherWindow * teaWindow = NULL;
    ManagerWindow * manWindow =NULL;
    void createManagerInfo();
private:
    Ui::RegisterInterface *ui;
};

#endif // REGISTERINTERFACE_H
