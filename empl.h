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
    explicit empl(QWidget *parent = nullptr);
    ~empl();

private:
    Ui::empl *ui;
};

#endif // EMPL_H
