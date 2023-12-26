#ifndef DEP_CHANGE_H
#define DEP_CHANGE_H

#include <QDialog>

namespace Ui {
class dep_change;
}

class dep_change : public QDialog
{
    Q_OBJECT

public:
    void tableset();
    void combox_emp_set();
    void combox_dep_set();
    explicit dep_change(QWidget *parent = nullptr);
    ~dep_change();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dep_change *ui;
};

#endif // DEP_CHANGE_H
