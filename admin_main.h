#ifndef ADMIN_MAIN_H
#define ADMIN_MAIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class admin_main;
}

class admin_main : public QDialog
{
    Q_OBJECT

public:
    explicit admin_main(QWidget *parent = 0);
    ~admin_main();

private slots:
    void on_pushButton_CreateAClub_clicked();

    void on_pushButton_ListOfClubs_clicked();

    void on_pushButton_ListOfFlaggedStudents_clicked();

    void on_pushButton_RemoveStudent_clicked();

    void on_pushButton_EditClubAttendance_clicked();

    void on_pushButton_AddStudent_clicked();

    void on_pushButton_IndividualClubInformation_clicked();

    void on_pushButton_AddUser_clicked();

private:
    Ui::admin_main *ui;
};

#endif // ADMIN_MAIN_H
