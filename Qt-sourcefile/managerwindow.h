#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include "manager.h"
namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(Manager*man,QWidget *parent = 0);
    ~ManagerWindow();
    //添加账号
    void addPerson(Manager * man);
    //查看账号
    void showPerson(Manager * man,int type);
    //查看机房信息
    void showComputer(Manager * man);
    //清空预约记录
    void cleanFile();
signals:

   void managerWindowBack();

private:
    Ui::ManagerWindow *ui;
};

#endif // MANAGERWINDOW_H
