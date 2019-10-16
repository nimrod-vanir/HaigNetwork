//include required header files and libraries
#include "admin_adduser.h"
#include "ui_admin_adduser.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "admin_main.h"

admin_AddUser::admin_AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_AddUser)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);
}

admin_AddUser::~admin_AddUser()
{
    //function called when window is closed

    delete ui;
}

void admin_AddUser::on_pushButton_Save_clicked()
{
    // function called when 'Save' button is clicked
    // function saves new user to the database

    QString UserID, UserNAME, UserPASSWORD, UserPROFILE;
    bool isInt;

    UserID = ui->lineEdit_UserID->text().toDouble(&isInt);

    if (!isInt) {
        QMessageBox::warning(this, tr("ERROR"), tr("User ID must be a number."));
    }

    UserID = ui->lineEdit_UserID->text();
    UserNAME = ui->lineEdit_UserName->text();
    UserPASSWORD = ui->lineEdit_Password->text();
    UserPROFILE = ui->comboBox_UserType->currentText();

    if (UserNAME == "" or UserPASSWORD == ""){
        QMessageBox::warning(this, tr("ERROR"), tr("Please enter all information."));
    }

    else{
        MainWindow_Class.dbOpen();
        QSqlQuery qry;

        qry.prepare("insert into Users (UserID, UserName, Password, Profile) values ('"+UserID+"', '"+UserNAME+"', '"+UserPASSWORD+"', '"+UserPROFILE+"')");
        if(qry.exec()){

            QMessageBox::information(this, tr("SAVED"), tr("New User has been saved."));
        }
        else{
            QMessageBox::warning(this, tr("ERROR"), tr("User ID already exists in database."));
        }
        MainWindow_Class.dbClose();
    }
}

void admin_AddUser::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    admin_main admin_main_pointer;
    admin_main_pointer.setModal(true);
    admin_main_pointer.exec();
}
