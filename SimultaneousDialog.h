#ifndef SIMULTANEOUSDIALOG_H
#define SIMULTANEOUSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class SimultaneousDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimultaneousDialog(QWidget *parent = nullptr);
    ~SimultaneousDialog();

    double getA1();
    double getB1();
    double getC1();
    double getA2();
    double getB2();
    double getC2();

private:
    QLineEdit *a1LineEdit;
    QLineEdit *b1LineEdit;
    QLineEdit *c1LineEdit;
    QLineEdit *a2LineEdit;
    QLineEdit *b2LineEdit;
    QLineEdit *c2LineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // SIMULTANEOUSDIALOG_H
