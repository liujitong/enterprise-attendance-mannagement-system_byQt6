#include "dep_admin.h"
#include "ui_dep_admin.h"
#include "publicdb.h"
#include "QMessageBox"
#include "qdebug.h"
int flagc=0;
dep_admin::dep_admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::dep_admin)
{
    ui->setupUi(this);
}
dep_admin::~dep_admin()
{
    delete ui;
}
QString s;//用以传递参数
int type=0;//表和精准查找的参数
void dep_admin::setupfirst()
{
    //设置两个输入框都为当前时间
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    QSqlQuery query(db),qu2(db),qu3(db);
    ui->comboBox->clear();
    qu2.exec(QString("SELECT dno from employee WHERE eno='%1'").arg(eno));
    if(qu2.first()) this->dno=qu2.value(0).toString();//部门序号初始化
    query.exec(QString("SELECT e.eno, e.ename FROM employee e LEFT JOIN department d ON e.dno = d.dno WHERE e.dno = '%1' AND e.eno IN (SELECT eno FROM account WHERE type = '2');").arg(dno));
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString()+" "+query.value(1).toString());
    }

    //数据表格遍历初始化
    ui->tableWidget->setHorizontalHeaderLabels({"编号","姓名","打卡日期","打卡时间","类型","请假理由"});
    query.exec(QString("SELECT e.eno, e.ename, CONVERT(date, a.time) AS 'date', CONVERT(time(3), a.time) AS 'time', CASE a.type WHEN '1' THEN '上班' WHEN '2' THEN '下班' WHEN '3' THEN '请假' END AS 'type', ISNULL(a.other,'不适用') AS 'other' FROM employee e LEFT JOIN attendance_sheet a ON e.eno = a.eno WHERE e.dno='%1' AND (a.time IS NOT NULL OR a.type IS NOT NULL)").arg(dno));
    int row = 0;
    while(query.next())
    {
        ui->tableWidget->setRowCount(row+1);
        for(int column = 0; column < query.record().count(); column++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            ui->tableWidget->setItem(row,column,item);
        }
        row++;
    }
}

void dep_admin::on_radioButton_2_clicked(bool checked)
{
    if(checked)
    {
        flagc=2;
    }
    else
    {
        flagc=0;
    }
}

//全部记录为1，按时间筛选为2，未选择为0；


void dep_admin::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        flagc=1;
    }
    else
    {
        flagc=0;
    }
}


void dep_admin::on_pushButton_clicked()
{
    QSqlQuery query(db);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels({"编号","姓名","打卡日期","打卡时间","类型","请假理由"});
    if(flagc==0) setupfirst();
    if(flagc==1)
    query.exec(QString("SELECT e.eno, e.ename, CONVERT(date, a.time) AS 'date', CONVERT(time(3), a.time) AS 'time', CASE a.type WHEN '1' THEN '上班' WHEN '2' THEN '下班' WHEN '3' THEN '请假' END AS 'type', ISNULL(a.other,'不适用') AS 'other' FROM employee e LEFT JOIN attendance_sheet a ON e.eno = a.eno WHERE e.eno='%1' AND (a.time IS NOT NULL OR a.type IS NOT NULL)").arg(ui->comboBox->currentText().left(5)));
    if(flagc==2)
    {
        //判定时间是否合法
        if(ui->dateEdit->date()>ui->dateEdit_2->date())
        {
            QMessageBox::warning(this,"错误","起始时间不能大于结束时间");
            return;
        }
        query.exec(QString("SELECT e.eno, e.ename, CONVERT(date, a.time) AS 'date', CONVERT(time(3), a.time) AS 'time', CASE a.type WHEN '1' THEN '上班' WHEN '2' THEN '下班' WHEN '3' THEN '请假' END AS 'type', ISNULL(a.other,'不适用') AS 'other' FROM employee e LEFT JOIN attendance_sheet a ON e.eno = a.eno WHERE e.eno='%1' AND (a.time IS NOT NULL OR a.type IS NOT NULL) AND CONVERT(date, a.time) BETWEEN '%2' AND '%3'").arg(ui->comboBox->currentText().left(5)).arg(ui->dateEdit->date().toString("yyyy-MM-dd")).arg(ui->dateEdit_2->date().toString("yyyy-MM-dd")));
    }
    int row = 0;
    while(query.next())
    {
        ui->tableWidget->setRowCount(row+1);
        for(int column = 0; column < query.record().count(); column++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());

            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            ui->tableWidget->setItem(row,column,item);
        }
        row++;
    }
}


void dep_admin::on_tableWidget_cellClicked(int row, int column)
{
    if(column++){
    }//这里是为啥呢？看Warning有点强迫症，column一直没有用;
    ui->select->setText(ui->tableWidget->item(row,0)->text()+" "+ui->tableWidget->item(row,1)->text());
    s=ui->tableWidget->item(row,2)->text()+" "+ui->tableWidget->item(row,3)->text();
    s = s.trimmed();//去掉头尾空格
    QDateTime time = QDateTime::fromString(s,"yyyy-M-d hh:mm:ss.zzz");
    ui->dateTimeEdit->setDateTime(time);
    ui->status->clear();
    if(ui->tableWidget->item(row,4)->text()=="上班")
    {
        type=1;
        ui->status->clear();
        ui->status->addItem("1 上班");
        ui->status->addItem("2 下班");
        ui->status->addItem("3 请假");
    }
    if(ui->tableWidget->item(row,4)->text()=="下班")
    {
        type=2;
        ui->status->clear();
        ui->status->addItem("2 下班");
        ui->status->addItem("1 上班");
        ui->status->addItem("3 请假");
    }
    if(ui->tableWidget->item(row,4)->text()=="请假")
    {
        type=3;
        ui->status->clear();
        ui->status->addItem("3 请假");
        ui->status->addItem("1 上班");
        ui->status->addItem("2 下班");
        ui->other->setText(ui->tableWidget->item(row,5)->text());
    }
}


void dep_admin::on_status_currentTextChanged(const QString &arg1)
{
    if(arg1=="1 上班"||arg1=="2 下班")
    {
        ui->other->setEnabled(false);
    }
    else
    {
        ui->other->setEnabled(true);
    }
}


void dep_admin::on_pushButton_2_clicked()
{
    if(ui->select->text()==""){
        QMessageBox::warning(this,"错误","没选中任何一个");
        return;
    }
    QSqlQuery qu(db);
    if(ui->status->currentText()=="3 请假")
    {
        if(ui->other->text()=="")
        {
            QMessageBox::warning(this,"错误","没有请假理由");
        }
        else
        {
            if(qu.exec(QString("UPDATE attendance_sheet SET type='3',time='%1',other='%2' WHERE eno='%3' AND time='%4' AND type='%5' ").arg(ui->dateTimeEdit->dateTime().toString("yyyy/M/d hh:mm:ss.zzz")).arg(ui->other->text()).arg(ui->select->text().left(5)).arg(s).arg(type)))
            {
                QMessageBox::information(this,"成功","更新成功");
                on_pushButton_clicked();
            }
            else{
                QMessageBox::warning(this,"错误","更新失败");
            }
        }
    }
    else{
        if(qu.exec(QString("UPDATE attendance_sheet SET type='%1',time='%2',other=NULL WHERE eno='%3' AND time='%4' AND type='%5' ").arg(ui->status->currentText().left(1)).arg(ui->dateTimeEdit->dateTime().toString("yyyy/M/d hh:mm:ss.zzz")).arg(ui->select->text().left(5)).arg(s).arg(type)))
        {
            QMessageBox::information(this,"成功","更新成功");
            on_pushButton_clicked();
        }
        else{
            QMessageBox::warning(this,"错误","更新失败");
        }
    }
}


void dep_admin::on_pushButton_3_clicked()
{
    QSqlQuery qb(db);
    if(qb.exec(QString("DELETE FROM attendance_sheet WHERE eno='%1' AND time='%2' AND type='%3'").arg(ui->select->text().left(5)).arg(s).arg(type)))
    {
        QMessageBox::information(this,"成功","删除成功");
        on_pushButton_clicked();
    }
    else
    {
        QMessageBox::warning(this,"错误","更新失败");
    }
}

