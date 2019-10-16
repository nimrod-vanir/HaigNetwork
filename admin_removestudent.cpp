//include required header files and libraries
#include "admin_removestudent.h"
#include "ui_admin_removestudent.h"
#include "mainwindow.h"
#include "admin_main.h"
#include <QMessageBox>

admin_RemoveStudent::admin_RemoveStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_RemoveStudent)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);
    MainWindow_Class.dbOpen();
    QSqlQuery qry;
    qry.prepare("select * from ClubsInfo where ClubStatus = 'Active'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->comboBox_club->addItem(qry.value(0).toString());
            qDebug()<<qry.value(0).toString();
        }
    }
    MainWindow_Class.dbClose();
}

admin_RemoveStudent::~admin_RemoveStudent()
{
    //function called when window is closed

    delete ui;
}

void admin_RemoveStudent::on_comboBox_club_activated(const QString &arg1)
{
    // function is called when 'Club' comboBox is clicked on or altered

    ui->comboBox_student->clear();

    if (arg1 != "Select a Club"){
        QString CLUBID, STUDENTID;
        MainWindow_Class.dbOpen();
        QSqlQuery qrry;
        QSqlQuery qrrry;
        QSqlQuery qrrrry;
        QSqlQuery qrrrrry;

        qrry.prepare("select * from ClubsInfo where ClubName = '"+arg1+"'");
        if(qrry.exec())
        {
            while(qrry.next()){
                CLUBID = qrry.value(3).toString();
                qDebug() << "CLUBID" << qrry.value(3).toInt();
                clubToRemove = qrry.value(3).toInt();
                qrrry.prepare("select * from MemberShips where ClubID = '"+CLUBID+"' and Status = 'Active' ");
                if (qrrry.exec()){
                    while (qrrry.next()){
                        STUDENTID = qrrry.value(1).toString();
                        studentToRemove->append(qrrry.value(1).toInt());
                        qrrrry.prepare("select * from Students where StudentID = '"+STUDENTID+"'");
                        if(qrrrry.exec()){
                            while(qrrrry.next()){
                                ui->comboBox_student->addItem(qrrrry.value(1).toString());
                            }
                        }
                    }
                }
            }
        }
        MainWindow_Class.dbClose();
    }

    else{
        ui->comboBox_student->addItem("Select a Student");
    }

}

void admin_RemoveStudent::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    admin_main admin_main_pointer;
    admin_main_pointer.setModal(true);
    admin_main_pointer.exec();
}

void admin_RemoveStudent::on_pushButton_delete_clicked()
{
    if (ui->comboBox_club->currentText() == "Select a Club" or ui->comboBox_student->currentText() == "Select a Student"){
        QMessageBox::warning(this, tr("ERROR"), tr("Please select a club and student."));
    }

    else{
        qDebug() << studentToRemove->value(ui->comboBox_student->currentIndex());
        qDebug() << clubToRemove;

        if (ui->comboBox_student->count() > 0){
            qDebug() << ui->comboBox_student->count();

            QVariant student = studentToRemove->value(ui->comboBox_student->currentIndex());
            QVariant club = clubToRemove;

            MainWindow_Class.dbOpen();
            QSqlQuery removeStudent;
            removeStudent.prepare("update MemberShips set Status = 'Inactive' where StudentID = '"+student.toString()+"' and ClubID = '"+club.toString()+"'");
            if (removeStudent.exec()){
                while (removeStudent.next()){
                }
                ui->comboBox_student->clear();

                QString CLUBID, STUDENTID;
                MainWindow_Class.dbOpen();
                QSqlQuery qrry;
                QSqlQuery qrrry;
                QSqlQuery qrrrry;
                QSqlQuery qrrrrry;
                qrry.prepare("select * from ClubsInfo where ClubName = '"+ui->comboBox_club->currentText()+"'");
                if(qrry.exec())
                    {
                    while(qrry.next()){
                        CLUBID = qrry.value(3).toString();
                        qDebug() << "CLUBID" << qrry.value(3).toInt();
                        clubToRemove = qrry.value(3).toInt();
                        qrrry.prepare("select * from MemberShips where ClubID = '"+CLUBID+"' and Status = 'Active' ");
                        if (qrrry.exec()){
                            while (qrrry.next()){
                                STUDENTID = qrrry.value(1).toString();
                                studentToRemove->append(qrrry.value(1).toInt());
                                qrrrry.prepare("select * from Students where StudentID = '"+STUDENTID+"'");
                                if(qrrrry.exec()){
                                    while(qrrrry.next()){
                                        ui->comboBox_student->addItem(qrrrry.value(1).toString());
                                    }
                                }
                            }
                        }
                    }
                    MainWindow_Class.dbClose();
                }
                QMessageBox::information(this, tr("Student Removed"), tr("Student has been successfully removed."));
            }
        }
    }
}
