#ifndef PRESIDENT_ADDNEWCLUBMEETING_H
#define PRESIDENT_ADDNEWCLUBMEETING_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class president_AddNewClubMeeting;
}

class president_AddNewClubMeeting : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit president_AddNewClubMeeting(QWidget *parent = 0);
    ~president_AddNewClubMeeting();

private slots:
    void on_calendarWidget_activated(const QDate &date);

    void on_pushButton_Save_clicked();

    void on_comboBox_Clubs_activated(const QString &arg1);

    void on_pushButton_Back_clicked();

private:
    Ui::president_AddNewClubMeeting *ui;
    QList<int>* StudentIDList = new QList<int>();
};

#endif // PRESIDENT_ADDNEWCLUBMEETING_H
