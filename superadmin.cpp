#include "superadmin.h"
#include "ui_superadmin.h"
#include "employee_set.h"
#include "publicdb.h"
#include "resi.h"
#include "resi_superadmin.h"
#include <QStandardItemModel>
#include "department_set.h"
#include "dep_fenpei.h"
#include "dep_change.h"
#include "depm.h"
#include "empl.h"
#include "pss_change.h"
superadmin::superadmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::superadmin)
{
    ui->setupUi(this);
    treeset();
    tableset();
    QObject::connect(ui->actionss, SIGNAL(triggered()), this, SLOT(department_se()));//部门设置槽函数
    QObject::connect(ui->actionREANEWACC,SIGNAL(triggered()),this,SLOT(re_new_pr()));//普通员工注册信号
    QObject::connect(ui->actionRESi,SIGNAL(triggered()),this,SLOT(open_resi_superadmin()));//超级管理员注册信号
    QObject::connect(ui->actionset,SIGNAL(triggered()),this,SLOT(depm_set()));//设置部门查看窗口
    QObject::connect(ui->actions1,SIGNAL(triggered()),this,SLOT(open_dep_fenpei()));//员工部门分配窗口的槽函数
    QObject::connect(ui->actions2,SIGNAL(triggered()),this,SLOT(open_dep_change()));//员工部门调换窗口
    QObject::connect(ui->actionreanew,SIGNAL(triggered()),this,SLOT(open_emp_set()));//员工注册窗口
    QObject::connect(ui->actionedit_2,SIGNAL(triggered()),this,SLOT(open_empl()));//员工查看窗口
    QObject::connect(ui->actioncode,SIGNAL(triggered()),this,SLOT(open_change_pss()));//更改密码
}
//根据项目初始化treeview，让他显示所有的部门，和该部门下面的所有员工
void superadmin::treeset()
{
    ui->treeView->setEditTriggers(QTreeView::NoEditTriggers);
    //清空treeView
    ui->treeView->setModel(NULL);
    QStandardItemModel *model = new QStandardItemModel(ui->treeView);
    QSqlQuery query(db);
    query.exec("SELECT dno,dname from department");
    while(query.next())
    {
        QStandardItem *item = new QStandardItem(query.value(1).toString());
        model->appendRow(item);
        QSqlQuery query2(db);
        query2.exec(QString("SELECT ename from employee where dno='%1'").arg(query.value(0).toString()));
        while(query2.next())
        {
            QStandardItem *item2 = new QStandardItem(query2.value(0).toString());
            item->appendRow(item2);
        }
    }
    ui->treeView->setModel(model);
    ui->treeView->expandAll();

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

void superadmin::on_upadate_clicked()
{
    tableset();
    treeset();
}

void superadmin::open_change_pss()
{
    pss_change *pss=new pss_change();
    pss->eno=eno;
    pss->show();
}

void superadmin::closeEvent(QCloseEvent *e)
{
    e->accept();
    db.close();
}
