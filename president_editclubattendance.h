#ifndef PRESIDENT_EDITCLUBATTENDANCE_H
#define PRESIDENT_EDITCLUBATTENDANCE_H

#include <QDialog>

namespace Ui {
class president_EditClubAttendance;
}

class president_EditClubAttendance : public QDialog
{
    Q_OBJECT

public:
    explicit president_EditClubAttendance(QWidget *parent = 0);
    ~president_EditClubAttendance();

private:
    Ui::president_EditClubAttendance *ui;
};

#endif // PRESIDENT_EDITCLUBATTENDANCE_H
