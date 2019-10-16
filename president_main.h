#ifndef PRESIDENT_MAIN_H
#define PRESIDENT_MAIN_H

#include <QDialog>

namespace Ui {
class president_main;
}

class president_main : public QDialog
{
    Q_OBJECT

public:
    explicit president_main(QWidget *parent = 0);
    ~president_main();

private slots:

    void on_pushButton_AddStudent_2_clicked();

    void on_pushButton_AddNewClubMeeting_1_clicked();

    void on_pushButton_EditClubAttendance_clicked();

private:
    Ui::president_main *ui;
};

#endif // PRESIDENT_MAIN_H
