#ifndef ADMIN_LISTOFCLUBS_H
#define ADMIN_LISTOFCLUBS_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class admin_ListOfClubs;
}

class admin_ListOfClubs : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit admin_ListOfClubs(QWidget *parent = 0);
    ~admin_ListOfClubs();

private slots:

    void on_tableView_ListOfClub_activated(const QModelIndex &index);

    void on_pushButton_Save_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_OpenIndividualClub_clicked();

private:
    Ui::admin_ListOfClubs *ui;
};

#endif // ADMIN_LISTOFCLUBS_H
