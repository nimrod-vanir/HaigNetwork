//include required header files and libraries
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admin_main.h"
#include "president_main.h"
#include "globals.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);
    qDebug() << QDir::currentPath();

    //if(dbOpen())
      //  ui->label_Status->setText("Database Connected");

    //else
      //  ui->label_Status->setText("Failed to Connect to Database");
}

MainWindow::~MainWindow()
{
    //function called when window is closed

    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    // function is called when 'Login' button is clicked
    qDebug() << "login";
    QString username, password;
    username = ui->lineEdit_UserName->text();
    SecCookie_Instance.assign(username.toInt());
    password = ui->lineEdit_Password->text();

    qDebug() << SecCookie_Instance.id;

    if(!dbOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }

    dbOpen();
    QSqlQuery qry;
    qry.prepare("select * from Users where UserID = '"+username+"' and Password = '"+password+"'");

    if(qry.exec())
    {
        int count = 0;
        while(qry.next())
        {
            count++;
        }

        if(count == 1)
        {
            ui->label_Status->setText("Username and password is correct");
            dbClose();
            this->close();
            qry.first();
            if(qry.value(3).toString() == "Exec"){
                president_main president_main_pointer;
                president_main_pointer.setModal(true);
                president_main_pointer.exec();
            }
            else if(qry.value(3).toString() == "Admin"){
                admin_main admin_main_pointer;
                admin_main_pointer.setModal(true);
                admin_main_pointer.exec();
            }
        }
        if(count > 1)
        {
            ui->label_Status->setText("Duplicate username and password");
            dbClose();
        }
        if(count < 1)
        {
            QMessageBox::warning(this, tr("ERROR"), tr("Username and/or password is incorrect"));
            dbClose();
        }
    }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    // function is used for reference

    //ui->label_3->setText(ui->calendarWidget->selectedDate().toString("MMM dd yyyy"));
    //ui->calendarWidget->setSelectedDate(QDate::fromString("Jan 20 2015", "MMM dd yyyy"));
}
