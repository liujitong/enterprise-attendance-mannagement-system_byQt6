#ifndef DEP_FENPEI_H
#define DEP_FENPEI_H

#include <QDialog>

namespace Ui {
class dep_fenpei;
}

class dep_fenpei : public QDialog
{
    Q_OBJECT


public:
    void tableset();
    void combox_emp_set();
    void combox_dep_set();
    explicit dep_fenpei(QWidget *parent = nullptr);
    ~dep_fenpei();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dep_fenpei *ui;
};

#endif // DEP_FENPEI_H
