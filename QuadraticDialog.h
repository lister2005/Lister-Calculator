#ifndef QUADRATICDIALOG_H
#define QUADRATICDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class QuadraticDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuadraticDialog(QWidget *parent = nullptr);
    ~QuadraticDialog();

    double getA();
    double getB();
    double getC();

private:
    QLineEdit *aLineEdit;
    QLineEdit *bLineEdit;
    QLineEdit *cLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // QUADRATICDIALOG_H
