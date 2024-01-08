#include "login.h"
#include "publicdb.h"
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QFont>
bool OpenDatabase()
{
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
        QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
        return false;                                   //打开失败
    }
    return true;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.addLibraryPath(a.applicationDirPath() + "/plugins");
    //加载样式表
    QFile file(":/css/index.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }

    //全局字体
    QFont font("宋体", 10);
    a.setFont(font);

    if(!OpenDatabase())
        return 1;
    login *ld=new login();
    ld->show();

    return a.exec();
}
