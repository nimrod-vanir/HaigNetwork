#ifndef ADDSTUDENTTOCLUB_H
#define ADDSTUDENTTOCLUB_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class AddStudentToClub;
}

class AddStudentToClub : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit AddStudentToClub(QWidget *parent = 0);
    ~AddStudentToClub();

private slots:
    void on_pushButton_Save_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::AddStudentToClub *ui;
};

#endif // ADDSTUDENTTOCLUB_H
