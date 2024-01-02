#ifndef DEP_ADMIN_H
#define DEP_ADMIN_H

#include <QMainWindow>
#include<QCloseEvent>
namespace Ui {
class dep_admin;
}

class dep_admin : public QMainWindow
{
    Q_OBJECT

public:
    QString eno;
    QString dno;
    void setupfirst();
    void closeEvent(QCloseEvent *e);
    explicit dep_admin(QWidget *parent = nullptr);
    ~dep_admin();

private slots:
    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_clicked(bool checked);

    void on_pushButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_status_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void open_change_pss();

private:
    Ui::dep_admin *ui;
};

#endif // DEP_ADMIN_H
