#ifndef CRTDIALOG_H
#define CRTDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include "CalculatorEngine.h"

class CRTDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRTDialog(QWidget *parent = nullptr);
    ~CRTDialog();

    std::vector<CalculatorEngine::CRTEquation> getEquations();

private:
    QTableWidget *equationTable;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *addRowButton;
};

#endif // CRTDIALOG_H
