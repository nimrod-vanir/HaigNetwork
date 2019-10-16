#ifndef ADMIN_CREATEACLUB_H
#define ADMIN_CREATEACLUB_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class admin_CreateAClub;
}

class admin_CreateAClub : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit admin_CreateAClub(QWidget *parent = 0);
    ~admin_CreateAClub();

private slots:
    void on_pushButton_SaveClub_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::admin_CreateAClub *ui;
};

#endif // ADMIN_CREATEACLUB_H
