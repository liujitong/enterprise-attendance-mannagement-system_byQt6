#include "pss_change.h"
#include "ui_pss_change.h"
#include <QRegularExpression>
#include <QMessageBox>
#include "publicdb.h"
pss_change::pss_change(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::pss_change)
{
    ui->setupUi(this);
}

pss_change::~pss_change()
{
    delete ui;
}

void pss_change::on_confirm_clicked()
{
    //确认原密码匹配
    QSqlQuery query(db),qu2(db);
    static QRegularExpression rpss(".{8,}");
    query.exec(QString("SELECT password FROM employee WHERE eno = '%1'").arg(eno));
    if(query.first())
    {
        if(query.value(0).toString()!=ui->old_pss->text())//原密码匹配
        {
            QMessageBox::warning(this,"错误","原密码错误");
            return;
        }
    }

    if(ui->pss_new->text()!=ui->pss_new_2->text())//输入符合要求
    {
        QMessageBox::warning(this,"错误","两次输入的密码不一致");
    }
    else if(rpss.match(ui->pss_new->text()).hasMatch()==false)//判断密码长度符合要求
    {
        QMessageBox::warning(this,"错误","密码长度不足8位");
    }
    else
    {
        if(qu2.exec(QString("UPDATE account SET code = '%1' WHERE eno = '%2'").arg(ui->pss_new->text()).arg(eno))){
        QMessageBox::information(this,"成功","密码修改成功");
        this->close();
        }
        else{
            QMessageBox::warning(this,"错误","密码修改失败");
        }
    }
}

