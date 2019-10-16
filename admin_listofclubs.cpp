//include required header files and libraries
#include "admin_listofclubs.h"
#include "ui_admin_listofclubs.h"
#include <QMessageBox>
#include "admin_main.h"
//#include "admin_individualclub.h"

admin_ListOfClubs::admin_ListOfClubs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_ListOfClubs)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);

    QSqlQueryModel * tableData = new QSqlQueryModel();
    MainWindow_Class.dbOpen();

    QSqlQuery* qry = new QSqlQuery(MainWindow_Class.LoginDB);
    qry->prepare("select ClubName as 'Club Name', ClubPresident as 'Club President', ClubStatus as 'Club Status', MinAttendPercent as 'Minimum Attendance %' from ClubsInfo order by ClubName");
    qry->exec();
    tableData->setQuery(*qry);
    MainWindow_Class.dbClose();
    ui->tableView_ListOfClub->setModel(tableData);
}

admin_ListOfClubs::~admin_ListOfClubs()
{
    //function called when window is closed

    delete ui;
}

void admin_ListOfClubs::on_tableView_ListOfClub_activated(const QModelIndex &index)
{
    // function is called when 'ListOfClub' table view is clicked on or altered

    QString currentVal = ui->tableView_ListOfClub->model()->data(index).toString();
    QPalette* pal = new QPalette();
    MainWindow_Class.dbOpen();
    QSqlQuery qry;
    qry.prepare("select * from ClubsInfo where ClubName = '"+currentVal+"'");
    if(qry.exec()){
        while(qry.next()){
            ui->label_CurrentClubName->setText(qry.value(0).toString());
            pal->setColor(QPalette::WindowText,Qt::white);
            ui->label_CurrentClubName->setPalette(*pal);
            ui->lineEdit_ClubPresident->setText((qry.value(1).toString()));
            int temp_index_ClubStatus = ui->comboBox_ClubStatus->findText(qry.value(2).toString());
            ui->comboBox_ClubStatus->setCurrentIndex(temp_index_ClubStatus);
            int temp_index_MinAttendPercent = ui->comboBox_MinAttendPercent->findText(qry.value(4).toString());
            ui->comboBox_MinAttendPercent->setCurrentIndex(temp_index_MinAttendPercent);
        }
        MainWindow_Class.dbClose();
    }
}

void admin_ListOfClubs::on_pushButton_Save_clicked()
{
    // function is called when 'Save' button is clicked on
    // function saves all information

    QString ClubPresident, ClubStatus, ClubMinAttendPercent;
    ClubPresident = ui->lineEdit_ClubPresident->text();
    ClubStatus = ui->comboBox_ClubStatus->currentText();
    ClubMinAttendPercent = ui->comboBox_MinAttendPercent->currentText();



    MainWindow_Class.dbOpen();
    QSqlQuery qry;
    qry.prepare("update ClubsInfo set ClubPresident = '"+ClubPresident+"', ClubStatus = '"+ClubStatus+"', MinAttendPercent = '"+ClubMinAttendPercent+"' where ClubName = '"+ui->label_CurrentClubName->text()+"' ");
    if(qry.exec()){

        QMessageBox::information(this, tr("SAVED"), tr("New Club Data has been saved."));
    }
    else{
        QMessageBox::warning(this, tr("ERROR"), tr("Error when updating Club Data. Please try again."));
    }
    MainWindow_Class.dbClose();


    QSqlQueryModel * tableDataRefresh = new QSqlQueryModel();
    MainWindow_Class.dbOpen();

    QSqlQuery* qrry = new QSqlQuery(MainWindow_Class.LoginDB);
    qrry->prepare("select ClubName as 'Club Name', ClubPresident as 'Club President', ClubStatus as 'Club Status', MinAttendPercent as 'Minimum Attendance Percentage' from ClubsInfo order by ClubName");
    qrry->exec();
    tableDataRefresh->setQuery(*qrry);
    MainWindow_Class.dbClose();
    ui->tableView_ListOfClub->setModel(tableDataRefresh);
}

void admin_ListOfClubs::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    admin_main admin_main_pointer;
    admin_main_pointer.setModal(true);
    admin_main_pointer.exec();
}

void admin_ListOfClubs::on_pushButton_OpenIndividualClub_clicked()
{
    // function is called when 'OpenIndividualClub' button is clicked (this function will be available in version 2.0)

    if (ui->tableView_ListOfClub->selectionModel()->currentIndex().column()==0)
    {
        QString CLUBNAME = ui->tableView_ListOfClub->model()->data(ui->tableView_ListOfClub->currentIndex()).toString();
        QString CLUBID;
        QStringListModel studentsList;

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
                //studentsList.append(qrry.value(1).toString());
            }
        }      
    }
}
