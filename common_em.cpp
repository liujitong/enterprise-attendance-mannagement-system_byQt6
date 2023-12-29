#include "common_em.h"
#include "ui_common_em.h"
#include "QMessageBox"
#include "publicdb.h"
int flag=0;//0->啥也没选中，1->蛇牙
common_em::common_em(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::common_em)
{
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
}

void common_em::tableset()//设置table
{
    QSqlQuery query(db),qu2(db);
    qu2.exec(QString("SELECT ename FROM employee WHERE eno='%1'").arg(eno));
    if(qu2.first())
    {
        ui->name->setText(qu2.value(0).toString()+"的考勤记录");
    }
    else
    {
        ui->name->setText(eno+"考勤");
    }
    ui->table->setHorizontalHeaderLabels({"日期","时间","类别","请假理由"});
    query.exec(QString("SELECT CONVERT(date, time) AS 'date', CONVERT(time, time) AS 'time', CASE type WHEN '1' THEN '上班' WHEN '2' THEN '下班' WHEN '3' THEN '请假' END AS 'type', ISNULL(other,'不适用') FROM attendance_sheet WHERE eno='%1'").arg(eno));
    int row = 0;
    while(query.next())
    {
        ui->table->setRowCount(row+1);
        for(int column = 0; column < query.record().count(); column++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());

            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            ui->table->setItem(row,column,item);
        }
        row++;
    }
}
common_em::~common_em()
{
    delete ui;
}

void common_em::on_type1_clicked(bool checked)
{
    ui->lineEdit->setEnabled(false);
    if(checked)
    {
        flag=1;
    }
    else
    {
        flag=0;
    }
}


void common_em::on_tyep2_clicked(bool checked)
{
    ui->lineEdit->setEnabled(false);
    if(checked)
    {
        flag=2;
    }
    else
    {
        flag=0;
    }
}



void common_em::on_type3_clicked(bool checked)
{
    if(checked)
    {
        flag=3;
        ui->lineEdit->setEnabled(true);
    }
    else
    {
        flag=0;
        ui->lineEdit->setEnabled(false);
    }
}


void common_em::on_pushButton_clicked()
{
    QSqlQuery qu(db);
    if(flag==0)
    {
        QMessageBox::warning(this,"错误","您未选中任何一个打卡方式");
    }
    if(flag==1)
    {
        if(qu.exec(QString("INSERT INTO attendance_sheet (eno,type,time) VALUES('%1',1,GETDATE())").arg(eno)))
        {
            QMessageBox::information(this,"打卡成功","上班愉快");
        }
        else {
            QMessageBox::warning(this,"错误","上班打卡失败");
        }
    }
    if(flag==2)
    {
        if(qu.exec(QString("INSERT INTO attendance_sheet (eno,type,time) VALUES('%1',2,GETDATE())").arg(eno)))
        {
            QMessageBox::information(this,"打卡成功","下班愉快,再见");
        }
        else {
            QMessageBox::warning(this,"错误","下班打卡失败");
        }
    }
    if(flag==3)
    {
        if(ui->lineEdit->text()=="")
        {
             QMessageBox::warning(this,"错误","请假需要填写请假理由");
        }
        else{
            if(qu.exec(QString("INSERT INTO attendance_sheet VALUES('%1','3',GETDATE(),'%2')").arg(eno).arg(ui->lineEdit->text())))
            {
                QMessageBox::information(this,"请假成功","您的信息已经提交");
            }
            else {
                QMessageBox::warning(this,"错误","信息提交失败");
            }
        }
    }

}


void common_em::on_sea_time_clicked()
{
    //判定时间是否合法
    if(ui->dateEdit->date()>ui->dateEdit_2->date())
    {
        QMessageBox::warning(this,"错误","起始时间不能大于结束时间");
        return;
    }
    ui->table->clear();
    ui->table->setRowCount(0);
    ui->table->setHorizontalHeaderLabels({"日期","时间","类别","请假理由"});
    QSqlQuery query(db);
    query.exec(QString("SELECT CONVERT(date, time) AS 'date', CONVERT(time, time) AS 'time', CASE type WHEN '1' THEN '上班' WHEN '2' THEN '下班' WHEN '3' THEN '请假' END AS 'type', ISNULL(other,'不适用') FROM attendance_sheet WHERE eno='%1' AND CONVERT(date, time) BETWEEN '%2' AND '%3'").arg(eno).arg(ui->dateEdit->date().toString("yyyy-MM-dd")).arg(ui->dateEdit_2->date().toString("yyyy-MM-dd")));
    int row = 0;
    while(query.next())
    {
        ui->table->setRowCount(row+1);
        for(int column = 0; column < query.record().count(); column++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());

            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            ui->table->setItem(row,column,item);
        }
        row++;
    }
}


void common_em::on_sea_all_clicked()
{
    tableset();
}

