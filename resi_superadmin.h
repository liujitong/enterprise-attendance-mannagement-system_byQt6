#ifndef RESI_SUPERADMIN_H
#define RESI_SUPERADMIN_H

#include <QDialog>

namespace Ui {
class resi_superadmin;
}

class resi_superadmin : public QDialog
{
    Q_OBJECT

public:
    explicit resi_superadmin(QWidget *parent = nullptr);
    ~resi_superadmin();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::resi_superadmin *ui;
};

#endif // RESI_SUPERADMIN_H
