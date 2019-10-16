//include required header files and libraries
#include "admin_listofflaggedstudents.h"
#include "ui_admin_listofflaggedstudents.h"
#include <QMessageBox>
#include "admin_main.h"

admin_ListOfFlaggedStudents::admin_ListOfFlaggedStudents(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_ListOfFlaggedStudents)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);

    MainWindow_Class.dbOpen();
    QSqlQuery qry;
    qry.prepare("select * from ClubsInfo where ClubStatus = 'Active'");
    if (qry.exec()){
        while (qry.next()){
            ui->comboBox_selectedClub->addItem(qry.value(0).toString());
        }
    }
    MainWindow_Class.dbClose();
}

admin_ListOfFlaggedStudents::~admin_ListOfFlaggedStudents()
{
    //function called when window is closed

    delete ui;
    qDebug() << "closed";
}

void admin_ListOfFlaggedStudents::on_comboBox_selectedClub_currentIndexChanged(const QString &arg1)
{
    // function is called when 'selectedClub' comboBox is clicked or altered

    if (ui->comboBox_selectedClub->currentIndex() > 0){
        qDebug() << arg1;
        MainWindow_Class.dbOpen();
        QSqlQuery qry;
        QSqlQuery qrry;
        QSqlQuery qrrry;
        QSqlQuery qrrrry;

        QStringListModel * model = new QStringListModel(this);
        QStringList list;

        QString totClubMeets, MinAttendPerc, CLUBID, STUDENTID;

        list.clear();
        model->setStringList(list);
        ui->listView_ClubFlaggedStudents->setModel(model);

        qry.prepare("select * from ClubsInfo where ClubName = '"+arg1+"'");
        if(qry.exec()){
            while(qry.next()){
                totClubMeets = qry.value(5).toString();
                MinAttendPerc = qry.value(4).toString();
                CLUBID = qry.value(3).toString();

                qrry.prepare("select * from MemberShips where ClubID = '"+CLUBID+"'");
                if(qrry.exec()){
                    while(qrry.next()){
                        STUDENTID = qrry.value(1).toString();
                        qrrry.prepare("select * from Attendance where StudentID = '"+STUDENTID+"' and ClubID = '"+CLUBID+"'");
                        if(qrrry.exec()){
                            int temp_count = 0;
                            while(qrrry.next()){
                                temp_count = temp_count + 1;
                            }

                            if(temp_count*100.0/totClubMeets.toInt() < MinAttendPerc.toInt()){

                                qrrrry.prepare("select * from Students where StudentID = '"+STUDENTID+"'");
                                if(qrrrry.exec()){
                                    while(qrrrry.next()){
                                        list.append(qrrrry.value(1).toString());
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        model->setStringList(list);
        ui->listView_ClubFlaggedStudents->setModel(model);
        MainWindow_Class.dbClose();
    }

}

void admin_ListOfFlaggedStudents::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    admin_main admin_main_pointer;
    admin_main_pointer.setModal(true);
    admin_main_pointer.exec();
}
