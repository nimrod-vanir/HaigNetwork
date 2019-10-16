//include required header files and libraries
#include "president_addnewclubmeeting.h"
#include "ui_president_addnewclubmeeting.h"
#include "president_main.h"
#include <QMessageBox>

president_AddNewClubMeeting::president_AddNewClubMeeting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::president_AddNewClubMeeting)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);

    QVariant currentID;
    currentID = SecCookie_Instance.id;

    MainWindow_Class.dbOpen();
    QSqlQuery SetComboBox;
    QSqlQuery CheckIfClubEmpty;
    SetComboBox.prepare("select * from ClubsInfo where ClubPresident = '"+currentID.toString()+"' and ClubStatus = 'Active' ");
    if (SetComboBox.exec()){
        while (SetComboBox.next()){
            CheckIfClubEmpty.prepare("select * from MemberShips where ClubID = '"+SetComboBox.value(3).toString()+"' ");
            if (CheckIfClubEmpty.exec()){
                while (CheckIfClubEmpty.next()){
                    ui->comboBox_Clubs->addItem(SetComboBox.value(0).toString());
                    CheckIfClubEmpty.last();
                }
            }
        }
    }
    MainWindow_Class.dbClose();
}

president_AddNewClubMeeting::~president_AddNewClubMeeting()
{
    //function called when window is closed

    delete ui;
}

void president_AddNewClubMeeting::on_calendarWidget_activated(const QDate &date)
{
    //function is called when calendar widget is clicked on or altered
    if (ui->comboBox_Clubs->currentText() != "Select a Club"){
        ui->tableWidget_Meeting->clearContents();
        ui->tableWidget_Meeting->setRowCount(0);

        MainWindow_Class.dbOpen();
        QSqlQuery GetClubID;
        QSqlQuery AddToTableWidget;
        QSqlQuery GetStudentName;
        QString ClubID, ClubNAME;
        int tempCount = 0;

        StudentIDList->clear();

        GetClubID.prepare("select * from ClubsInfo where ClubName = '"+ui->comboBox_Clubs->currentText()+"'");
        if (GetClubID.exec()){
            while (GetClubID.next()){
                ClubNAME = ui->comboBox_Clubs->currentText();
                ClubID = GetClubID.value(3).toString();
                qDebug() << "1" << ClubID << ClubNAME;

                AddToTableWidget.prepare("select * from MemberShips where ClubID = '"+ClubID+"' and Status = 'Active' ");
                if (AddToTableWidget.exec()){
                    //AddToTableWidget.first();
                    while (AddToTableWidget.next()){
                        qDebug() << "2";
                        StudentIDList->append(AddToTableWidget.value(1).toInt());
                        GetStudentName.prepare("select * from Students where StudentID = '"+AddToTableWidget.value(1).toString()+"' ");
                        if (GetStudentName.exec()){
                            while (GetStudentName.next()){
                                ui->tableWidget_Meeting->setRowCount(ui->tableWidget_Meeting->rowCount() + 1);
                                QTableWidgetItem *temp = new QTableWidgetItem(GetStudentName.value(1).toString());
                                ui->tableWidget_Meeting->setItem(tempCount, 0, temp);
                                tempCount++;
                            }
                        }
                    }
                }
            }
        }
        MainWindow_Class.dbClose();
        qDebug() << *StudentIDList;
    }

    else{
        QMessageBox::warning(this, tr("Club Selection"), tr("Please select a club."));
    }

}

void president_AddNewClubMeeting::on_pushButton_Save_clicked()
{
    // function is called when 'Save' button is clicked on

    if (ui->comboBox_Clubs->currentText() == "Select a Club"){
        QMessageBox::warning(this, tr("Club Selection"), tr("Please select a club."));
    }

    else{
        if (ui->tableWidget_Meeting->rowCount() == 0){
            QMessageBox::warning(this, tr("ERROR"), tr("Please select a date."));
        }

        bool tableIsFull = true;
        for (int i = 0; i<ui->tableWidget_Meeting->rowCount(); i++){
            QTableWidgetItem* item1 = ui->tableWidget_Meeting->item(i,0);
            QTableWidgetItem* item2 = ui->tableWidget_Meeting->item(i,1);
            if (!item1 || item1->text().isEmpty())
            {
               if (!item2 || item2->text().isEmpty())
               {
                  tableIsFull = false;
               }
            }
        }

        if (tableIsFull){
            MainWindow_Class.dbOpen();
            QSqlQuery GetClubID;
            QString ClubID, ClubNAME = ui->comboBox_Clubs->currentText();
            GetClubID.prepare("select * from ClubsInfo where ClubName = '"+ui->comboBox_Clubs->currentText()+"' ");
            qDebug() << "1";
            if (GetClubID.exec()){
                qDebug() << "2";
                while (GetClubID.next()){
                    qDebug() << "3";
                    ClubID = GetClubID.value(3).toString();
                }
            }

            QVariant temp_MeetingID = 0;
            QSqlQuery FindClubID;
            FindClubID.prepare("select * from Meetings where ClubID > 0");
            if (FindClubID.exec()){
                while (FindClubID.next()){
                    int tempnum = FindClubID.value(0).toInt();
                    if (tempnum > temp_MeetingID.toInt()){
                        temp_MeetingID = tempnum + 1;
                    }
                }
            }

            qDebug() << temp_MeetingID.toInt();

            QSqlQuery AddNewMeeting;
            AddNewMeeting.prepare("insert into Meetings (ClubID, Date) values ('"+ClubID+"', '"+ui->calendarWidget->selectedDate().toString("MMM dd yyyy")+"')");    //QDate::currentDate().toString("MMM dd yyyy")+"') ");
            qDebug() << "4";
            if (AddNewMeeting.exec()){
                qDebug() << "5";
                qDebug () << ui->calendarWidget->selectedDate().toString("MMM dd yyyy");
            }

            QSqlQuery addToAttendance;
            QVariant StudentID;

            qDebug() << StudentIDList->at(0);
            bool queryState = true;
            for (int i = 0; i<ui->tableWidget_Meeting->rowCount(); i++){
                QTableWidgetItem* item1 = ui->tableWidget_Meeting->item(i,0);
                StudentID = StudentIDList->at(i);
                if (!item1 || item1->text().isEmpty())
                {
                    addToAttendance.prepare("insert into Attendance (ClubID, MeetingID, StudentID, Presence) values ('"+ClubID+"', '"+temp_MeetingID.toString()+"', '"+StudentID.toString()+"', 'True') ");
                }
                else{
                    addToAttendance.prepare("insert into Attendance (ClubID, MeetingID, StudentID, Presence) values ('"+ClubID+"', '"+temp_MeetingID.toString()+"', '"+StudentID.toString()+"', 'False') ");
                }

                if (addToAttendance.exec()){
                    while (addToAttendance.next()){
                        queryState = true;
                    }
                }
                else{
                    queryState = false;
                }
            }

            if (queryState){
                QMessageBox::information(this, tr("SUCCESS"), tr("New meeting information has been saved."));
            }

            MainWindow_Class.dbClose();
        }

        else{
            QMessageBox::warning(this, tr("ERROR"), tr("Please select a date."));
        }
    }
}

void president_AddNewClubMeeting::on_comboBox_Clubs_activated(const QString &arg1)
{
    // function is called when 'Clubs' comboBox is clicked or altered

    ui->tableWidget_Meeting->clearContents();
}

void president_AddNewClubMeeting::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    president_main president_main_pointer;
    president_main_pointer.setModal(true);
    president_main_pointer.exec();
}
