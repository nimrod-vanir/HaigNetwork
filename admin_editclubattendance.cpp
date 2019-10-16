#include "admin_editclubattendance.h"
#include "ui_admin_editclubattendance.h"
#include "admin_main.h"
#include <QtGui>
#include <QColumnView>
#include <QMessageBox>
#include <QDebug>
// #include <QListWidgetItem>

#define ATTEND_CLUBID 0
#define ATTEND_MEETID 1
#define ATTEND_STDID  2
#define ATTEND_PRESENCE 3

#define CLUBINFO_CLUBNAME 0
#define CLUBINFO_CLUBPRES 1
#define CLUBINFO_CLUBSTAT 2
#define CLUBINFO_CLUBID   3
#define CLUBINFO_CLUBMINATTEND 4
#define CLUBINFO_CLUBNUMMEETS 5

#define MEETS_MEETID 0
#define MEETS_CLUBID 1
#define MEETS_DATE   2

#define MEMBSHIPS_CLUBID  0
#define MEMBSHIPS_STDID   1
#define MEMBSHIPS_DATEIN  2
#define MEMBSHIPS_DATEOUT 3

#define STDS_STDID 0
#define STDS_NAME  1
#define STDS_EMAIL 2

#define USERS_USERID 0
#define USERS_USERNAME 1
#define USERS_PASSWORD 2
#define USERS_PROFILE 3
#define USERS_USERSTATUS 4

Admin_EditClubAttendance::Admin_EditClubAttendance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin_EditClubAttendance)
{
    ui->setupUi(this);

    init_table();

    find_active_clubs(true);
}

Admin_EditClubAttendance::~Admin_EditClubAttendance()
{
    delete ui;
}

void Admin_EditClubAttendance::init_table()
{
    QTableWidgetItem *HeaderStudents = new QTableWidgetItem;
    QTableWidgetItem *HeaderChkBx = new QTableWidgetItem;

    HeaderStudents->setText("Students");
    HeaderChkBx->setText("Presence");

    ui->tableWidget_students->insertColumn(0);
    ui->tableWidget_students->insertColumn(0);
    ui->tableWidget_students->setHorizontalHeaderItem(0, HeaderStudents);
    ui->tableWidget_students->setHorizontalHeaderItem(1, HeaderChkBx);
}

QString Admin_EditClubAttendance::stdID2NAME(QString stdID)
{
    MainWindow_Class.dbOpen();

    QSqlQuery qry_std;
    QString std_name;

    qry_std.prepare("select * from Students where StudentID = '"+stdID+"'");
    if (qry_std.exec()){
        while (qry_std.next()){
            std_name = qry_std.value(STDS_NAME).toString();
        }
    }
    MainWindow_Class.dbClose();
    return std_name;
}

int Admin_EditClubAttendance::stdNAME2ID(QString stdName)
{
    MainWindow_Class.dbOpen();

    QSqlQuery qry_std;
    int std_ID;

    qry_std.prepare("select * from Students where Name = '"+stdName+"'");
    if (qry_std.exec()){
        while (qry_std.next()){
            std_ID = qry_std.value(STDS_STDID).toInt();
        }
    }
    MainWindow_Class.dbClose();
    return std_ID;
}

bool Admin_EditClubAttendance::save(QString action)
{
    MainWindow_Class.dbOpen();
    bool SaveSuccessful = true;
    char stdID[15];
    char meetID[15];

    QString stdPresence;
    QSqlQuery qry_attend;

    for (int i=0; i<ui->tableWidget_students->rowCount(); i++){
        qDebug() << "studentIDlist:" << studentIDlist->value(i);
        qDebug() << "studentName" << ui->tableWidget_students->item(i, 0)->text();
    }

    sprintf(meetID, "%d", meetIDList->value(ui->listWidget_pick_meet->currentRow()));

    for (int i=0; i<ui->tableWidget_students->rowCount(); i++){
        sprintf(stdID, "%d", studentIDlist->value(ui->tableWidget_students->rowCount()-i-1));
        if (action == "save")
            stdPresence = ui->tableWidget_students->item(i, 1)->text();
        else if (action == "revert")
            stdPresence = presenceListREVsave->value(ui->tableWidget_students->rowCount()-i-1);

        qDebug() << "stdID SAVE" << stdID;
        qDebug() << "stdPresence SAVE" << stdPresence;
        qry_attend.prepare("update Attendance set Presence = '"+stdPresence+"' "
                           "where StudentID = '"+stdID+"' and MeetingID = '"+meetID+"'");
        if (qry_attend.exec())
            SaveSuccessful = true;
        else{
            SaveSuccessful = false;
            break;
        }
    }
    MainWindow_Class.dbClose();
    return SaveSuccessful;
}

QList<int>* Admin_EditClubAttendance::find_active_clubs(bool display_clubs)
{
    MainWindow_Class.dbOpen();

    QSqlQuery qry_activeClubs;

    qry_activeClubs.prepare("select * from ClubsInfo where ClubStatus = 'Active'");
    if (qry_activeClubs.exec()){
        while (qry_activeClubs.next()){
            if (display_clubs)
                ui->listWidget_pick_club->addItem(qry_activeClubs.value(CLUBINFO_CLUBNAME).toString());
            clubIDList->append(qry_activeClubs.value(CLUBINFO_CLUBID).toInt());
        }
    }
    MainWindow_Class.dbClose();
    return clubIDList;
}

QList<int>* Admin_EditClubAttendance::find_meets_of_clubs(QString clubID, bool display_meets)
{
    MainWindow_Class.dbOpen();

    QSqlQuery qry_meets;
    // QList<int>* meetIDList = new QList<int>();
    qDebug() << "Current Club ID:" << clubID;
    ui->listWidget_pick_meet->clear();
    qry_meets.prepare("select * from Meetings where ClubID = '"+clubID+"'");
    if (qry_meets.exec()){
        while (qry_meets.next()){
            if (display_meets)
                ui->listWidget_pick_meet->addItem(qry_meets.value(MEETS_DATE).toString());
            meetIDList->append(qry_meets.value(MEETS_MEETID).toInt());
        }
    }
    MainWindow_Class.dbClose();
    return meetIDList;
}

QList<int>* Admin_EditClubAttendance::find_student_attendance(QString meetID, bool display_attends)
{
    MainWindow_Class.dbOpen();

    QSqlQuery qry_attend;
    QTableWidgetItem* stdName = NULL;
    QTableWidgetItem* stdPresence = NULL;
    int curRow = 0;
    int rows;

    while (ui->tableWidget_students->rowCount()>0)
        ui->tableWidget_students->removeRow(0);
    qry_attend.prepare("select * from Attendance where MeetingID = '"+meetID+"'");
    if (qry_attend.exec()){
        while (qry_attend.next()){
            if (display_attends){
                rows = ui->tableWidget_students->rowCount();
                qDebug() << "Row:" << rows;
                stdName = new QTableWidgetItem(stdID2NAME(qry_attend.value(ATTEND_STDID).toString()));
                stdPresence = new QTableWidgetItem(qry_attend.value(ATTEND_PRESENCE).toString());
                qDebug() << "stdPresence:" << stdPresence->text();
                ui->tableWidget_students->insertRow(0);
                ui->tableWidget_students->setItem(rows - curRow, 0, stdName);
                ui->tableWidget_students->setItem(rows - (curRow++), 1, stdPresence);
            }
            studentIDlist->append(qry_attend.value(ATTEND_STDID).toInt());
            presenceListREVsave->append(qry_attend.value(ATTEND_PRESENCE).toString());
        }
    }
    for (int i=0; i<ui->tableWidget_students->rowCount(); i++){
        qDebug() << "studentIDlist" << studentIDlist->value(ui->tableWidget_students->rowCount()-i-1);
        qDebug() << "presenceListREVsave" << presenceListREVsave->value(ui->tableWidget_students->rowCount()-i-1);
    }
    MainWindow_Class.dbClose();
    return studentIDlist;
}

void Admin_EditClubAttendance::on_listWidget_pick_club_activated(const QModelIndex &index)
{

    QList<int> active_clubs_List, meetings_List;
    char clubIDstr[15];

    active_clubs_List = *find_active_clubs(false);

    sprintf(clubIDstr, "%d", active_clubs_List[index.row()]);
    qDebug() << "current club:" << active_clubs_List[index.row()];
    qDebug() << "index row:" << index.row();
    qDebug() << "clubIDstr:" << clubIDstr;

    meetings_List = *find_meets_of_clubs(clubIDstr, true);

    qDebug() << "clubIDList" << active_clubs_List;
    qDebug() << "meetings_List" << meetings_List;
}


void Admin_EditClubAttendance::on_listWidget_pick_meet_activated(const QModelIndex &index)
{
    char meetIDstr[15];
    sprintf(meetIDstr, "%d", meetIDList->value(index.row()));
    find_student_attendance(meetIDstr, true);
}

void Admin_EditClubAttendance::on_tableWidget_students_activated(const QModelIndex &index)
{
    if (ui->tableWidget_students->currentItem()->text() == "Present")
        ui->tableWidget_students->currentItem()->setText("Absent");
    else if (ui->tableWidget_students->currentItem()->text() == "Absent")
        ui->tableWidget_students->currentItem()->setText("Present");
}

void Admin_EditClubAttendance::on_pushButton_Save_clicked()
{
    if (save("save"))
        QMessageBox::information(this, tr("SAVED"), tr("Your changes have been saved."));
    else
        QMessageBox::warning(this, tr("ERROR"), tr("Error while saving your changes. Please try again."));
}

void Admin_EditClubAttendance::on_pushButton_revert_clicked()
{
    save("revert");
    char meetIDstr[15];
    sprintf(meetIDstr, "%d", meetIDList->value(ui->listWidget_pick_meet->currentIndex().row()));
    qDebug() << "meeting ID from qlist:" << ui->listWidget_pick_meet->currentIndex().data();
    qDebug() << "meetIDstr REVERT BUTTON" << meetIDstr;
    find_student_attendance(meetIDstr, true);
}

void Admin_EditClubAttendance::on_pushButton_Back_clicked()
{
    this->close();

    admin_main admin_main_pointer;
    admin_main_pointer.setModal(true);
    admin_main_pointer.exec();
}
