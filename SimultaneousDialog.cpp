#include "SimultaneousDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>

SimultaneousDialog::SimultaneousDialog(QWidget *parent)
    : QDialog(parent)
{
    a1LineEdit = new QLineEdit;
    b1LineEdit = new QLineEdit;
    c1LineEdit = new QLineEdit;
    a2LineEdit = new QLineEdit;
    b2LineEdit = new QLineEdit;
    c2LineEdit = new QLineEdit;
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(new QLabel("Equation 1:"), 0, 0);
    mainLayout->addWidget(new QLabel("a:"), 1, 0);
    mainLayout->addWidget(a1LineEdit, 1, 1);
    mainLayout->addWidget(new QLabel("b:"), 1, 2);
    mainLayout->addWidget(b1LineEdit, 1, 3);
    mainLayout->addWidget(new QLabel("c:"), 1, 4);
    mainLayout->addWidget(c1LineEdit, 1, 5);

    mainLayout->addWidget(new QLabel("Equation 2:"), 2, 0);
    mainLayout->addWidget(new QLabel("a:"), 3, 0);
    mainLayout->addWidget(a2LineEdit, 3, 1);
    mainLayout->addWidget(new QLabel("b:"), 3, 2);
    mainLayout->addWidget(b2LineEdit, 3, 3);
    mainLayout->addWidget(new QLabel("c:"), 3, 4);
    mainLayout->addWidget(c2LineEdit, 3, 5);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout, 4, 0, 1, 6);

    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &SimultaneousDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &SimultaneousDialog::reject);
}

SimultaneousDialog::~SimultaneousDialog()
{
}

double SimultaneousDialog::getA1() { return a1LineEdit->text().toDouble(); }
double SimultaneousDialog::getB1() { return b1LineEdit->text().toDouble(); }
double SimultaneousDialog::getC1() { return c1LineEdit->text().toDouble(); }
double SimultaneousDialog::getA2() { return a2LineEdit->text().toDouble(); }
double SimultaneousDialog::getB2() { return b2LineEdit->text().toDouble(); }
double SimultaneousDialog::getC2() { return c2LineEdit->text().toDouble(); }
