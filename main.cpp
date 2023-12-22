#include "login.h"
#include "publicdb.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

bool OpenDatabase()
{
       //数据库驱动类型为SQL Server
    qDebug()<<"ODBC driver?"<<db.isValid();
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                               "SERVER=%1;" //服务器名称
                               "DATABASE=%2;"//数据库名
                               "UID=%3;"           //登录名
                               "PWD=%4;"        //密码
                               ).arg("127.0.0.1,1433")//默认的sqlserver的端口号是1433
                           .arg("EAS_qt")
                           .arg("EAS_ADMIN")
                           .arg("liujitong0")
                       );
    if(!db.open())                                      //打开数据库
    {
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
        return false;                                   //打开失败
    }
    else
        qDebug()<<"database open success!";
    return true;

}

int main(int argc, char *argv[])
{

    if(!OpenDatabase())
        return 1;

    QApplication a(argc, argv);
    login *ld=new login();
    ld->show();
    return a.exec();
}
