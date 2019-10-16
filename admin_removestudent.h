#ifndef ADMIN_REMOVESTUDENT_H
#define ADMIN_REMOVESTUDENT_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class admin_RemoveStudent;
}

class admin_RemoveStudent : public QDialog
{
    Q_OBJECT

public:
    MainWindow MainWindow_Class;
    explicit admin_RemoveStudent(QWidget *parent = 0);
    ~admin_RemoveStudent();

private slots:
    void on_comboBox_club_activated(const QString &arg1);

    void on_pushButton_Back_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::admin_RemoveStudent *ui;
    QList<int>* studentToRemove = new QList<int>();
    int clubToRemove;
};

#endif // ADMIN_REMOVESTUDENT_H
