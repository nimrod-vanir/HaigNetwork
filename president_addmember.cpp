//include required header files and libraries
#include "president_addmember.h"
#include "ui_president_addmember.h"
#include "mainwindow.h"
#include "globals.h"
#include "president_main.h"

president_AddMember::president_AddMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::president_AddMember)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);
}

president_AddMember::~president_AddMember()
{
    //function called when window is closed

    delete ui;
}

void president_AddMember::on_pushButton_Back_clicked()
{
    //function is called when 'Back' button is clicked
    //closes current window and returns to previous window

    this->close();

    president_main president_main_pointer;
    president_main_pointer.setModal(true);
    president_main_pointer.exec();
}
