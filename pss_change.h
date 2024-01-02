#ifndef PSS_CHANGE_H
#define PSS_CHANGE_H

#include <QWidget>

namespace Ui {
class pss_change;
}

class pss_change : public QWidget
{
    Q_OBJECT

public:
    QString eno;
    explicit pss_change(QWidget *parent = nullptr);
    ~pss_change();

private slots:
    void on_confirm_clicked();

private:
    Ui::pss_change *ui;
};

#endif // PSS_CHANGE_H
