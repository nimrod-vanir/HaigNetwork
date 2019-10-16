//include required header files and libraries
#include "admin_individualclubinformation.h"
#include "ui_admin_individualclubinformation.h"
#include "mainwindow.h"
#include "admin_main.h"

admin_IndividualClubInformation::admin_IndividualClubInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_IndividualClubInformation)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);

    MainWindow_Class.dbOpen();
    QSqlQuery qry;
    qry.prepare("select * from ClubsInfo where ClubStatus = 'Active' ");
    if (qry.exec()){
        while (qry.next()){
            ui->listWidget_ClubList->addItem(qry.value(0).toString());
        }
    }
    MainWindow_Class.dbClose();
}

admin_IndividualClubInformation::~admin_IndividualClubInformation()
{
    //function called when window is closed

    delete ui;
}

void admin_IndividualClubInformation::on_listWidget_ClubList_activated(const QModelIndex &index)
{
    // function is called when the 'Clublist' list widget is called

    ui->listWidget_StudentList->clear();

    QString CLUBNAME = index.data().toString();
    QString CLUBID;

    MainWindow_Class.dbOpen();
    QSqlQuery qry;
    qry.prepare("select * from ClubsInfo where ClubName = '"+CLUBNAME+"' ");
    if (qry.exec()){
        while (qry.next()){
            CLUBID = qry.value(3).toString();
        }
    }

    QSqlQuery qrry;
    qrry.prepare("select * from MemberShips where ClubID = '"+CLUBID+"' ");
    if (qrry.exec()){
        while (qrry.next()){
            QString STUDENTID = qrry.value(1).toString();
            QSqlQuery qrrry;
            qrrry.prepare("select * from Students where StudentID = '"+STUDENTID+"' ");
            if (qrrry.exec()){
                while (qrrry.next()){
                    ui->listWidget_StudentList->addItem(qrrry.value(1).toString());
                }
            }
        }
    }
}

void admin_IndividualClubInformation::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    admin_main admin_main_pointer;
    admin_main_pointer.setModal(true);
    admin_main_pointer.exec();
}
