//include required header files and libraries
#include "president_removemembers.h"
#include "ui_president_removemembers.h"

president_RemoveMembers::president_RemoveMembers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::president_RemoveMembers)
{
    //function called when window is launched

    //Ui window is displayed
    ui->setupUi(this);
}

president_RemoveMembers::~president_RemoveMembers()
{
    //function called when window is closed

    delete ui;
}
