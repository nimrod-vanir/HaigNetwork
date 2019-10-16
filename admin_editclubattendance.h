#ifndef ADMIN_EDITCLUBATTENDANCE_H
#define ADMIN_EDITCLUBATTENDANCE_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include "mainwindow.h"

namespace Ui {
class Admin_EditClubAttendance;
}

class Admin_EditClubAttendance : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit Admin_EditClubAttendance(QWidget *parent = 0);
    ~Admin_EditClubAttendance();

private slots:

    void on_listWidget_pick_club_activated(const QModelIndex &index);

    void on_listWidget_pick_meet_activated(const QModelIndex &index);

    void on_tableWidget_students_activated(const QModelIndex &index);

    void on_pushButton_Save_clicked();

    void on_pushButton_revert_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::Admin_EditClubAttendance *ui;
    QStandardItemModel *model;

    QList<int>* clubIDList = new QList<int>();
    QList<int>* meetIDList = new QList<int>();
    QList<int>* studentIDlist = new QList<int>();
    QList<QString>* presenceListREVsave = new QList<QString>();

    void init_table();
    QString stdID2NAME(QString stdID);
    int stdNAME2ID(QString stdName);
    bool save(QString action);
    QList<int>* find_active_clubs(bool display_clubs);
    QList<int>* find_meets_of_clubs(QString clubID, bool display_meets);
    QList<int>* find_student_attendance(QString meetID, bool display_attends);
};

#endif // ADMIN_EDITCLUBATTENDANCE_H
