#include "MatrixDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>

MatrixDialog::MatrixDialog(QWidget *parent)
    : QDialog(parent)
{
    matrixAWidget = new QTableWidget(3, 3);
    matrixBWidget = new QTableWidget(3, 3);
    operationComboBox = new QComboBox;
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    matrixARowsSpinBox = new QSpinBox;
    matrixARowsSpinBox->setRange(1, 10);
    matrixAColsSpinBox = new QSpinBox;
    matrixAColsSpinBox->setRange(1, 10);
    matrixBRowsSpinBox = new QSpinBox;
    matrixBRowsSpinBox->setRange(1, 10);
    matrixBColsSpinBox = new QSpinBox;
    matrixBColsSpinBox->setRange(1, 10);

    matrixARowsSpinBox->setValue(3);
    matrixAColsSpinBox->setValue(3);
    matrixBRowsSpinBox->setValue(3);
    matrixBColsSpinBox->setValue(3);

    operationComboBox->addItem("Add");
    operationComboBox->addItem("Multiply");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *matrixLayout = new QHBoxLayout;
    QHBoxLayout *controlsLayout = new QHBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QVBoxLayout *matrixALayout = new QVBoxLayout;
    QHBoxLayout *matrixAControlsLayout = new QHBoxLayout;
    matrixAControlsLayout->addWidget(new QLabel("Rows:"));
    matrixAControlsLayout->addWidget(matrixARowsSpinBox);
    matrixAControlsLayout->addWidget(new QLabel("Cols:"));
    matrixAControlsLayout->addWidget(matrixAColsSpinBox);
    matrixALayout->addLayout(matrixAControlsLayout);
    matrixALayout->addWidget(matrixAWidget);

    QVBoxLayout *matrixBLayout = new QVBoxLayout;
    QHBoxLayout *matrixBControlsLayout = new QHBoxLayout;
    matrixBControlsLayout->addWidget(new QLabel("Rows:"));
    matrixBControlsLayout->addWidget(matrixBRowsSpinBox);
    matrixBControlsLayout->addWidget(new QLabel("Cols:"));
    matrixBControlsLayout->addWidget(matrixBColsSpinBox);
    matrixBLayout->addLayout(matrixBControlsLayout);
    matrixBLayout->addWidget(matrixBWidget);

    matrixLayout->addLayout(matrixALayout);
    matrixLayout->addLayout(matrixBLayout);

    controlsLayout->addWidget(operationComboBox);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(matrixLayout);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &MatrixDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &MatrixDialog::reject);
    connect(matrixARowsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixDialog::onMatrixARowsChanged);
    connect(matrixAColsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixDialog::onMatrixAColsChanged);
    connect(matrixBRowsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixDialog::onMatrixBRowsChanged);
    connect(matrixBColsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixDialog::onMatrixBColsChanged);
}

MatrixDialog::~MatrixDialog()
{
}

Matrix MatrixDialog::getMatrixA()
{
    Matrix matrix(matrixAWidget->rowCount(), std::vector<double>(matrixAWidget->columnCount()));
    for (int i = 0; i < matrixAWidget->rowCount(); ++i) {
        for (int j = 0; j < matrixAWidget->columnCount(); ++j) {
            matrix[i][j] = matrixAWidget->item(i, j) ? matrixAWidget->item(i, j)->text().toDouble() : 0.0;
        }
    }
    return matrix;
}

Matrix MatrixDialog::getMatrixB()
{
    Matrix matrix(matrixBWidget->rowCount(), std::vector<double>(matrixBWidget->columnCount()));
    for (int i = 0; i < matrixBWidget->rowCount(); ++i) {
        for (int j = 0; j < matrixBWidget->columnCount(); ++j) {
            matrix[i][j] = matrixBWidget->item(i, j) ? matrixBWidget->item(i, j)->text().toDouble() : 0.0;
        }
    }
    return matrix;
}

QString MatrixDialog::getOperation()
{
    return operationComboBox->currentText();
}

void MatrixDialog::onMatrixARowsChanged(int value)
{
    matrixAWidget->setRowCount(value);
}

void MatrixDialog::onMatrixAColsChanged(int value)
{
    matrixAWidget->setColumnCount(value);
}

void MatrixDialog::onMatrixBRowsChanged(int value)
{
    matrixBWidget->setRowCount(value);
}

void MatrixDialog::onMatrixBColsChanged(int value)
{
    matrixBWidget->setColumnCount(value);
}