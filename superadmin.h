#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class superadmin;
}

class superadmin : public QMainWindow
{
    Q_OBJECT

public:
    QString eno;
    explicit superadmin(QWidget *parent = nullptr);
     void closeEvent(QCloseEvent *e);
    void superadminset();
    ~superadmin();
    void tableset();//设置表
    void treeset();//设置树
private slots:
    void department_se();
    void re_new_pr();
    void open_resi_superadmin();
    void depm_set();
    void open_dep_fenpei();
    void open_dep_change();
    void open_emp_set();
    void open_empl();
    void on_upadate_clicked();
    void open_change_pss();

private:
    Ui::superadmin *ui;
};


#endif // SUPERADMIN_H
