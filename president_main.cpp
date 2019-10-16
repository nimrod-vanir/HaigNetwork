//include required header files and libraries
#include "president_main.h"
#include "ui_president_main.h"
#include "president_viewclubattendance.h"
#include "president_addnewclubmeeting.h"
#include "president_addmember.h"
#include "president_removemembers.h"
#include "addstudenttoclub.h"
#include "createnewstudent.h"

president_main::president_main(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::president_main)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);
    ui->pushButton_AddNewClubMeeting_1->setIcon(QIcon(":/pngs/Resources/addIcon.png"));
    ui->pushButton_AddStudent_2->setIcon(QIcon(":/pngs/Resources/addIcon.png"));
    ui->pushButton_EditClubAttendance->setIcon(QIcon(":/pngs/Resources/listIcon.png"));
}

president_main::~president_main()
{
    //function called when window is closed

    delete ui;
}

void president_main::on_pushButton_AddStudent_2_clicked()
{
    // function is called when 'AddStudent' button is clicked ******

    this->close();

    AddStudentToClub AddStudentToClub_pointer;
    AddStudentToClub_pointer.setModal(true);
    AddStudentToClub_pointer.exec();
}

void president_main::on_pushButton_AddNewClubMeeting_1_clicked()
{
    // function is called when 'AddNewClubMeeting' button is clicked ********

    this->close();

    president_AddNewClubMeeting president_AddNewClubMeeting_pointer;
    president_AddNewClubMeeting_pointer.setModal(true);
    president_AddNewClubMeeting_pointer.exec();
}

void president_main::on_pushButton_EditClubAttendance_clicked()
{
    // function is called when 'ViewClubAttendance' button is clicked *******

    this->close();

    president_ViewClubAttendance president_ViewClubAttendance_pointer;
    president_ViewClubAttendance_pointer.setModal(true);
    president_ViewClubAttendance_pointer.exec();
}
