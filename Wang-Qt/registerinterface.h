#ifndef REGISTERINTERFACE_H
#define REGISTERINTERFACE_H

#include <QMainWindow>

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
private:
    Ui::RegisterInterface *ui;
};

#endif // REGISTERINTERFACE_H
