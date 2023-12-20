#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include <QMainWindow>

namespace Ui {
class superadmin;
}

class superadmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit superadmin(QWidget *parent = nullptr);
    void superadminset(QString eno);
    ~superadmin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::superadmin *ui;
};

#endif // SUPERADMIN_H
