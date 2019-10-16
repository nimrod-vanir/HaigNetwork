//include required header files and librariess
#include "president_editclubattendance.h"
#include "ui_president_editclubattendance.h"

president_EditClubAttendance::president_EditClubAttendance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::president_EditClubAttendance)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);
}

president_EditClubAttendance::~president_EditClubAttendance()
{
    //function called when window is closed

    delete ui;
}
