#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include <QMainWindow>

namespace Ui {
class superadmin;
}

class superadmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit superadmin(QWidget *parent = nullptr);
    void superadminset(QString eno);
    ~superadmin();
    void tableset();//设置表
    void treeset();//设置树
private slots:
    void department_set();
    void re_new_pr();
    void open_resi_superadmin();
private:
    Ui::superadmin *ui;
};


#endif // SUPERADMIN_H
