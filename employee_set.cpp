#include "employee_set.h"
#include "ui_employee_set.h"
#include "QMessageBox"
#include "publicdb.h"
employee_set::employee_set(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::employee_set)
{
    ui->setupUi(this);
    combox_dep_set();
    combox_gen_set();
}
void employee_set::combox_gen_set()
{
    ui->gen->addItem("男");
    ui->gen->addItem("女");
}
void employee_set::combox_dep_set()
{
    ui->dep->clear();
    QSqlQuery query(db);
    query.exec("SELECT dno,dname FROM department");
    while(query.next())
    {
        ui->dep->addItem(query.value(0).toString()+" "+query.value(1).toString());
    }
}

employee_set::~employee_set()
{
    delete ui;
}

void employee_set::on_pushButton_clicked()
{
    QSqlQuery query(db),qu1(db);
    static QRegularExpression enostd( "[0-9]{5}" );//设置正则表达式-部门账号
    static QRegularExpression enamestd("(!(%[^吖-座]%))||[^a-z]%|[^A-Z]%");
    static QRegularExpression etelstd("[0-9]{11,12}");
    if(!enostd.match(ui->eid->text()).hasMatch())//员工号匹配
    {
        QMessageBox::warning(this,"员工号输入错误","员工号格式为五位数字");
    }
    else if(!enamestd.match(ui->ename->text()).hasMatch())//姓名匹配
    {
        QMessageBox::warning(this,"姓名输入错误","姓名只能是中文或英文");
    }
    else if(ui->telephone->text()=="")//电话号码为空
    {
        if(query.exec(QString("INSERT INTO employee (eno,ename,dno,gendar) VALUES('%1','%2','%3','%4')").arg(ui->eid->text()).arg(ui->ename->text()).arg(ui->dep->currentText().left(3)).arg(ui->gen->currentText())))
        {
            qu1.exec(QString("SELECT code FROM account WHERE eno='%1'").arg(ui->eid->text()));
            if(qu1.first()) QMessageBox::information(this,"创建成功","请牢记您的账户名："+ui->eid->text()+" 密码："+qu1.value(0).toString());
        }
        else
        {
            QMessageBox::warning(this,"出错了","请检查部门编号是否重复");
        }
    }//电话号码匹配
    else if(!etelstd.match(ui->telephone->text()).hasMatch())
    {
        QMessageBox::warning(this,"电话输出错误","电话号码长度限制在11-12位");
    }
    else//都满足的情况之下
    {
        if(query.exec(QString("INSERT INTO employee VALUES('%1','%2','%3','%4','%5')").arg(ui->eid->text()).arg(ui->ename->text()).arg(ui->dep->currentText().left(3)).arg(ui->gen->currentText()).arg(ui->telephone->text())))
        {
            qu1.exec(QString("SELECT code FROM account WHERE eno='%1'").arg(ui->eid->text()));
            if(qu1.first()) QMessageBox::information(this,"创建成功","请牢记您的账户名："+ui->eid->text()+" 密码："+qu1.value(0).toString());
        }
        else
        {
            QMessageBox::warning(this,"出错了","请检查部门编号是否重复");
        }
    }

}

