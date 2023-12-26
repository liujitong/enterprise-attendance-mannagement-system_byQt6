#include "dep_change.h"
#include "ui_dep_change.h"
#include "QMessageBox"
#include "publicdb.h"
dep_change::dep_change(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dep_change)
{
    ui->setupUi(this);
    tableset();
    combox_dep_set();
    combox_emp_set();
}

//表的初始化
void dep_change::tableset()
{
    ui->inf_table->setHorizontalHeaderLabels({"员工编号","姓名","部门","部门编号"});
    QSqlQuery query(db);
    query.exec("SELECT eno,ename,department.dname,department.dno FROM employee,department WHERE department.dno=employee.dno");
    int row = 0;
    while(query.next())
    {
        ui->inf_table->setRowCount(row+1);
        for(int column = 0; column < query.record().count(); column++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            ui->inf_table->setItem(row,column,item);
        }
        row++;
    }
}
void dep_change::combox_emp_set()
{
    ui->emp->clear();
    QSqlQuery query(db);
    query.exec("SELECT eno,ename FROM employee");
    while(query.next())
    {
        ui->emp->addItem(query.value(0).toString()+" "+query.value(1).toString());
    }
}
void dep_change::combox_dep_set()
{
    QSqlQuery query(db);
    query.exec("SELECT dno,dname FROM department ");
    while(query.next())
    {
        ui->dep->addItem(query.value(0).toString()+" "+query.value(1).toString());
    }
}
dep_change::~dep_change()
{
    delete ui;
}

void dep_change::on_pushButton_clicked()
{
    QSqlQuery query(db);
    if(query.exec(QString("UPDATE employee SET dno='%1' WHERE eno='%2'").arg(ui->dep->currentText().left(3)).arg(ui->emp->currentText().left(5))))
    {
        QMessageBox::information(this,"更新成功","Successful");
        tableset();
    }
    else {
        QMessageBox::warning(this,"更新失败","Unsuccessful");
    }
}

