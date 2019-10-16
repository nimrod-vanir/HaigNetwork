#ifndef PRESIDENT_REMOVEMEMBERS_H
#define PRESIDENT_REMOVEMEMBERS_H

#include <QDialog>

namespace Ui {
class president_RemoveMembers;
}

class president_RemoveMembers : public QDialog
{
    Q_OBJECT

public:
    explicit president_RemoveMembers(QWidget *parent = 0);
    ~president_RemoveMembers();

private:
    Ui::president_RemoveMembers *ui;
};

#endif // PRESIDENT_REMOVEMEMBERS_H
