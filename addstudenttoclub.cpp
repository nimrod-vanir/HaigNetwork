//include required header files and libraries
#include "addstudenttoclub.h"
#include "ui_addstudenttoclub.h"
#include "mainwindow.h"
#include "createnewstudent.h"
#include <QMessageBox>
#include "admin_main.h"
#include "president_main.h"


AddStudentToClub::AddStudentToClub(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudentToClub)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);

    //comboBox is loaded with appropriate clubs based on user
    QVariant currentID;
    currentID = SecCookie_Instance.id;

    MainWindow_Class.dbOpen();
    QSqlQuery qry_checkUser1;
    QSqlQuery qry_checkUser2;

    qry_checkUser1.prepare("select * from Users where UserID = '"+currentID.toString()+"' ");
    if (qry_checkUser1.exec()){
        while (qry_checkUser1.next()){
            if (qry_checkUser1.value(3).toString() == "Admin"){
                qry_checkUser2.prepare("select * from ClubsInfo where ClubStatus = 'Active' ");
            }
            else{
                qry_checkUser2.prepare("select * from ClubsInfo where ClubPresident = '"+currentID.toString()+"' ");
            }
        }
    }

    //else{
      //  qry_checkUser2.prepare("select * from ClubsInfo where ClubPresident = '"+currentID.toString()+"' ");
    //}

    if (qry_checkUser2.exec()){
        while (qry_checkUser2.next()){
            ui->comboBox_Clubs->addItem(qry_checkUser2.value(0).toString());
            qDebug() << qry_checkUser2.value(0);
        }
    }
    MainWindow_Class.dbClose();
}

AddStudentToClub::~AddStudentToClub()
{
    //function called when window is closed

    delete ui;
}

void AddStudentToClub::on_pushButton_Save_clicked()
{
    //function is called when 'Save' button is clicked

    //initialization of variables
    QString StudentID, StudentNAME, StudentEMAIL;
    QString ClubNAME, ClubID;
    bool isInt;

    StudentID = ui->lineEdit_StudentNum->text().toDouble(&isInt);

    //check that student number entered is of int type (if not, error message is displayed)
    if (!isInt) {
        QMessageBox::warning(this, tr("ERROR"), tr("Student number must be a number."));
    }

    //variables are assigned to values from Ui
    StudentID = ui->lineEdit_StudentNum->text();
    StudentNAME = ui->lineEdit_StudentName->text();
    StudentEMAIL = ui->lineEdit_Email->text();

    //check that all fields have entered information (if not, error message is displayed)
    if (StudentNAME == "" or StudentEMAIL == ""){
        QMessageBox::warning(this, tr("ERROR"), tr("Please enter all information."));
    }

    else{
        //username is checked to see if it's present in database; if present, student is added to the group,
        //else 'createnewstudent' page is called to add student to database
        //error messages displayed appropriately

        ClubNAME = ui->comboBox_Clubs->currentText();

        MainWindow_Class.dbOpen();
        QSqlQuery CheckIfStudentExists;
        QSqlQuery GetClubID;
        QSqlQuery CheckIfStudentInClub;

        bool StudentInClub = false, StudentInDB = false;

        CheckIfStudentExists.prepare("select * from Students where StudentID = '"+StudentID+"' ");
        if (CheckIfStudentExists.exec()){
            qDebug () << "1";
            while (CheckIfStudentExists.next()){
                StudentInDB = true;
                qDebug () << "2";
                GetClubID.prepare("select * from ClubsInfo where ClubName = '"+ClubNAME+"' ");
                if (GetClubID.exec()){
                    qDebug () << "3";
                    while (GetClubID.next()){
                        ClubID = GetClubID.value(3).toString();
                        qDebug () << "4";
                        CheckIfStudentInClub.prepare("select * from MemberShips where ClubID = '"+GetClubID.value(3).toString()+"' and StudentID = '"+StudentID+"' ");
                        if (CheckIfStudentInClub.exec()){
                          //  qDebug () << "5";
                            while (CheckIfStudentInClub.next()){
                                StudentInClub = true;
                                qDebug () << "6";
                                qDebug () << "alerady in";
                                MainWindow_Class.dbClose();
                                QMessageBox::warning(this, tr("ERROR"), tr("Student number already exists in club."));
                            }
                        }
                    }
                }
            }
        }

        if (!StudentInClub){
            if (!StudentInDB){
                qDebug() << "not in db";
                QMessageBox::warning(this, tr("ERROR"), tr("Student number is none existent. Please add this student to the database."));

                CreateNewStudent CreateNewStudent_pointer;
                CreateNewStudent_pointer.setModal(true);
                CreateNewStudent_pointer.exec();
            }
            else{
                MainWindow_Class.dbOpen();
                QSqlQuery AddToClub;
                AddToClub.prepare("insert into MemberShips (ClubID, StudentID, DateIn, Status) values ('"+ClubID+"', '"+StudentID+"', '"+QDate::currentDate().toString("MMM dd yyyy")+"', 'Active') ");

                if (AddToClub.exec()){
                    MainWindow_Class.dbClose();
                   QMessageBox::information(this, tr("SAVED"), tr("New Student has been saved."));
                }
                else{
                    MainWindow_Class.dbClose();
                    QMessageBox::warning(this, tr("ERROR"), tr("There was an error. Please try again. (Contact Mr. Lawrence if this problem continues)"));
                }
            }
        }
    }
}

void AddStudentToClub::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    QVariant currentID;
    currentID = SecCookie_Instance.id;

    MainWindow_Class.dbOpen();
    QSqlQuery qry_checkUser1;

    qry_checkUser1.prepare("select * from Users where UserID = '"+currentID.toString()+"' ");
    if (qry_checkUser1.exec()){
        while (qry_checkUser1.next()){
            if (qry_checkUser1.value(3).toString() == "Admin"){
                admin_main admin_main_pointer;
                admin_main_pointer.setModal(true);
                admin_main_pointer.exec();
            }
            else if (qry_checkUser1.value(3).toString() == "Exec"){
                president_main president_main_pointer;
                president_main_pointer.setModal(true);
                president_main_pointer.exec();
            }
        }
    }
}
