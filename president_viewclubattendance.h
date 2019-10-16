#ifndef PRESIDENT_VIEWCLUBATTENDANCE_H
#define PRESIDENT_VIEWCLUBATTENDANCE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class president_ViewClubAttendance;
}

class president_ViewClubAttendance : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit president_ViewClubAttendance(QWidget *parent = 0);
    ~president_ViewClubAttendance();

private slots:

    void on_tableView_ClubAttendance_activated(const QModelIndex &index);

    void on_pushButton_Save_clicked();

    void on_pushButton_Back_clicked();

    void on_comboBox_ClubChoice_currentIndexChanged(const QString &arg1);

    void on_comboBox_DateChoice_currentIndexChanged(const QString &arg1);

private:
    Ui::president_ViewClubAttendance *ui;
};

#endif // PRESIDENT_VIEWCLUBATTENDANCE_H
