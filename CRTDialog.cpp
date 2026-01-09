#include "CRTDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

CRTDialog::CRTDialog(QWidget *parent)
    : QDialog(parent)
{
    equationTable = new QTableWidget(2, 3);
    equationTable->setHorizontalHeaderLabels({"a", "b", "m"});
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    addRowButton = new QPushButton("Add Row");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(addRowButton);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addWidget(equationTable);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &CRTDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &CRTDialog::reject);
    connect(addRowButton, &QPushButton::clicked, this, [=]() {
        equationTable->insertRow(equationTable->rowCount());
    });
}

CRTDialog::~CRTDialog()
{
}

std::vector<CalculatorEngine::CRTEquation> CRTDialog::getEquations()
{
    std::vector<CalculatorEngine::CRTEquation> equations;
    for (int i = 0; i < equationTable->rowCount(); ++i) {
        long long a = equationTable->item(i, 0) ? equationTable->item(i, 0)->text().toLongLong() : 0;
        long long b = equationTable->item(i, 1) ? equationTable->item(i, 1)->text().toLongLong() : 0;
        long long m = equationTable->item(i, 2) ? equationTable->item(i, 2)->text().toLongLong() : 1;
        equations.push_back({a, b, m});
    }
    return equations;
}
