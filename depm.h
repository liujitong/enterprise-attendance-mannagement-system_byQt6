#ifndef DEPM_H
#define DEPM_H

#include <QDialog>

namespace Ui {
class depm;
}

class depm : public QDialog
{
    Q_OBJECT

public:
    void tableset();
    void comboxset();
    void admincomboxset(QString arf);
    explicit depm(QWidget *parent = nullptr);
    ~depm();

private slots:

    void on_ID_currentIndexChanged(int index);

    void on_conf_edit_clicked();

    void on_conf_dele_clicked();

private:
    Ui::depm *ui;
};

#endif // DEPM_H
