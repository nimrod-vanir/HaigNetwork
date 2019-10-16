#ifndef CREATENEWSTUDENT_H
#define CREATENEWSTUDENT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class CreateNewStudent;
}

class CreateNewStudent : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit CreateNewStudent(QWidget *parent = 0);
    ~CreateNewStudent();

private slots:
    void on_pushButton_Save_clicked();

private:
    Ui::CreateNewStudent *ui;
};

#endif // CREATENEWSTUDENT_H
