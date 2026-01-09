#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "CalculatorEngine.h"
#include <QTableWidget>

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    CalculatorWindow(QWidget *parent = nullptr);
    ~CalculatorWindow();

private slots:
    void digitClicked();
    void operatorClicked();
    void functionClicked();
    void clearClicked();
    void equalsClicked();
    void backspaceClicked();
    void decimalClicked();
    void shiftClicked();
    void equationClicked();
    void matrixClicked();
    void rclClicked();
    void mPlusClicked();
    void preAnsClicked();
    void showMatrixResult(const Matrix& resultMatrix);
    void hideMatrixResult();
    void hypClicked(); // New slot

private:
    void createWidgets();
    void createLayout();
    void createConnections();
    int precedence(const QString& op);
    long double applyOp(long double a, long double b, const QString& op);
    void evaluateExpression();
    void updateButtonTexts();

    QLineEdit *display;
    QLabel *matrixResultLabel;
    QTableWidget *matrixResultWidget;

    // Top row buttons
    QPushButton *shiftButton;

    // Function buttons
    QPushButton *x3Button;
    QPushButton *logBaseButton;
    QPushButton *sqrtButton;
    QPushButton *x2Button;
    QPushButton *powButton;
    QPushButton *logButton;
    QPushButton *lnButton;
    QPushButton *factButton;
    QPushButton *hypButton;
    QPushButton *sinButton;
    QPushButton *cosButton;
    QPushButton *tanButton;
    // stoButton removed
    QPushButton *rclButton;
    QPushButton *leftParenButton;
    QPushButton *rightParenButton;
    QPushButton *mPlusButton;
    QPushButton *mMinusButton;

    // Number pad
    QPushButton *sevenButton;
    QPushButton *eightButton;
    QPushButton *nineButton;
    QPushButton *fourButton;
    QPushButton *fiveButton;
    QPushButton *sixButton;
    QPushButton *oneButton;
    QPushButton *twoButton;
    QPushButton *threeButton;
    QPushButton *zeroButton;
    QPushButton *decimalButton;

    // Operator buttons
    QPushButton *delButton;
    QPushButton *acButton;
    QPushButton *multiplyButton;
    QPushButton *divideButton;
    QPushButton *addButton;
    QPushButton *subtractButton;
    QPushButton *equalsButton;

    // Other buttons from the image (including new hyperbolic/reciprocal trig)
    QPushButton *percentButton; // Will be renamed to "a mod b"
    QPushButton *nprButton;
    QPushButton *ncrButton;
    QPushButton *gcdButton;
    // intButton removed
    QPushButton *preAnsButton;
    QPushButton *matrixButton;
    QPushButton *quadraticButton;
    QPushButton *simultaneousButton;
    QPushButton *crtButton;
    QPushButton *piButton;
    QPushButton *xInverseButton;
    QPushButton *secButton;
    QPushButton *cosecButton;
    QPushButton *cotButton;
    QPushButton *lcmButton; // New button
    QPushButton *arcsinButton; // New
    QPushButton *arccosButton; // New
    QPushButton *arctanButton; // New
    QPushButton *nthRootButton; // New dedicated button for nth root
    QPushButton *arcsinhButton;
    QPushButton *arccoshButton;
    QPushButton *arctanhButton;
    QPushButton *arccosechButton;
    QPushButton *arcsechButton;
    QPushButton *arccothButton;

    CalculatorEngine engine;

    // State variables for calculation
    QString currentExpression;
    bool waitingForOperand;
    long double lastResult;
    bool isShifted;
    bool isHyp; // New member variable
    double memory;
    QLabel *titleLabel;
};

#endif // CALCULATORWINDOW_H