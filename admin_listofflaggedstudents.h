#ifndef ADMIN_LISTOFFLAGGEDSTUDENTS_H
#define ADMIN_LISTOFFLAGGEDSTUDENTS_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class admin_ListOfFlaggedStudents;
}

class admin_ListOfFlaggedStudents : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit admin_ListOfFlaggedStudents(QWidget *parent = 0);
    ~admin_ListOfFlaggedStudents();

private slots:
    void on_comboBox_selectedClub_currentIndexChanged(const QString &arg1);

    void on_pushButton_Back_clicked();

private:
    Ui::admin_ListOfFlaggedStudents *ui;
};

#endif // ADMIN_LISTOFFLAGGEDSTUDENTS_H
