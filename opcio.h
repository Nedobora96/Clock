#ifndef OPCIO_H
#define OPCIO_H

#include <QDialog>
#include <QString>

namespace Ui {
class Opcio;
}

class Opcio : public QDialog
{
    Q_OBJECT

public:
    explicit Opcio(QWidget *parent = 0);
    QString alarm;
    ~Opcio();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Opcio *ui;
};

#endif // OPCIO_H
