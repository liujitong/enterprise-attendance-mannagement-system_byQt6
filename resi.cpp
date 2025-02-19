#include "resi.h"
#include "ui_resi.h"
#include "publicdb.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>
resi::resi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resi)
{

    ui->setupUi(this);
}

resi::~resi()
{
    delete ui;
}

void resi::on_pushButton_2_clicked()
{
    QSqlQuery qb(db);
    QString username;
    QString name;
    QString pss;
    username=ui->username->text();
    name=ui->name1->text();
    pss=ui->password->text();
    static QRegularExpression re( "[0-9]{5}" );//设置正则表达式
    static QRegularExpression rpss(".{8,}");
    static QRegularExpression rname("(!(%[^吖-座]%))||[^a-z]%|[^A-Z]%");
    if(!((re.match(username)).hasMatch()))
    {
     QMessageBox::warning(this,"用户名输入错误","用户名格式为5位数字");//后接管理界面
    }
    else if(!(rpss.match(pss)).hasMatch())
    {
     QMessageBox::warning(this,"密码输入有误","密码至少8位");
    }
    else if(!(rname.match(name)).hasMatch())
    {
        QMessageBox::warning(this,"姓名有错误","姓名为中文或英文");
    }
    else  {
     if(qb.exec(QString("INSERT INTO employee (eno,ename) VALUES('%1','%2')").arg(username).arg(name)))
     {
        QSqlQuery qb2(db);
         qb2.exec(QString("UPDATE account SET code='%1' WHERE eno='%2'").arg(pss).arg(username));
         //提示窗格
         QMessageBox::information(this,"注册成功",QString("牢记您的账号名：%1和密码:%2").arg(username).arg(pss));
         this->close();
     }
     else {
         QMessageBox::critical(this,"注册失败","请检查用户名是否重复");
        }
    }
}

