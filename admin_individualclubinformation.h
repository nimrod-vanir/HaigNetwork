#ifndef ADMIN_INDIVIDUALCLUBINFORMATION_H
#define ADMIN_INDIVIDUALCLUBINFORMATION_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class admin_IndividualClubInformation;
}

class admin_IndividualClubInformation : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit admin_IndividualClubInformation(QWidget *parent = 0);
    ~admin_IndividualClubInformation();

private slots:
    void on_listWidget_ClubList_activated(const QModelIndex &index);

    void on_pushButton_Back_clicked();

private:
    Ui::admin_IndividualClubInformation *ui;
};

#endif // ADMIN_INDIVIDUALCLUBINFORMATION_H
