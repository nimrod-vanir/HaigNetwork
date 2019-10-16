//include required header files and libraries
#include "admin_createaclub.h"
#include "ui_admin_createaclub.h"
#include "admin_main.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "globals.h"

admin_CreateAClub::admin_CreateAClub(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_CreateAClub)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);
}

admin_CreateAClub::~admin_CreateAClub()
{
    //function called when window is closed

    delete ui;
}

void admin_CreateAClub::on_pushButton_SaveClub_clicked()
{
    // function called when 'Save' button is clicked
    // function saves new club to the database

    QString ClubName, ClubPresident, ClubMinAttendPercent;
    ClubName = ui->lineEdit_ClubName->text();
    ClubPresident = ui->lineEdit_ClubPresident->text();
    ClubMinAttendPercent = ui->comboBox_MinAttendPercent->currentText();

    MainWindow_Class.dbOpen();
    QSqlQuery qry;
    qry.prepare("insert into ClubsInfo (ClubName, ClubPresident, MinAttendPercent) values ('"+ClubName+"', '"+ClubPresident+"', '"+ClubMinAttendPercent+"')");
    if(qry.exec()){

        QMessageBox::information(this, tr("SAVED"), tr("New Club has been saved."));
    }
    else{
        QMessageBox::warning(this, tr("ERROR"), tr("Club already exists in database."));
    }
}

void admin_CreateAClub::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    admin_main admin_main_pointer;
    admin_main_pointer.setModal(true);
    admin_main_pointer.exec();
}
