#ifndef RESI_H
#define RESI_H

#include <QDialog>

namespace Ui {
class resi;
}

class resi : public QDialog
{
    Q_OBJECT

public:
    explicit resi(QWidget *parent = nullptr);
    ~resi();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::resi *ui;
};

#endif // RESI_H
