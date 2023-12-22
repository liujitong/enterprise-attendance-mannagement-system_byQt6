 #include "superadmin.h"
#include "ui_superadmin.h"
#include "publicdb.h"
#include "resi.h"
#include "resi_superadmin.h"
#include "QDebug"
superadmin::superadmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::superadmin)
{
    ui->setupUi(this);
    treeset();
    tableset();
    connect(ui->actionss, SIGNAL(triggered()), this, SLOT(department_set()));//部门设置槽函数
    connect(ui->actionREANEWACC,SIGNAL(triggered()),this,SLOT(re_new_pr()));//普通员工注册信号
    connect(ui->actionRESi,SIGNAL(triggered()),this,SLOT(open_resi_superadmin()));//超级管理员注册信号

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
            ui->ALL->setItem(row,column,item);
        }
        row++;
    }
}
//设置标题
void superadmin::superadminset(QString eno)
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

void superadmin::department_set()
{
    qDebug()<<"部门设置函数";
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
