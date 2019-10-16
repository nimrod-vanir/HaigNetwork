//include required header files and libraries
#include "createnewstudent.h"
#include "ui_createnewstudent.h"
#include <QMessageBox>

CreateNewStudent::CreateNewStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewStudent)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);

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
        }
    }

    else{
        qry_checkUser2.prepare("select * from ClubsInfo where ClubPresident = '"+currentID.toString()+"' ");
    }

    if (qry_checkUser2.exec()){
        while (qry_checkUser2.next()){
            ui->comboBox_Clubs->addItem(qry_checkUser2.value(0).toString());
            qDebug() << qry_checkUser2.value(0);
        }
    }
    MainWindow_Class.dbClose();
}

CreateNewStudent::~CreateNewStudent()
{
    //function called when window is closed

    delete ui;
}

void CreateNewStudent::on_pushButton_Save_clicked()
{
    // function is called when 'Save' button is clicked

    QString StudentID, StudentNAME, StudentEMAIL;
    QString ClubNAME, ClubID;
    bool isInt;

    StudentID = ui->lineEdit_StudentNum->text().toDouble(&isInt);

    if (!isInt) {
        QMessageBox::warning(this, tr("ERROR"), tr("Student number must be a number."));
    }

    StudentID = ui->lineEdit_StudentNum->text();
    StudentNAME = ui->lineEdit_StudentName->text();
    StudentEMAIL = ui->lineEdit_Email->text();

    if(StudentNAME == "" or StudentEMAIL == "") {
        QMessageBox::warning(this, tr("ERROR"), tr("Please enter all information."));
    }

    else{
        ClubNAME = ui->comboBox_Clubs->currentText();

        MainWindow_Class.dbOpen();
        QSqlQuery CheckIfStudentExists;
        QSqlQuery GetClubID;

        bool StudentInDB = false;

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
                        MainWindow_Class.dbClose();
                    }
                }
            }
        }

        if (StudentInDB == true){
            QMessageBox::warning(this, tr("ERROR"), tr("Student number already exists."));
        }
        else{
            MainWindow_Class.dbOpen();
            QSqlQuery AddToDB;
            AddToDB.prepare("insert into Students (StudentID, Name, Email) values ('"+StudentID+"', '"+StudentNAME+"', '"+StudentEMAIL+"') ");

            if (AddToDB.exec()){
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
