#include "login.h"
#include "ui_login.h"
#include "dep_admin.h"
#include <QString>
#include <QMessageBox>
#include "publicdb.h"
#include "common_em.h"
#include "superadmin.h"
#include "resi.h"
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString eno=ui->eno->text();
    QString pss=ui->password->text();
    QString str=QString("select type from account where eno='%1' and code='%2';").arg(eno).arg(pss);
    QSqlQuery sqltext(db);
    sqltext.exec(str);
    if(eno==""||pss=="")
    {
       QMessageBox::critical(this,"登录情况","请输入账号或密码");
        return ;
    }
    if(sqltext.first())
    {
        //type0->超级管理员，type1->部门管理员,type2->普通员工
        QMessageBox::information(this,"登录情况","登录成功");//后接管理界面
        if(sqltext.value(0).toString()=="0")
        {
            //超级管理员界面
            superadmin *spa=new superadmin();
            spa->eno=ui->eno->text();
            spa->superadminset();
            spa->show();
            this->close();
        }
        if(sqltext.value(0).toString()=="1")
        {
            //部门管理员界面
            dep_admin *dpc=new dep_admin();
            dpc->eno=eno;
            dpc->setupfirst();
            dpc->show();
            this->close();
        }
        if(sqltext.value(0).toString()=="2")
        {
        //员工界面
            common_em *ce=new common_em();
            ce->eno=ui->eno->text();
            ce->setupfirst();
            ce->tableset();
            ce->show();
            this->close();
        }
    }
    else
        QMessageBox::critical(this,"登录情况","密码不正确！");
}

void login::on_pushButton_2_clicked()
{
    resi *reg=new resi();
    reg->show();
}

