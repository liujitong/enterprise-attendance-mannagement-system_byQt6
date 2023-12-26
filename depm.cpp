#include "depm.h"
#include "qmessagebox.h"
#include "ui_depm.h"
#include "publicdb.h"
depm::depm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::depm)
{
    ui->setupUi(this);
    tableset();
    comboxset();
}
void depm::admincomboxset(QString arf)//选择管理员的combox初始化
{
    ui->ADMIN->clear();
    QSqlQuery query(db),qu2(db);
    query.exec(QString("SELECT ename from employee where eno='%1' ").arg(arf));
    if(query.first()) ui->ADMIN->addItem(arf+" "+query.value(0).toString());
    qu2.exec(QString("SELECT ename,employee.eno from employee ,account where account.eno=employee.eno and (account.type=2) and employee.eno !='%1'").arg(arf) );
    while(qu2.next())
    {
        ui->ADMIN->addItem(qu2.value(1).toString()+" "+qu2.value(0).toString());
    }
}
void depm::comboxset()
{
    ui->ID->clear();
    ui->ID_2->clear();
    QSqlQuery query(db);
    query.exec("SELECT dno from department ");
    while(query.next())
    {
        ui->ID->addItem(query.value(0).toString());
       ui->ID_2->addItem(query.value(0).toString());
    }
}
void depm::tableset()//设置table
{
    ui->ALL->setHorizontalHeaderLabels({"部门编号","部门名称","部门人数","部门管理员","部门备注"});
    QSqlQuery query(db);
    query.exec("SELECT d.dno, d.dname, (SELECT COUNT(*) FROM employee WHERE dno = d.dno) AS '员工数量', e.ename AS '管理员姓名', d.Other AS '备注' FROM department d LEFT JOIN employee e ON d.dmano = e.eno GROUP BY d.dno, d.dname, e.ename, d.Other;");
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
depm::~depm()
{
    delete ui;
}


//将编辑框更改为eno对应的内容。
void depm::on_ID_currentIndexChanged(int index)
{
    if(index)index++;
    QString secNO=ui->ID->currentText();
    QSqlQuery query(db);
    query.exec(QString("SELECT dname,dmano,other from department where dno='%1'").arg(secNO));
    if(query.first())
    {
        ui->nameedit->setText(query.value(0).toString());
        ui->otheredit->setText(query.value(2).toString());
        admincomboxset(query.value(1).toString());
    }
}

void depm::on_conf_edit_clicked()
{
    QSqlQuery qu1(db),qu2(db),qu3(db);
    qu1.exec(QString("UPDATE account SET type='2' WHERE eno=(SELECT dmano FROM department WHERE dno='%1')").arg(ui->ID->currentText()));
    if(qu2.exec(QString("UPDATE department SET dname='%1',dmano='%2',other='%3' WHERE  dno='%4'").arg(ui->nameedit->text()).arg(ui->ADMIN->currentText().left(5)).arg(ui->otheredit->text()).arg(ui->ID->currentText())))
    {
        QMessageBox::information(this,"修改成功","SUCCESSFUL");
        //将标签设置为部门管理员
        qu3.exec(QString("UPDATE account SET type='1' WHERE eno='%1'").arg(ui->ID->currentText()));
        //将此成员设置为本部门成员
        tableset();
        comboxset();
    }
    else
    {
       QMessageBox::warning(this,"修改失败","UNSUCCESSFUL");
    }
}


void depm::on_conf_dele_clicked()
{
    QSqlQuery qu1(db);
    qu1.exec(QString("DELETE department WHERE dno='%1'").arg(ui->ID_2->currentText()));
    tableset();
    comboxset();
}

