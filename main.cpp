#include "login.h"
//#include "publicdb.h"
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QFont>
bool OpenDatabase()
{

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
