#ifndef EMPL_H
#define EMPL_H

#include <QDialog>

namespace Ui {
class empl;
}

class empl : public QDialog
{
    Q_OBJECT

public:
    void tableset();
    void comboxset();
    void combox_dep_set(QString a);
    explicit empl(QWidget *parent = nullptr);
    ~empl();

private slots:

    void on_eid_currentTextChanged(const QString &arg1);

    void on_conf_edit_clicked();

    void on_conf_dele_clicked();

private:
    Ui::empl *ui;
};

#endif // EMPL_H
