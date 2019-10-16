#ifndef PRESIDENT_ADDMEMBER_H
#define PRESIDENT_ADDMEMBER_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class president_AddMember;
}

class president_AddMember : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit president_AddMember(QWidget *parent = 0);
    ~president_AddMember();

private slots:
    void on_pushButton_Back_clicked();

private:
    Ui::president_AddMember *ui;
};

#endif // PRESIDENT_ADDMEMBER_H
