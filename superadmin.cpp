#include "superadmin.h"
#include "ui_superadmin.h"
#include "employee_set.h"
#include "publicdb.h"
#include "resi.h"
#include "resi_superadmin.h"
#include "department_set.h"
#include "dep_fenpei.h"
#include "dep_change.h"
#include "depm.h"
#include "empl.h"
#include "QDebug"
superadmin::superadmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::superadmin)
{
    ui->setupUi(this);
    treeset();
    tableset();
    connect(ui->actionss, SIGNAL(triggered()), this, SLOT(department_se()));//部门设置槽函数
    connect(ui->actionREANEWACC,SIGNAL(triggered()),this,SLOT(re_new_pr()));//普通员工注册信号
    connect(ui->actionRESi,SIGNAL(triggered()),this,SLOT(open_resi_superadmin()));//超级管理员注册信号
    connect(ui->actionset,SIGNAL(triggered()),this,SLOT(depm_set()));//设置部门查看窗口
    connect(ui->actions1,SIGNAL(triggered()),this,SLOT(open_dep_fenpei()));//员工部门分配窗口的槽函数
    connect(ui->actions2,SIGNAL(triggered()),this,SLOT(open_dep_change()));//员工部门调换窗口
    connect(ui->actionreanew,SIGNAL(triggered()),this,SLOT(open_emp_set()));//员工注册窗口
    connect(ui->actionedit_2,SIGNAL(triggered()),this,SLOT(open_empl()));//员工查看窗口
}
void superadmin::treeset()//设置tree
{

}
void superadmin::tableset()//设置table
{
    ui->ALL->setHorizontalHeaderLabels({"姓名","编号","部门","性别","电话"});
    QSqlQuery query(db);
    query.exec("SELECT ename,eno,department.dname, gendar ,telephone from employee,department where employee.dno=department.dno");
    int row = 0;
    while(query.next())
    {
        ui->ALL->setRowCount(row+1);
        for(int column = 0; column < query.record().count(); column++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());

            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            ui->ALL->setItem(row,column,item);
        }
        row++;
    }
}
//设置标题
void superadmin::superadminset()
{
    QSqlQuery qsl(db);
    qsl.exec(QString("select ename from employee where eno='%1'").arg(eno));
    if(qsl.first())
    {
        this->setWindowTitle(QString("超级管理员(%1)界面").arg(qsl.value(0).toString()));
    }
    else
        this->setWindowTitle("超级管理员界面");
}
superadmin::~superadmin()
{
    delete ui;
}

void superadmin::department_se()
{
    department_set *dep=new department_set();
    dep->show();
}

void superadmin::re_new_pr()
{
    resi *re=new resi();
    re->show();
}

void superadmin::open_resi_superadmin()
{
    resi_superadmin *resp=new resi_superadmin();
    resp->show();
}
void superadmin::depm_set()
{
    depm *dep=new depm();
    dep->show();
}
void superadmin::open_dep_fenpei()
{
    dep_fenpei *dep_f=new dep_fenpei();
    dep_f->show();
}
void superadmin::open_dep_change()
{
    dep_change *dep_c=new dep_change();
    dep_c->show();
}
void superadmin::open_emp_set()
{
    employee_set *emp=new employee_set();
    emp->show();
}
void superadmin::open_empl()
{
    empl *empl1=new empl();
    empl1->show();
}
