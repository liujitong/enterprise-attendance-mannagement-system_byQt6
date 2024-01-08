#include "department_set.h"
#include "ui_department_set.h"
#include "publicdb.h"
#include <QMessageBox>
department_set::department_set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::department_set)
{
    ui->setupUi(this);

    QSqlQuery query(db);
    query.exec("SELECT ename,employee.eno from employee ,account where account.eno=employee.eno and (account.type=2) ");
    while(query.next())
    {
        ui->comboBox->addItem(query.value(1).toString()+" "+query.value(0).toString());
    }

}

department_set::~department_set()
{
    delete ui;
}

void department_set::on_pushButton_clicked()
{
    QSqlQuery query(db),qu3(db);
    static QRegularExpression dnostd( "[0-9]{3}" );//设置正则表达式-部门账号
    static QRegularExpression dnamestd("[\u4e00-\u9fa5]+");
    if(!dnostd.match(ui->did->text()).hasMatch())
    {
        QMessageBox::warning(this,"部门号输入错误","部门号格式为3位数字");
    }
    else if(!dnamestd.match(ui->dname->text()).hasMatch())
    {
        QMessageBox::warning(this,"名称输入错误","名称应该纯中文");
    }
    else
    {
        QString other=ui->Other->text();
        if(query.exec(QString("INSERT INTO department VALUES('%1','%2','%3','%4')").arg(ui->did->text()).arg(ui->dname->text()).arg(ui->comboBox->currentText().left(5)).arg(other)))
        {
            QMessageBox::information(this,"创建成功","SUCCESSFUL");
            ui->did->clear();
            ui->dname->clear();
            ui->Other->clear();
            ui->comboBox->clear();
            //设置复选框
            QSqlQuery query(db);
            query.exec("SELECT ename,employee.eno from employee ,account where account.eno=employee.eno and (account.type=2) ");
            while(query.next())
            {
                ui->comboBox->addItem(query.value(1).toString()+" "+query.value(0).toString());
            }
            qu3.exec(QString("UPDATE account SET type=1 WHERE eno='%1'").arg(ui->comboBox->currentText().left(5)));//更新账户类别
        }
        else
        {
                QMessageBox::warning(this,"出错了","请检查部门编号是否重复");
        }
    }
}

