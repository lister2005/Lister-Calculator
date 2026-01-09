#ifndef NTHROOTDIALOG_H
#define NTHROOTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class NthRootDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NthRootDialog(QWidget *parent = nullptr);
    double getN() const;
    double getX() const;

private:
    QLineEdit *nLineEdit;
    QLineEdit *xLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // NTHROOTDIALOG_H