#ifndef ADMIN_ADDUSER_H
#define ADMIN_ADDUSER_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class admin_AddUser;
}

class admin_AddUser : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit admin_AddUser(QWidget *parent = 0);
    ~admin_AddUser();

private slots:
    void on_pushButton_Save_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::admin_AddUser *ui;
};

#endif // ADMIN_ADDUSER_H
