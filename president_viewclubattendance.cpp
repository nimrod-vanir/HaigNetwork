//include required header files and libraries
#include "president_viewclubattendance.h"
#include "ui_president_viewclubattendance.h"
#include <QMessageBox>
#include "president_main.h"
#include "QString"

president_ViewClubAttendance::president_ViewClubAttendance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::president_ViewClubAttendance)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);
    // hard code username
    QVariant userName;
    userName = SecCookie_Instance.id;


    ui->comboBox_ClubChoice->clear();

    // combo box Club choice set up
    MainWindow_Class.dbOpen();
    QSqlQuery* qry = new QSqlQuery(MainWindow_Class.LoginDB);

    qry->prepare("select ClubName as 'Club Name' from ClubsInfo  where ClubPresident = '"+userName.toString()+"' order by ClubName");

    if(qry->exec()){
        while(qry->next()){
            ui->comboBox_ClubChoice->addItem(qry->value(0).toString());}
                    }
    MainWindow_Class.dbClose();

    ui->comboBox_DateChoice->clear();
    // combo box Date choice set up
    MainWindow_Class.dbOpen();
    QSqlQuery* qry3 = new QSqlQuery(MainWindow_Class.LoginDB);

    qry3->prepare("select Date as 'Date' from Meetings  where ClubID in (select ClubID  from ClubsInfo  where ClubName = '"+ui->comboBox_ClubChoice->currentText()+"') order by Date");
    if(qry3->exec()){
        while(qry3->next()){
            ui->comboBox_DateChoice->addItem(qry3->value(0).toString());}
                    }
    MainWindow_Class.dbClose();

    // displaying the data table
    QSqlQueryModel * tableData1 = new QSqlQueryModel();

    MainWindow_Class.dbOpen();

    QString temp_selectedClub;
    QSqlQuery* qry1 = new QSqlQuery(MainWindow_Class.LoginDB);

    temp_selectedClub = ui->comboBox_ClubChoice->currentText();

    qry1->prepare("select C.ClubName as 'ClubName', M.Date as 'Date', S.Name as 'Name', A.StudentID as 'StudentID' ,A.Presence as 'Presence'  from Attendance as A left join Meetings as M on A.MeetingID = M.MeetingID left join Students as S on A.StudentID = S.StudentID left join ClubsInfo as C on A.ClubID = C.ClubID where C.ClubName = '"+temp_selectedClub+"' and M.Date = '"+ui->comboBox_DateChoice->currentText()+"' order by S.Name");
    qry1->exec();
    tableData1->setQuery(*qry1);
    MainWindow_Class.dbClose();

    ui->tableView_ClubAttendance->setModel(tableData1);

}

president_ViewClubAttendance::~president_ViewClubAttendance()
{
    //function called when window is closed

    delete ui;
}

void president_ViewClubAttendance::on_comboBox_ClubChoice_currentIndexChanged(const QString &arg1)
{
    // function is called when 'ClubChoice' comboBox is clicked or altered

    ui->comboBox_DateChoice->clear();
    MainWindow_Class.dbOpen();
    QSqlQuery* qry3 = new QSqlQuery(MainWindow_Class.LoginDB);

    qry3->prepare("select Date as 'Date' from Meetings  where ClubID in (select ClubID  from ClubsInfo  where ClubName = '"+ui->comboBox_ClubChoice->currentText()+"') order by Date");

    if(qry3->exec()){
        while(qry3->next()){
            ui->comboBox_DateChoice->addItem(qry3->value(0).toString());}
                    }
    MainWindow_Class.dbClose();

    QSqlQueryModel * tableData1 = new QSqlQueryModel();
    MainWindow_Class.dbOpen();
    QString temp_selectedClub;
    QSqlQuery* qry1 = new QSqlQuery(MainWindow_Class.LoginDB);

    temp_selectedClub = ui->comboBox_ClubChoice->currentText();
    qry1->prepare("select C.ClubName as 'ClubName', M.Date as 'Date', S.Name as 'Name', A.StudentID as 'StudentID' ,A.Presence as 'Presence'  from Attendance as A left join Meetings as M on A.MeetingID = M.MeetingID left join Students as S on A.StudentID = S.StudentID left join ClubsInfo as C on A.ClubID = C.ClubID where C.ClubName = '"+temp_selectedClub+"' and M.Date = '"+ui->comboBox_DateChoice->currentText()+"' order by S.Name");
    qry1->exec();
    tableData1->setQuery(*qry1);
    MainWindow_Class.dbClose();
    ui->tableView_ClubAttendance->setModel(tableData1);

}

void president_ViewClubAttendance::on_comboBox_DateChoice_currentIndexChanged(const QString &arg1)
{
    // function is called when 'DateChoice' comboBox is clicked or altered

    QSqlQueryModel * tableData1 = new QSqlQueryModel();
    MainWindow_Class.dbOpen();
    QString temp_selectedClub;
    QSqlQuery* qry1 = new QSqlQuery(MainWindow_Class.LoginDB);

    temp_selectedClub = ui->comboBox_ClubChoice->currentText();
    qry1->prepare("select C.ClubName as 'ClubName', M.Date as 'Date', S.Name as 'Name', A.StudentID as 'StudentID' ,A.Presence as 'Presence'  from Attendance as A left join Meetings as M on A.MeetingID = M.MeetingID left join Students as S on A.StudentID = S.StudentID left join ClubsInfo as C on A.ClubID = C.ClubID where C.ClubName = '"+temp_selectedClub+"' and M.Date = '"+ui->comboBox_DateChoice->currentText()+"' order by S.Name");
    //qry1->prepare("select ClubID as 'Club ID', MeetingID as 'Meeting ID', StudentID as 'Student ID', Presence as 'Presence' from Attendance where ClubID in (select ClubID  from ClubsInfo  where ClubName = '"+temp_selectedClub+"')and MeetingID in (select MeetingID  from Meetings  where Date = '"+ui->comboBox_DateChoice->currentText()+"') order by MeetingID ");
    qry1->exec();
    tableData1->setQuery(*qry1);
    MainWindow_Class.dbClose();
    ui->tableView_ClubAttendance->setModel(tableData1);
}

void president_ViewClubAttendance::on_tableView_ClubAttendance_activated(const QModelIndex &index)
{
    // function is called when 'ClubAttendance' tableview is clicked or altered

    int rowidx = ui->tableView_ClubAttendance->selectionModel()->currentIndex().row();
    MainWindow_Class.dbOpen();
    QSqlQuery qry;
    QString temp_selectedClubID;
    QString temp_selectedClub;
    temp_selectedClub = ui->comboBox_ClubChoice->currentText();

    int i=0;
    qry.prepare("select C.ClubName as 'ClubName', M.Date as 'Date', S.Name as 'Name', A.StudentID as 'StudentID' ,A.Presence as 'Presence'  from Attendance as A left join Meetings as M on A.MeetingID = M.MeetingID left join Students as S on A.StudentID = S.StudentID left join ClubsInfo as C on A.ClubID = C.ClubID where C.ClubName = '"+temp_selectedClub+"' and M.Date = '"+ui->comboBox_DateChoice->currentText()+"' order by S.Name");
    //qry.prepare("select ClubID as 'Club ID', MeetingID as 'Meeting ID', StudentID as 'Student ID', Presence as 'Presence' from Attendance where ClubID in (select ClubID  from ClubsInfo  where ClubName = '"+temp_selectedClub+"')and MeetingID in (select MeetingID  from Meetings  where Date = '"+ui->comboBox_DateChoice->currentText()+"') order by MeetingID ");

    QPalette* pal = new QPalette();
    pal->setColor(QPalette::WindowText,Qt::white);

    if(qry.exec()){
        while(qry.next()){
            if ( rowidx == i) {
            ui->label_CurrentClubID->setText(qry.value(0).toString());
            ui->label_CurrentClubID->setPalette(*pal);
            ui->label_CurrentMeetingID->setText((qry.value(1).toString()));
            ui->label_CurrentMeetingID->setPalette(*pal);
            ui->label_CurrentStudentID->setText((qry.value(3).toString()));
            ui->label_CurrentStudentID->setPalette(*pal);
            ui->label_CurrentStudentName->setText((qry.value(2).toString()));
            ui->label_CurrentStudentName->setPalette(*pal);
            int temp_index_PresenceStatus = ui->comboBox_PresenceStatus->findText(qry.value(4).toString());
            ui->comboBox_PresenceStatus->setCurrentIndex(temp_index_PresenceStatus);
            }
            i++;
        }
        MainWindow_Class.dbClose();
    }
}

void president_ViewClubAttendance::on_pushButton_Save_clicked()
{
    // function is called when 'Save' button is clicked or altered

    QString ClubID, MeetingID, StudentID, PresenceStatus;
    ClubID = ui->label_CurrentClubID->text();
    MeetingID = ui->label_CurrentMeetingID->text();
    StudentID = ui->label_CurrentStudentID->text();
    PresenceStatus = ui->comboBox_PresenceStatus->currentText();

    MainWindow_Class.dbOpen();
    QSqlQuery qry;
    qry.prepare("update Attendance set Presence = '"+PresenceStatus+"' where ClubID  in (select ClubID  from ClubsInfo  where ClubName = '"+ClubID+"') and MeetingID in (select MeetingID  from Meetings  where Date =  '"+MeetingID+"') and StudentID = '"+StudentID+"' ");
    //qry.prepare("update Attendance set Presence = '"+PresenceStatus+"' where ClubID = '"+ClubID+"' and MeetingID = '"+MeetingID+"'and StudentID = '"+StudentID+"' ");
    if(qry.exec()){

        QMessageBox::information(this, tr("SAVED"), tr("New Club Data has been saved."));
    }
    else{
        QMessageBox::warning(this, tr("ERROR"), tr("Error when updating Club Data. Please try again."));
    }
    MainWindow_Class.dbClose();


    QSqlQueryModel * tableData1 = new QSqlQueryModel();

    MainWindow_Class.dbOpen();

    QString temp_selectedClub;

    QSqlQuery* qry1 = new QSqlQuery(MainWindow_Class.LoginDB);

    temp_selectedClub = ui->comboBox_ClubChoice->currentText();
    qry1->prepare("select C.ClubName as 'ClubName', M.Date as 'Date', S.Name as 'Name', A.StudentID as 'StudentID' ,A.Presence as 'Presence'  from Attendance as A left join Meetings as M on A.MeetingID = M.MeetingID left join Students as S on A.StudentID = S.StudentID left join ClubsInfo as C on A.ClubID = C.ClubID where C.ClubName = '"+temp_selectedClub+"' and M.Date = '"+ui->comboBox_DateChoice->currentText()+"' order by S.Name");
   // qry1->prepare("select ClubID as 'Club ID', MeetingID as 'Meeting ID', StudentID as 'Student ID', Presence as 'Presence' from Attendance where ClubID in (select ClubID  from ClubsInfo  where ClubName = '"+temp_selectedClub+"')and MeetingID in (select MeetingID  from Meetings  where Date = '"+ui->comboBox_DateChoice->currentText()+"') order by MeetingID ");
    qry1->exec();
    tableData1->setQuery(*qry1);
    MainWindow_Class.dbClose();
    ui->tableView_ClubAttendance->setModel(tableData1);
}

void president_ViewClubAttendance::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    president_main president_main_pointer;
    president_main_pointer.setModal(true);
    president_main_pointer.exec();
}
