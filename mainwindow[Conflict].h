#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "admin_main.h"
#include "globals.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString path;
    QSqlDatabase LoginDB;
    void dbClose()
    {
        LoginDB.close();
        LoginDB.removeDatabase(QSqlDatabase::defaultConnection );
    }

    bool dbOpen()
    {
        path = QDir::current().path()+"/StandardUserDataBase.db";
        qDebug() << path;
        LoginDB = QSqlDatabase::addDatabase("QSQLITE");
        LoginDB.setDatabaseName(path);
        //LoginDB.setDatabaseName("/Users/nimrodvanir/Google\ Drive/Grade\ 12/Computer\ Science/HaigNetwork/StandardUserDataBase.db");
        //QFileInfo checkfile("/Users/nimrodvanir/Google\ Drive/Grade\ 12/Computer\ Science/HaigNetwork/StandardUserDataBase.db");

        if(LoginDB.open()){
            qDebug()<<("Database Connected");
            return true;
        }

        else{
            qDebug()<<("Failed to Connect to Database");
            return true;
        }
    }

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_Login_clicked();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
