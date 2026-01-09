#ifndef MATRIXDIALOG_H
#define MATRIXDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include "CalculatorEngine.h"

#include <QSpinBox>

class MatrixDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MatrixDialog(QWidget *parent = nullptr);
    ~MatrixDialog();

    Matrix getMatrixA();
    Matrix getMatrixB();
    QString getOperation();

private slots:
    void onMatrixARowsChanged(int value);
    void onMatrixAColsChanged(int value);
    void onMatrixBRowsChanged(int value);
    void onMatrixBColsChanged(int value);

private:
    QTableWidget *matrixAWidget;
    QTableWidget *matrixBWidget;
    QComboBox *operationComboBox;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpinBox *matrixARowsSpinBox;
    QSpinBox *matrixAColsSpinBox;
    QSpinBox *matrixBRowsSpinBox;
    QSpinBox *matrixBColsSpinBox;
};

#endif // MATRIXDIALOG_H
