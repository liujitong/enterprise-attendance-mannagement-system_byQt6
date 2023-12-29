#ifndef COMMON_EM_H
#define COMMON_EM_H

#include <QMainWindow>

namespace Ui {
class common_em;
}

class common_em : public QMainWindow
{
    Q_OBJECT

public:
    QString eno;
    void tableset();
    explicit common_em(QWidget *parent = nullptr);
    ~common_em();

private slots:
    void on_type1_clicked(bool checked);

    void on_tyep2_clicked(bool checked);

    void on_type3_clicked(bool checked);

    void on_pushButton_clicked();

    void on_sea_time_clicked();

    void on_sea_all_clicked();

private:
    Ui::common_em *ui;
};

#endif // COMMON_EM_H
