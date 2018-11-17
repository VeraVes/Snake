#ifndef RECORDS_H
#define RECORDS_H

#include <QDialog>

namespace Ui {
class Records;
}

class Records : public QDialog
{
    Q_OBJECT

public:
    explicit Records(QWidget *parent = 0);
    ~Records();

private:
    Ui::Records *ui;
};

#endif // RECORDS_H
