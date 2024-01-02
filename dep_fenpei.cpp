#include "dep_fenpei.h"
#include "ui_dep_fenpei.h"
#include "QMessageBox"
#include "publicdb.h"
dep_fenpei::dep_fenpei(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dep_fenpei)
{
    ui->setupUi(this);
    tableset();
    combox_dep_set();
    combox_emp_set();
}
//表的初始化
void dep_fenpei::tableset()
{
    ui->inf_table->clear();
    ui->inf_table->setHorizontalHeaderLabels({"姓名","编号"});
    QSqlQuery query(db);
    query.exec("SELECT eno,ename FROM employee WHERE dno IS NULL;");
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
void dep_fenpei::combox_emp_set()
{
    ui->emp->clear();
    QSqlQuery query(db);
    query.exec("SELECT eno,ename FROM employee WHERE dno IS NULL; ");
    while(query.next())
    {
        ui->emp->addItem(query.value(0).toString()+" "+query.value(1).toString());
    }
}
void dep_fenpei::combox_dep_set()
{
    QSqlQuery query(db);
    query.exec("SELECT dno,dname FROM department ");
    while(query.next())
    {
        ui->dep->addItem(query.value(0).toString()+" "+query.value(1).toString());
    }
}
dep_fenpei::~dep_fenpei()
{
    delete ui;
}

void dep_fenpei::on_pushButton_clicked()
{
    if(ui->emp->currentText()=="")
    {
        QMessageBox::critical(this,"输入有误","员工ID是空值，Empty");
        return;
    }
    QSqlQuery query(db);

    if(query.exec(QString("UPDATE employee SET dno='%1' WHERE eno='%2'").arg(ui->dep->currentText().left(3)).arg(ui->emp->currentText().left(5))))
    {
        combox_emp_set();
        tableset();
        QMessageBox::information(this,"修改成功","Successful");
    }
    else
    {
        QMessageBox::warning(this,"修改失败","Unsuccessful");
    }
}

