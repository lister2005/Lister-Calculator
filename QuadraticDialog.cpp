#include "QuadraticDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

QuadraticDialog::QuadraticDialog(QWidget *parent)
    : QDialog(parent)
{
    aLineEdit = new QLineEdit;
    bLineEdit = new QLineEdit;
    cLineEdit = new QLineEdit;
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *inputLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    inputLayout->addWidget(new QLabel("a:"));
    inputLayout->addWidget(aLineEdit);
    inputLayout->addWidget(new QLabel("b:"));
    inputLayout->addWidget(bLineEdit);
    inputLayout->addWidget(new QLabel("c:"));
    inputLayout->addWidget(cLineEdit);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &QuadraticDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QuadraticDialog::reject);
}

QuadraticDialog::~QuadraticDialog()
{
}

double QuadraticDialog::getA()
{
    return aLineEdit->text().toDouble();
}

double QuadraticDialog::getB()
{
    return bLineEdit->text().toDouble();
}

double QuadraticDialog::getC()
{
    return cLineEdit->text().toDouble();
}
