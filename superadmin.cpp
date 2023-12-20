#include "superadmin.h"
#include "ui_superadmin.h"
#include "publicdb.h"
superadmin::superadmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::superadmin)
{
    ui->setupUi(this);
    ui->ALL->setHorizontalHeaderLabels({"姓名","编号","部门","性别","电话"});

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

void superadmin::on_pushButton_clicked()
{


    QSqlQuery query(db);
    query.exec("SELECT ename,eno, dno, gendar ,telephone from employee ");
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

