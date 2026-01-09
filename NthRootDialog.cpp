#include "NthRootDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

NthRootDialog::NthRootDialog(QWidget *parent)
    : QDialog(parent)
{
    nLineEdit = new QLineEdit;
    xLineEdit = new QLineEdit;
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    nLineEdit->setPlaceholderText("Enter n (root)");
    xLineEdit->setPlaceholderText("Enter x (number)");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *nLayout = new QHBoxLayout;
    QHBoxLayout *xLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    nLayout->addWidget(new QLabel("n:"));
    nLayout->addWidget(nLineEdit);

    xLayout->addWidget(new QLabel("x:"));
    xLayout->addWidget(xLineEdit);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(nLayout);
    mainLayout->addLayout(xLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Nth Root Input");

    connect(okButton, &QPushButton::clicked, this, &NthRootDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &NthRootDialog::reject);
}

double NthRootDialog::getN() const
{
    return nLineEdit->text().toDouble();
}

double NthRootDialog::getX() const
{
    return xLineEdit->text().toDouble();
}