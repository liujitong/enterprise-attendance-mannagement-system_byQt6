#include "empl.h"
#include "ui_empl.h"
#include "publicdb.h"
#include "QMessageBox"
empl::empl(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::empl)
{
    ui->setupUi(this);
    tableset();
    comboxset();
}
void empl::comboxset()
{
    ui->eid->clear();
    ui->eid_2->clear();
    QSqlQuery query(db);
    query.exec("SELECT eno from employee ");
    while(query.next())
    {
        ui->eid->addItem(query.value(0).toString());
        ui->eid_2->addItem(query.value(0).toString());
    }
}
void empl::combox_dep_set(QString a)
{
    ui->dep->clear();
    QSqlQuery query(db), qu2(db), qu3(db);
    // 查询当前员工所在部门
    query.exec(QString("SELECT d.dno,d.dname FROM employee e LEFT JOIN department d ON e.dno = d.dno WHERE e.eno='%1'AND d.dno IS NOT NULL; ").arg(a));
    if (query.first())
    {
        if (query.value(0).toString() != "")
            ui->dep->addItem(query.value(0).toString() + " " + query.value(1).toString());
    }
    // 查询其他可选部门
    qu2.exec(QString("SELECT DISTINCT d.dno, d.dname FROM employee e LEFT JOIN department d ON e.dno = d.dno WHERE (e.eno != '%1' OR e.dno IS NULL)  AND d.dno IS NOT NULL  AND e.eno <> '%1' AND d.dno NOT IN (SELECT dno FROM employee WHERE eno = '%1');").arg(a));
    while (qu2.next())
    {
        if (qu2.value(0).toString() != "")
            ui->dep->addItem(qu2.value(0).toString() + " " + qu2.value(1).toString());
    }
    // 如果没有其他可选部门，则显示所有部门
    if (ui->dep->count() == 0)
    {
        qu3.exec("SELECT DISTINCT d.dno,d.dname FROM employee e LEFT JOIN department d ON e.dno = d.dno");
        while (qu3.next())
        {
            if (qu3.value(0).toString() != "")
                ui->dep->addItem(qu3.value(0).toString() + " " + qu3.value(1).toString());
        }
    }
}
void empl::tableset()//设置table
{
    ui->ALL->setHorizontalHeaderLabels({"编号","姓名","所在部门","性别","手机号"});
    QSqlQuery query(db);
    query.exec("SELECT e.eno, e.ename, ISNULL(d.dname,'无部门') AS '部门名称', ISNULL(e.gendar,'N'), ISNULL(e.telephone,'待补充') FROM employee e LEFT JOIN department d ON e.dno = d.dno;");
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
empl::~empl()
{
    delete ui;
}

void empl::on_eid_currentTextChanged(const QString &arg1)
{
    QSqlQuery qd(db);
    qd.exec(QString("SELECT e.ename, e.gendar, e.telephone FROM employee e LEFT JOIN department d ON e.dno = d.dno WHERE e.eno='%1';").arg(arg1));
    if(qd.first())
    {
        ui->nameedit->setText(qd.value(0).toString());
        ui->gen->clear();
        if(qd.value(1).toString()=="女")
        {
            ui->gen->addItem("女");
            ui->gen->addItem("男");
        }
        else
        {
            ui->gen->addItem("男");
            ui->gen->addItem("女");
        }
        ui->telephone->setText(qd.value(2).toString());
    }
    combox_dep_set(arg1);

}

//确认修改
void empl::on_conf_edit_clicked()
{
    QSqlQuery query(db);
    static QRegularExpression enostd( "[0-9]{5}" );//设置正则表达式-部门账号
    static QRegularExpression enamestd("(!(%[^吖-座]%))||[^a-z]%|[^A-Z]%");
    static QRegularExpression etelstd("[0-9]{11,12}");
    if(!enamestd.match(ui->nameedit->text()).hasMatch())//姓名匹配
    {
        QMessageBox::warning(this,"姓名输入错误","姓名只能是中文或英文");

    }
    else if(ui->telephone->text()=="")//电话号码为空
    {
        if(query.exec(QString("UPDATE employee SET ename='%1',dno='%2',gendar='%3' WHERE eno='%4'").arg(ui->nameedit->text()).arg(ui->dep->currentText().left(3)).arg(ui->gen->currentText()).arg(ui->eid->currentText())))
        {
            tableset();
            comboxset();
            QMessageBox::information(this,"修改成功","Successful");
        }
        else
        {
            QMessageBox::warning(this,"出错了","更改未成功");
        }
    }//电话号码匹配
    else if(!etelstd.match(ui->telephone->text()).hasMatch())
    {
        QMessageBox::warning(this,"电话输出错误","电话号码长度限制在11-12位");
    }
    else//都满足的情况之下
    {
        if(query.exec(QString("UPDATE employee SET ename='%1',dno='%2',gendar='%3',telephone='%4' WHERE eno='%5'").arg(ui->nameedit->text()).arg(ui->dep->currentText().left(3)).arg(ui->gen->currentText()).arg(ui->telephone->text()).arg(ui->eid->currentText())))
        {
            QMessageBox::information(this,"修改成功","Successful");
            tableset();
            comboxset();
        }
        else
        {
            QMessageBox::warning(this,"出错了","更改未成功");
        }
    }

}


void empl::on_conf_dele_clicked()
{
    QSqlQuery qu1(db);
    if(qu1.exec(QString("DELETE employee WHERE eno='%1'").arg(ui->eid_2->currentText())))
    {
        QMessageBox::information(this,"删除成功","Sucessful");
    }
    else
    {
        QMessageBox::warning(this,"出错了","删除未成功");
    }
    tableset();
    comboxset();
}

