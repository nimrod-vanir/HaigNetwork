//include required header files and libraries
#include "admin_main.h"
#include "ui_admin_main.h"
#include "admin_createaclub.h"
#include "admin_listofclubs.h"
#include "admin_listofflaggedstudents.h"
#include "admin_removestudent.h"
#include "mainwindow.h"
#include "admin_editclubattendance.h"
#include "admin_individualclubinformation.h"
#include "addstudenttoclub.h"
#include "createnewstudent.h"

#include "admin_adduser.h"

admin_main::admin_main(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_main)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);    
    ui->pushButton_CreateAClub->setIcon(QIcon(":/pngs/Resources/addIcon.png"));
    ui->pushButton_AddStudent->setIcon(QIcon(":/pngs/Resources/addIcon.png"));
    ui->pushButton_AddUser->setIcon(QIcon(":/pngs/Resources/addIcon.png"));
    ui->pushButton_ListOfClubs->setIcon(QIcon(":/pngs/Resources/listIcon.png"));
    //ui->pushButton_IndividualClubInformation->setIcon(QIcon(":/pngs/listIcon.png"));
    ui->pushButton_ListOfFlaggedStudents->setIcon(QIcon(":/pngs/Resources/listIcon.png"));
    ui->pushButton_EditClubAttendance->setIcon(QIcon(":/pngs/Resources/listIcon.png"));
    ui->pushButton_RemoveStudent->setIcon(QIcon(":/pngs/Resources/subtractIcon.png"));
}

admin_main::~admin_main()
{
    //function called when window is closed

    delete ui;
}

void admin_main::on_pushButton_CreateAClub_clicked()
{
    // function is called when 'CreateAClub' button is clicked

    this->close();

    admin_CreateAClub admin_CreateAClub_pointer;
    admin_CreateAClub_pointer.setModal(true);
    admin_CreateAClub_pointer.exec();
}

void admin_main::on_pushButton_ListOfClubs_clicked()
{
    // function is called when 'ListOfClubs' button is clicked

    this->close();

    admin_ListOfClubs admin_ListOfClubs_pointer;
    admin_ListOfClubs_pointer.setModal(true);
    admin_ListOfClubs_pointer.exec();
}

void admin_main::on_pushButton_ListOfFlaggedStudents_clicked()
{
    // function is called when 'ListOfFlaggedStudents' button is clicked

    this->close();

    admin_ListOfFlaggedStudents admin_ListOfFlaggedStudents_pointer;
    admin_ListOfFlaggedStudents_pointer.setModal(true);
    admin_ListOfFlaggedStudents_pointer.exec();
}

void admin_main::on_pushButton_RemoveStudent_clicked()
{
    // function is called when 'RemoveStudent' button is clicked

    this->close();

    admin_RemoveStudent admin_RemoveStudent_pointer;
    admin_RemoveStudent_pointer.setModal(true);
    admin_RemoveStudent_pointer.exec();
}

void admin_main::on_pushButton_EditClubAttendance_clicked()
{
    // function is called when 'EditClubAttendance' button is clicked

    this->close();

    Admin_EditClubAttendance admin_EditClubAttendance_pointer;
    admin_EditClubAttendance_pointer.setModal(true);
    admin_EditClubAttendance_pointer.exec();
}

void admin_main::on_pushButton_AddStudent_clicked()
{
    // function is called when 'AddStudent' button is clicked

    this->close();

    AddStudentToClub AddStudentToClub_pointer;
    AddStudentToClub_pointer.setModal(true);
    AddStudentToClub_pointer.exec();
}

void admin_main::on_pushButton_IndividualClubInformation_clicked()
{
    // function is called when 'IndividualClubInformation' button is clicked

    this->close();

    admin_IndividualClubInformation admin_IndividualClubInformation_pointer;
    admin_IndividualClubInformation_pointer.setModal(true);
    admin_IndividualClubInformation_pointer.exec();
}

void admin_main::on_pushButton_AddUser_clicked()
{
    // function is called when 'AddUser' button is clicked

    this->close();

    admin_AddUser admin_AddUser_pointer;
    admin_AddUser_pointer.setModal(true);
    admin_AddUser_pointer.exec();
}
