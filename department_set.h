#ifndef DEPARTMENT_SET_H
#define DEPARTMENT_SET_H

#include <QDialog>

namespace Ui {
class department_set;
}

class department_set : public QDialog
{
    Q_OBJECT

public:
    explicit department_set(QWidget *parent = nullptr);
    ~department_set();

private slots:
    void on_pushButton_clicked();

private:
    Ui::department_set *ui;
};

#endif // DEPARTMENT_SET_H
