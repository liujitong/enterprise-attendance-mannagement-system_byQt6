#ifndef EMPLOYEE_SET_H
#define EMPLOYEE_SET_H

#include <QDialog>

namespace Ui {
class employee_set;
}

class employee_set : public QDialog
{
    Q_OBJECT

public:
    void combox_dep_set();
    void combox_gen_set();
    explicit employee_set(QWidget *parent = nullptr);
    ~employee_set();

private slots:
    void on_pushButton_clicked();

private:
    Ui::employee_set *ui;
};

#endif // EMPLOYEE_SET_H
