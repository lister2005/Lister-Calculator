#include "CalculatorWindow.h"
#include "MatrixDialog.h"
#include "QuadraticDialog.h"
#include "SimultaneousDialog.h"
#include "CRTDialog.h"
#include "NthRootDialog.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStack>
#include <QDebug>
#include <QLabel>
#include <QHeaderView> // Required for QHeaderView
#include <cmath> // For fmod
#include <QInputDialog> // For getting two inputs for modulo and power

CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QMainWindow(parent),
      waitingForOperand(true),
      lastResult(0.0),
      isShifted(false),
      isHyp(false),
      memory(0.0)
{
    createWidgets();
    createLayout();
    createConnections();

    setFixedSize(400, 600);
}

CalculatorWindow::~CalculatorWindow()
{
}

void CalculatorWindow::createWidgets()
{
    titleLabel = new QLabel(this);
    titleLabel->setTextFormat(Qt::RichText);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    QString coloredText = "<span style='color: lightgreen;'>L</span>"
                          "<span style='color: khaki;'>I</span>"
                          "<span style='color: skyblue;'>S</span>"
                          "<span style='color: lightcoral;'>T</span>"
                          "<span style='color: orange;'>E</span>"
                          "<span style='color: plum;'>R</span>";
    titleLabel->setText(coloredText);

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(80);

    matrixResultLabel = new QLabel("Matrix Result:", this);
    matrixResultLabel->setAlignment(Qt::AlignCenter);
    matrixResultLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    matrixResultLabel->hide(); // Initially hidden

    matrixResultWidget = new QTableWidget(this);
    matrixResultWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // Make it read-only
    matrixResultWidget->horizontalHeader()->setVisible(false);
    matrixResultWidget->verticalHeader()->setVisible(false);
    matrixResultWidget->hide(); // Initially hidden

    // Top row
    shiftButton = new QPushButton("SHIFT");

    // Functions
    x3Button = new QPushButton("x³");
    logBaseButton = new QPushButton("logₐb");
    sqrtButton = new QPushButton("√");
    x2Button = new QPushButton("x²");
    powButton = new QPushButton("xʸ"); // Renamed
    logButton = new QPushButton("log");
    lnButton = new QPushButton("ln");
    factButton = new QPushButton("x!");
    hypButton = new QPushButton("hyp");
    mMinusButton = new QPushButton("(-)");
    sinButton = new QPushButton("sin");
    cosButton = new QPushButton("cos");
    tanButton = new QPushButton("tan");
    // stoButton removed
    rclButton = new QPushButton("RCL");
    leftParenButton = new QPushButton("(");
    rightParenButton = new QPushButton(")");
    mPlusButton = new QPushButton("M+");

    // Number Pad
    sevenButton = new QPushButton("7");
    eightButton = new QPushButton("8");
    nineButton = new QPushButton("9");
    fourButton = new QPushButton("4");
    fiveButton = new QPushButton("5");
    sixButton = new QPushButton("6");
    oneButton = new QPushButton("1");
    twoButton = new QPushButton("2");
    threeButton = new QPushButton("3");
    zeroButton = new QPushButton("0");
    decimalButton = new QPushButton(".");

    // Operators
    delButton = new QPushButton("DEL");
    acButton = new QPushButton("AC");
    multiplyButton = new QPushButton("x");
    divideButton = new QPushButton("÷");
    addButton = new QPushButton("+");
    subtractButton = new QPushButton("-");
    equalsButton = new QPushButton("=");

    // Other buttons from the image (including new hyperbolic/reciprocal trig)
    percentButton = new QPushButton("a mod b"); // Renamed
    nprButton = new QPushButton("nPr");
    ncrButton = new QPushButton("nCr");
    gcdButton = new QPushButton("GCD");
    // intButton removed
    preAnsButton = new QPushButton("PreAns");
    matrixButton = new QPushButton("Matrix");
    quadraticButton = new QPushButton("Quad");
    simultaneousButton = new QPushButton("Simult");
    crtButton = new QPushButton("CRT");
    piButton = new QPushButton("π");
    xInverseButton = new QPushButton("x⁻¹");
    secButton = new QPushButton("sec");
    cosecButton = new QPushButton("cosec");
    cotButton = new QPushButton("cot");
    lcmButton = new QPushButton("LCM"); // New button
    arcsinButton = new QPushButton("arcsin"); // New
    arccosButton = new QPushButton("arccos"); // New
    arctanButton = new QPushButton("arctan"); // New
    nthRootButton = new QPushButton("ⁿ√x"); // New dedicated button for nth root
    arcsinhButton = new QPushButton("arcsinh");
    arccoshButton = new QPushButton("arccosh");
    arctanhButton = new QPushButton("arctanh");
    arccosechButton = new QPushButton("arccosech");
    arcsechButton = new QPushButton("arcsech");
    arccothButton = new QPushButton("arccoth");
}

void CalculatorWindow::createLayout()
{
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QGridLayout *gridLayout = new QGridLayout;

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(display);
    mainLayout->addWidget(matrixResultLabel); // Add the label
    mainLayout->addWidget(matrixResultWidget); // Add the table widget
    mainLayout->addLayout(gridLayout);

    // Row 0
    gridLayout->addWidget(shiftButton, 0, 0);
    gridLayout->addWidget(percentButton, 0, 1); // a mod b
    gridLayout->addWidget(mPlusButton, 0, 2); // Swapped from (6,4)
    gridLayout->addWidget(preAnsButton, 0, 3);
    gridLayout->addWidget(acButton, 0, 4);

    // Row 1
    gridLayout->addWidget(xInverseButton, 1, 0);
    gridLayout->addWidget(secButton, 1, 1);
    gridLayout->addWidget(cosecButton, 1, 2);
    gridLayout->addWidget(cotButton, 1, 3);
    gridLayout->addWidget(delButton, 1, 4);

    // Row 2
    gridLayout->addWidget(sqrtButton, 2, 0);
    gridLayout->addWidget(x2Button, 2, 1);
    gridLayout->addWidget(x3Button, 2, 2);
    gridLayout->addWidget(powButton, 2, 3); // x^y
    gridLayout->addWidget(hypButton, 2, 4);

    // Row 3
    gridLayout->addWidget(logButton, 3, 0);
    gridLayout->addWidget(lnButton, 3, 1);
    gridLayout->addWidget(factButton, 3, 2);
    gridLayout->addWidget(leftParenButton, 3, 3);
    gridLayout->addWidget(rightParenButton, 3, 4);

    // Row 4
    gridLayout->addWidget(sinButton, 4, 0);
    gridLayout->addWidget(cosButton, 4, 1);
    gridLayout->addWidget(tanButton, 4, 2);
    gridLayout->addWidget(rclButton, 4, 3);
    gridLayout->addWidget(mMinusButton, 4, 4);

    // Row 5 (Number Pad)
    gridLayout->addWidget(sevenButton, 5, 0);
    gridLayout->addWidget(eightButton, 5, 1);
    gridLayout->addWidget(nineButton, 5, 2);
    gridLayout->addWidget(divideButton, 5, 3);
    gridLayout->addWidget(multiplyButton, 5, 4);

    // Row 6
    gridLayout->addWidget(fourButton, 6, 0);
    gridLayout->addWidget(fiveButton, 6, 1);
    gridLayout->addWidget(sixButton, 6, 2);
    gridLayout->addWidget(addButton, 6, 3);
    gridLayout->addWidget(subtractButton, 6, 4);

    // Row 7
    gridLayout->addWidget(oneButton, 7, 0);
    gridLayout->addWidget(twoButton, 7, 1);
    gridLayout->addWidget(threeButton, 7, 2);
    gridLayout->addWidget(ncrButton, 7, 3);
    gridLayout->addWidget(nprButton, 7, 4);

    // Row 8
    gridLayout->addWidget(zeroButton, 8, 0);
    gridLayout->addWidget(decimalButton, 8, 1);
    gridLayout->addWidget(equalsButton, 8, 2); // Swapped from (0,2)
    gridLayout->addWidget(piButton, 8, 3);
    gridLayout->addWidget(gcdButton, 8, 4);

    // Row 9
    gridLayout->addWidget(matrixButton, 9, 0);
    gridLayout->addWidget(quadraticButton, 9, 1);
    gridLayout->addWidget(simultaneousButton, 9, 2);
    gridLayout->addWidget(crtButton, 9, 3);
    gridLayout->addWidget(logBaseButton, 9, 4);

    // Row 10 (Inverse Trig and Nth Root)
    gridLayout->addWidget(nthRootButton, 10, 0);
    gridLayout->addWidget(arcsinhButton, 10, 1);
    gridLayout->addWidget(arccoshButton, 10, 2);
    gridLayout->addWidget(arctanhButton, 10, 3);
    gridLayout->addWidget(arccosechButton, 10, 4);

    // Row 11 (Inverse Hyperbolic functions)
    gridLayout->addWidget(arcsechButton, 11, 0);
    gridLayout->addWidget(arccothButton, 11, 1);


    setCentralWidget(centralWidget);
}

void CalculatorWindow::createConnections()
{
    // Connect number buttons
    connect(zeroButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(oneButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(twoButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(threeButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(fourButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(fiveButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(sixButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(sevenButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(eightButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(nineButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);

    // Connect operator buttons
    connect(addButton, &QPushButton::clicked, this, &CalculatorWindow::operatorClicked);
    connect(subtractButton, &QPushButton::clicked, this, &CalculatorWindow::operatorClicked);
    connect(multiplyButton, &QPushButton::clicked, this, &CalculatorWindow::operatorClicked);
    connect(divideButton, &QPushButton::clicked, this, &CalculatorWindow::operatorClicked);
    connect(powButton, &QPushButton::clicked, this, &CalculatorWindow::operatorClicked); // x^y is an operator

    // Connect function buttons
    connect(sinButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(cosButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(tanButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(logButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(lnButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(sqrtButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(x2Button, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(x3Button, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(xInverseButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(factButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(hypButton, &QPushButton::clicked, this, &CalculatorWindow::hypClicked);
    connect(mMinusButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(rclButton, &QPushButton::clicked, this, &CalculatorWindow::rclClicked);
    connect(mPlusButton, &QPushButton::clicked, this, &CalculatorWindow::mPlusClicked);
    // stoButton removed

    // Connect other buttons
    connect(acButton, &QPushButton::clicked, this, &CalculatorWindow::clearClicked);
    connect(equalsButton, &QPushButton::clicked, this, &CalculatorWindow::equalsClicked);
    connect(delButton, &QPushButton::clicked, this, &CalculatorWindow::backspaceClicked);
    connect(decimalButton, &QPushButton::clicked, this, &CalculatorWindow::decimalClicked);
    connect(leftParenButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);
    connect(rightParenButton, &QPushButton::clicked, this, &CalculatorWindow::digitClicked);

    // New button connections
    connect(ncrButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(gcdButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(piButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(matrixButton, &QPushButton::clicked, this, &CalculatorWindow::matrixClicked);
    connect(quadraticButton, &QPushButton::clicked, this, &CalculatorWindow::equationClicked);
    connect(simultaneousButton, &QPushButton::clicked, this, &CalculatorWindow::equationClicked);
    connect(crtButton, &QPushButton::clicked, this, &CalculatorWindow::equationClicked);
    connect(shiftButton, &QPushButton::clicked, this, &CalculatorWindow::shiftClicked);
    connect(percentButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked); // a mod b
    connect(nprButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    // intButton removed
    connect(preAnsButton, &QPushButton::clicked, this, &CalculatorWindow::preAnsClicked);

    // Connect new hyperbolic and reciprocal trig buttons (now handled by text changes)
    // Removed direct connections for cosechButton, sechButton, cothButton, arcsinhButton, etc.
    connect(secButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(cosecButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(cotButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(logBaseButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);

    // Connect new inverse trig buttons
    connect(nthRootButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked); // Dedicated nth root button

    // Connect dedicated inverse hyperbolic buttons
    connect(arcsinhButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(arccoshButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(arctanhButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(arccosechButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(arcsechButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
    connect(arccothButton, &QPushButton::clicked, this, &CalculatorWindow::functionClicked);
}

void CalculatorWindow::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString digitValue = clickedButton->text();

    hideMatrixResult();

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }

    if (display->text() == "0" && digitValue != ".") {
        display->setText(digitValue);
    } else {
        display->setText(display->text() + digitValue);
    }
}

void CalculatorWindow::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString operatorValue = clickedButton->text();
    hideMatrixResult();

    if (operatorValue == "x") {
        operatorValue = "*";
    } else if (operatorValue == "÷") {
        operatorValue = "/";
    } else if (operatorValue == "xʸ") {
        operatorValue = "^";
    }

    display->setText(display->text() + operatorValue);
    waitingForOperand = false;
}

void CalculatorWindow::functionClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString func = clickedButton->text();

    hideMatrixResult();

    if (waitingForOperand) {
        // If waiting for operand, and a function is clicked, it means the user wants to apply
        // the function to the previous result or 0 if display is empty.
        // For now, let's assume they want to apply it to the current display value.
        // If display is "0" and not waiting for operand, it means a fresh start.
        // If display is "0" and waiting for operand, it means previous calculation resulted in 0 or clear was pressed.
        // We should not clear the display here.
    }

    double number = display->text().toDouble();
    double result = 0.0;
    bool ok;
    QString inputString;
    QStringList parts;

    // Handle functions that operate on the current display value (unary functions)
    if (func == "sin") result = engine.sine(number);
    else if (func == "cos") result = engine.cosine(number);
    else if (func == "tan") result = engine.tangent(number);
    else if (func == "csc") result = engine.cosecant(number);
    else if (func == "sec") result = engine.secant(number);
    else if (func == "cot") result = engine.cotangent(number);
    else if (func == "sinh") result = engine.sinh(number);
    else if (func == "cosh") result = engine.cosh(number);
    else if (func == "tanh") result = engine.tanh(number);
    else if (func == "sech") result = engine.sech(number);
    else if (func == "cosech") result = engine.cosech(number);
    else if (func == "coth") result = engine.coth(number);
    else if (func == "sin⁻¹") result = engine.arcsin(number);
    else if (func == "cos⁻¹") result = engine.arccos(number);
    else if (func == "tan⁻¹") result = engine.arctan(number);
    else if (func == "sec⁻¹") result = engine.arcsec(number);
    else if (func == "cosec⁻¹") result = engine.arccsc(number);
    else if (func == "cot⁻¹") result = engine.arccot(number);
    else if (func == "sinh⁻¹") result = engine.arcsinh(number);
    else if (func == "cosh⁻¹") result = engine.arccosh(number);
    else if (func == "tanh⁻¹") result = engine.arctanh(number);
    else if (func == "sech⁻¹") result = engine.arcsech(number);
    else if (func == "cosech⁻¹") result = engine.arccosech(number);
    else if (func == "coth⁻¹") result = engine.arccoth(number);
    else if (func == "arcsinh") result = engine.arcsinh(number);
    else if (func == "arccosh") result = engine.arccosh(number);
    else if (func == "arctanh") result = engine.arctanh(number);
    else if (func == "arccosech") result = engine.arccosech(number);
    else if (func == "arcsech") result = engine.arcsech(number);
    else if (func == "arccoth") result = engine.arccoth(number);
    else if (func == "log") result = engine.logBase(number, 10.0); // Assuming log base 10 for "log" button
    else if (func == "ln") result = engine.naturalLog(number);
    else if (func == "x²") result = engine.power(number, 2);
    else if (func == "x³") result = engine.power(number, 3);
    else if (func == "x⁻¹") result = engine.power(number, -1);
    else if (func == "√") result = engine.root(number, 2);
    else if (func == "x!") result = engine.factorial(static_cast<int>(number));
    else if (func == "π") {
        display->setText(QString::number(M_PI, 'g', 15));
        waitingForOperand = true;
        return;
    }
    else if (func == "(-)") {
        display->setText(QString::number(-number, 'g', 15)); // Apply unary minus
        waitingForOperand = true;
        return;
    }
    // Functions that require multiple inputs via a single dialog line
    else if (func == "ⁿ√x") {
        inputString = QInputDialog::getText(this, tr("Nth Root"), tr("Enter n, x (comma-separated):"), QLineEdit::Normal, QString("%1, %2").arg(2).arg(number), &ok);
        if (ok && !inputString.isEmpty()) {
            parts = inputString.split(',', Qt::SkipEmptyParts);
            if (parts.size() == 2) {
                bool n_ok, x_ok;
                double n_val = parts[0].trimmed().toDouble(&n_ok);
                double x_val = parts[1].trimmed().toDouble(&x_ok);
                if (n_ok && x_ok) {
                    result = engine.root(x_val, static_cast<int>(n_val));
                } else {
                    display->setText("Error: Invalid numbers");
                    waitingForOperand = true;
                    return;
                }
            } else {
                display->setText("Error: Invalid format");
                waitingForOperand = true;
                return;
            }
        } else {
            display->setText("Error: Input cancelled or empty");
            waitingForOperand = true;
            return;
        }
    }
    else if (func == "nCr") {
        inputString = QInputDialog::getText(this, tr("Combinations"), tr("Enter n, r (comma-separated):"), QLineEdit::Normal, QString("%1, %2").arg(0).arg(0), &ok);
        if (ok && !inputString.isEmpty()) {
            parts = inputString.split(',', Qt::SkipEmptyParts);
            if (parts.size() == 2) {
                bool n_ok, r_ok;
                int n_val = parts[0].trimmed().toInt(&n_ok);
                int r_val = parts[1].trimmed().toInt(&r_ok);
                if (n_ok && r_ok) {
                    result = engine.combination(n_val, r_val);
                } else {
                    display->setText("Error: Invalid numbers");
                    waitingForOperand = true;
                    return;
                }
            } else {
                display->setText("Error: Invalid format");
                waitingForOperand = true;
                return;
            }
        } else {
            display->setText("Error: Input cancelled or empty");
            waitingForOperand = true;
            return;
        }
    }
    else if (func == "nPr") {
        inputString = QInputDialog::getText(this, tr("Permutations"), tr("Enter n, r (comma-separated):"), QLineEdit::Normal, QString("%1, %2").arg(0).arg(0), &ok);
        if (ok && !inputString.isEmpty()) {
            parts = inputString.split(',', Qt::SkipEmptyParts);
            if (parts.size() == 2) {
                bool n_ok, r_ok;
                int n_val = parts[0].trimmed().toInt(&n_ok);
                int r_val = parts[1].trimmed().toInt(&r_ok);
                if (n_ok && r_ok) {
                    result = engine.permutation(n_val, r_val);
                } else {
                    display->setText("Error: Invalid numbers");
                    waitingForOperand = true;
                    return;
                }
            } else {
                display->setText("Error: Invalid format");
                waitingForOperand = true;
                return;
            }
        } else {
            display->setText("Error: Input cancelled or empty");
            waitingForOperand = true;
            return;
        }
    }
    else if (func == "a mod b") {
        inputString = QInputDialog::getText(this, tr("Modulo"), tr("Enter a, m (comma-separated):"), QLineEdit::Normal, QString("%1, %2").arg(number).arg(2), &ok);
        if (ok && !inputString.isEmpty()) {
            parts = inputString.split(',', Qt::SkipEmptyParts);
            if (parts.size() == 2) {
                bool a_ok, m_ok;
                long long a_val = parts[0].trimmed().toLongLong(&a_ok);
                long long m_val = parts[1].trimmed().toLongLong(&m_ok);
                if (a_ok && m_ok) {
                    result = engine.modulo(a_val, m_val);
                } else {
                    display->setText("Error: Invalid numbers");
                    waitingForOperand = true;
                    return;
                }
            } else {
                display->setText("Error: Invalid format");
                waitingForOperand = true;
                return;
            }
        } else {
            display->setText("Error: Input cancelled or empty");
            waitingForOperand = true;
            return;
        }
    }
    else if (func == "GCD") {
        inputString = QInputDialog::getText(this, tr("GCD"), tr("Enter num1, num2 (comma-separated):"), QLineEdit::Normal, QString("%1, %2").arg(number).arg(0), &ok);
        if (ok && !inputString.isEmpty()) {
            parts = inputString.split(',', Qt::SkipEmptyParts);
            if (parts.size() == 2) {
                bool num1_ok, num2_ok;
                long long num1_val = parts[0].trimmed().toLongLong(&num1_ok);
                long long num2_val = parts[1].trimmed().toLongLong(&num2_ok);
                if (num1_ok && num2_ok) {
                    result = engine.gcd(num1_val, num2_val);
                } else {
                    display->setText("Error: Invalid numbers");
                    waitingForOperand = true;
                    return;
                }
            } else {
                display->setText("Error: Invalid format");
                waitingForOperand = true;
                return;
            }
        } else {
            display->setText("Error: Input cancelled or empty");
            waitingForOperand = true;
            return;
        }
    }
    else if (func == "LCM") {
        inputString = QInputDialog::getText(this, tr("LCM"), tr("Enter num1, num2 (comma-separated):"), QLineEdit::Normal, QString("%1, %2").arg(number).arg(0), &ok);
        if (ok && !inputString.isEmpty()) {
            parts = inputString.split(',', Qt::SkipEmptyParts);
            if (parts.size() == 2) {
                bool num1_ok, num2_ok;
                long long num1_val = parts[0].trimmed().toLongLong(&num1_ok);
                long long num2_val = parts[1].trimmed().toLongLong(&num2_ok);
                if (num1_ok && num2_ok) {
                    result = engine.lcm(num1_val, num2_val);
                } else {
                    display->setText("Error: Invalid numbers");
                    waitingForOperand = true;
                    return;
                }
            } else {
                display->setText("Error: Invalid format");
                waitingForOperand = true;
                return;
            }
        } else {
            display->setText("Error: Input cancelled or empty");
            waitingForOperand = true;
            return;
        }
    }
    else if (func == "logₐb") {
        inputString = QInputDialog::getText(this, tr("Logarithm"), tr("Enter b, a (comma-separated):"), QLineEdit::Normal, QString("%1, %2").arg(number).arg(10), &ok);
        if (ok && !inputString.isEmpty()) {
            parts = inputString.split(',', Qt::SkipEmptyParts);
            if (parts.size() == 2) {
                bool b_ok, a_ok;
                double b_val = parts[0].trimmed().toDouble(&b_ok);
                double a_val = parts[1].trimmed().toDouble(&a_ok);
                if (b_ok && a_ok) {
                    result = engine.logBase(b_val, a_val);
                } else {
                    display->setText("Error: Invalid numbers");
                    waitingForOperand = true;
                    return;
                }
            } else {
                display->setText("Error: Invalid format");
                waitingForOperand = true;
                return;
            }
        } else {
            display->setText("Error: Input cancelled or empty");
            waitingForOperand = true;
            return;
        }
    }
    else {
        // For any other function not handled above, append func()
        display->setText("Error: Unknown function");
        waitingForOperand = true;
        return;
    }

    display->setText(QString::number(result, 'g', 15));
    waitingForOperand = true;
}

void CalculatorWindow::clearClicked()
{
    display->setText("0");
    waitingForOperand = true;
    hideMatrixResult();
}

void CalculatorWindow::equalsClicked()
{
    evaluateExpression();
    hideMatrixResult();
}

void CalculatorWindow::backspaceClicked()
{
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
    hideMatrixResult();
}

void CalculatorWindow::decimalClicked()
{
    if (!display->text().contains('.')) {
        display->setText(display->text() + ".");
    }
    hideMatrixResult();
}

void CalculatorWindow::updateButtonTexts()
{
    // This function updates all button texts based on the current state of isShifted and isHyp
    if (isHyp) {
        if (isShifted) {
            sinButton->setText("sinh⁻¹");
            cosButton->setText("cosh⁻¹");
            tanButton->setText("tanh⁻¹");
            secButton->setText("sech⁻¹");
            cosecButton->setText("cosech⁻¹");
            cotButton->setText("coth⁻¹");
        } else {
            sinButton->setText("sinh");
            cosButton->setText("cosh");
            tanButton->setText("tanh");
            secButton->setText("sech");
            cosecButton->setText("cosech");
            cotButton->setText("coth");
        }
    } else { // Not hyperbolic
        if (isShifted) {
            sinButton->setText("sin⁻¹");
            cosButton->setText("cos⁻¹");
            tanButton->setText("tan⁻¹");
            secButton->setText("sec⁻¹");
            cosecButton->setText("cosec⁻¹");
            cotButton->setText("cot⁻¹");
        } else {
            sinButton->setText("sin");
            cosButton->setText("cos");
            tanButton->setText("tan");
            secButton->setText("sec");
            cosecButton->setText("cosec");
            cotButton->setText("cot");
        }
    }

    // These buttons change with shift but not with hyp
    if (isShifted) {
        x3Button->setText("x³"); // x3Button always displays x³
        mMinusButton->setText("Abs");
        gcdButton->setText("LCM");
        piButton->setText("π"); // Shift action for pi if any, e.g. show constant menu
    } else {
        logButton->setText("log");
        lnButton->setText("ln");
        sqrtButton->setText("³√x");
        x2Button->setText("x³");
        x3Button->setText("x³"); // x3Button always displays x³
        mMinusButton->setText("(-)");
        factButton->setText("x!");
        gcdButton->setText("GCD");
        piButton->setText("π");
    }

    // These buttons are not affected by shift or hyp in this new design
    // Their text is static.
    powButton->setText("xʸ");
    ncrButton->setText("nCr");
    percentButton->setText("a mod b");
    xInverseButton->setText("x⁻¹");
    logBaseButton->setText("logₐb");
    nthRootButton->setText("ⁿ√x");
    arcsinhButton->setText("arcsinh");
    arccoshButton->setText("arccosh");
    arctanhButton->setText("arctanh");
    arccosechButton->setText("arccosech");
    arcsechButton->setText("arcsech");
    arccothButton->setText("arccoth");
}

void CalculatorWindow::shiftClicked()
{
    isShifted = !isShifted;
    if (isShifted) {
        shiftButton->setStyleSheet("background-color: lightblue;");
    } else {
        shiftButton->setStyleSheet("");
    }
    updateButtonTexts();
}

void CalculatorWindow::equationClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString buttonText = clickedButton->text();

    hideMatrixResult(); // Hide matrix result when an equation button is clicked

    if (buttonText == "Quad") {
        QuadraticDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            double a = dialog.getA();
            double b = dialog.getB();
            double c = dialog.getC();
            CalculatorEngine::QuadraticSolution solution = engine.solveQuadratic(a, b, c);
            if (solution.hasRealRoots) {
                if (solution.root1 == solution.root2) {
                    display->setText("x = " + QString::number(solution.root1));
                } else {
                    display->setText("x1 = " + QString::number(solution.root1) + ", x2 = " + QString::number(solution.root2));
                }
            } else {
                display->setText(QString::fromStdString(solution.errorMessage));
            }
        }
    } else if (buttonText == "Simult") {
        SimultaneousDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            double a1 = dialog.getA1();
            double b1 = dialog.getB1();
            double c1 = dialog.getC1();
            double a2 = dialog.getA2();
            double b2 = dialog.getB2();
            double c2 = dialog.getC2();
            CalculatorEngine::SimultaneousSolution solution = engine.solveSimultaneous(a1, b1, c1, a2, b2, c2);
            if (solution.hasSolution) {
                display->setText("x = " + QString::number(solution.x) + ", y = " + QString::number(solution.y));
            } else {
                display->setText(QString::fromStdString(solution.errorMessage));
            }
        }
    } else if (buttonText == "CRT") {
        CRTDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            std::vector<CalculatorEngine::CRTEquation> equations = dialog.getEquations();
            CalculatorEngine::CRTResult result = engine.solveChineseRemainderTheorem(equations);
            if (result.solvable) {
                display->setText("x ≡ " + QString::number(result.solutionX) + " (mod " + QString::number(result.modulusM) + ")");
            } else {
                display->setText(QString::fromStdString(result.errorMessage));
            }
        }
    }
}

void CalculatorWindow::matrixClicked()
{
    MatrixDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Matrix matrixA = dialog.getMatrixA();
        Matrix matrixB = dialog.getMatrixB();
        QString operation = dialog.getOperation();

        try {
            Matrix resultMatrix;
            if (operation == "Add") {
                resultMatrix = engine.matrixAdd(matrixA, matrixB);
            } else if (operation == "Multiply") {
                resultMatrix = engine.matrixMultiply(matrixA, matrixB);
            }
            showMatrixResult(resultMatrix);

        } catch (const std::invalid_argument& e) {
            display->setText("Error: " + QString(e.what()));
        }
    }
}

void CalculatorWindow::rclClicked()
{
    display->setText(QString::number(memory));
    hideMatrixResult();
}

void CalculatorWindow::mPlusClicked()
{
    memory += display->text().toDouble();
    hideMatrixResult();
}

void CalculatorWindow::preAnsClicked()
{
    display->setText(QString::number(static_cast<double>(lastResult), 'g', 15));
    hideMatrixResult(); // Hide matrix result when preAns is clicked
}

void CalculatorWindow::showMatrixResult(const Matrix& resultMatrix)
{
    display->hide();
    matrixResultLabel->show();
    matrixResultWidget->show();

    matrixResultWidget->setRowCount(resultMatrix.size());
    if (!resultMatrix.empty()) {
        matrixResultWidget->setColumnCount(resultMatrix[0].size());
    } else {
        matrixResultWidget->setColumnCount(0);
    }

    for (size_t i = 0; i < resultMatrix.size(); ++i) {
        for (size_t j = 0; j < resultMatrix[i].size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(resultMatrix[i][j], 'g', 6));
            matrixResultWidget->setItem(i, j, item);
        }
    }
    matrixResultWidget->resizeColumnsToContents();
    matrixResultWidget->resizeRowsToContents();
}

void CalculatorWindow::hideMatrixResult()
{
    display->show();
    matrixResultLabel->hide();
    matrixResultWidget->hide();
    matrixResultWidget->clearContents(); // Clear contents when hidden
}

void CalculatorWindow::hypClicked()
{
    isHyp = !isHyp;
    if (isHyp) {
        hypButton->setStyleSheet("background-color: lightblue;"); // Highlight hyp button
    } else {
        hypButton->setStyleSheet(""); // Reset style
    }
    updateButtonTexts(); // Update all buttons
}

bool isFunction(const QString& token) {
    return token == "sin" || token == "cos" || token == "tan" || token == "log" ||
           token == "ln" || token == "sqrt" || token == "x²" || token == "x³" ||
           token == "x⁻¹" || token == "x!" || token == "sinh" || token == "cosh" ||
           token == "tanh" || token == "sec" || token == "cosec" || token == "cot" ||
           token == "sech" || token == "cosech" || token == "coth" || token == "sin⁻¹" ||
           token == "cos⁻¹" || token == "tan⁻¹" || token == "sec⁻¹" || token == "cosec⁻¹" ||
           token == "cot⁻¹" || token == "sinh⁻¹" || token == "cosh⁻¹" || token == "tanh⁻¹" ||
           token == "sech⁻¹" || token == "cosech⁻¹" || token == "coth⁻¹" || token == "Abs" ||
           token == "³√x" || token == "10^x" || token == "exp(x)" ||
           token == "arcsin" || token == "arccos" || token == "arctan" ||
           token == "arcsec" || token == "arccsc" || token == "arccot" ||
           token == "arcsinh" || token == "arccosh" || token == "arctanh" ||
           token == "arcsech" || token == "arccosech" || token == "arccoth";
}

int CalculatorWindow::precedence(const QString& op)
{
    if (isFunction(op))
        return 4; // Functions have high precedence
    if (op == "^")
        return 3;
    if (op == "*" || op == "/")
        return 2;
    if (op == "+" || op == "-")
        return 1;
    return 0;
}

long double CalculatorWindow::applyOp(long double a, long double b, const QString& op)
{
    if (op == "+") return engine.add({(double)a, (double)b});
    if (op == "-") return engine.add({(double)a, (double)-b});
    if (op == "*") return engine.multiply({(double)a, (double)b});
    if (op == "/") {
        if (b == 0) throw std::invalid_argument("Division by zero!");
        return a / b;
    }
    if (op == "^") return engine.power(a, b);
    // This is now a fallback, single-operand functions are handled in evaluateExpression
    return 0;
}


void CalculatorWindow::evaluateExpression()
{
    QString expression = display->text();
    if (expression.isEmpty()) return;

    QStack<long double> values;
    QStack<QString> ops;

    auto applyUnaryOperation = [&](const QString& op) {
        if (values.isEmpty()) throw std::invalid_argument("Syntax Error");
        long double val = values.pop();
        long double result = 0.0;
        if (op == "sin") result = engine.sine(val);
        else if (op == "cos") result = engine.cosine(val);
        else if (op == "tan") result = engine.tangent(val);
        else if (op == "log") result = engine.logBase(val, 10.0);
        else if (op == "ln") result = engine.naturalLog(val);
        else if (op == "sqrt" || op == "√") result = engine.root(val, 2);
        else if (op == "x²") result = engine.power(val, 2);
        else if (op == "x³") result = engine.power(val, 3);
        else if (op == "x⁻¹") result = engine.power(val, -1);
        else if (op == "x!") result = engine.factorial(static_cast<int>(val));
        else if (op == "sinh") result = engine.sinh(val);
        else if (op == "cosh") result = engine.cosh(val);
        else if (op == "tanh") result = engine.tanh(val);
        else if (op == "sec") result = engine.secant(val);
        else if (op == "cosec") result = engine.cosecant(val);
        else if (op == "cot") result = engine.cotangent(val);
        else if (op == "sech") result = engine.sech(val);
        else if (op == "cosech") result = engine.cosech(val);
        else if (op == "coth") result = engine.coth(val);
        else if (op == "sin⁻¹" || op == "arcsin") result = engine.arcsin(val);
        else if (op == "cos⁻¹" || op == "arccos") result = engine.arccos(val);
        else if (op == "tan⁻¹" || op == "arctan") result = engine.arctan(val);
        else if (op == "sec⁻¹" || op == "arcsec") result = engine.arcsec(val);
        else if (op == "cosec⁻¹" || op == "arccsc") result = engine.arccsc(val);
        else if (op == "cot⁻¹" || op == "arccot") result = engine.arccot(val);
        else if (op == "sinh⁻¹" || op == "arcsinh") result = engine.arcsinh(val);
        else if (op == "cosh⁻¹" || op == "arccosh") result = engine.arccosh(val);
        else if (op == "tanh⁻¹" || op == "arctanh") result = engine.arctanh(val);
        else if (op == "sech⁻¹" || op == "arcsech") result = engine.arcsech(val);
        else if (op == "cosech⁻¹" || op == "arccosech") result = engine.arccosech(val);
        else if (op == "coth⁻¹" || op == "arccoth") result = engine.arccoth(val);
        else if (op == "Abs") result = std::abs(val);
        else if (op == "³√x") result = engine.root(val, 3);
        else if (op == "10^x") result = engine.power(10, val);
        else if (op == "exp(x)") result = engine.exponential(val);
        else throw std::invalid_argument("Unknown function");
        values.push(result);
    };

    try {
        for (int i = 0; i < expression.length(); ++i) {
            if (expression[i].isSpace()) continue;

            if (expression[i].isLetter()) {
                QString token;
                while (i < expression.length() && (expression[i].isLetter() || expression[i] == '⁻' || expression[i] == '¹' || expression[i] == '²' || expression[i] == '³' || expression[i] == '(' || expression[i] == ')' || expression[i] == '√' || expression[i] == 'ⁿ' || expression[i] == 'ₓ')) {
                    token.append(expression[i]);
                    i++;
                }
                i--; // Decrement i because the outer loop increments it

                if (isFunction(token)) {
                    ops.push(token);
                } else if (token == "pi" || token == "π") {
                    values.push(M_PI);
                } else if (token == "e") {
                    values.push(M_E);
                }
                else {
                    throw std::invalid_argument("Unknown identifier: " + token.toStdString());
                }
            } else if (expression[i].isDigit() || expression[i] == '.') {
                QString val;
                while (i < expression.length() && (expression[i].isDigit() || expression[i] == '.')) {
                    val.append(expression[i]);
                    i++;
                }
                values.push(val.toDouble());
                i--;
            } else if (expression[i] == '(') {
                ops.push(QString(expression[i]));
            } else if (expression[i] == ')') {
                while (!ops.isEmpty() && ops.top() != "(") {
                    QString op = ops.pop();
                    if (isFunction(op)) {
                        applyUnaryOperation(op);
                    } else {
                        if (values.size() < 2) throw std::invalid_argument("Syntax Error");
                        long double val2 = values.pop();
                        long double val1 = values.pop();
                        values.push(applyOp(val1, val2, op));
                    }
                }
                if (!ops.isEmpty()) ops.pop(); // Pop '('
            } else { // Operator
                QString op_str = QString(expression[i]);
                 if ((op_str == "-") && (i == 0 || expression[i-1] == '(' || expression[i-1] == '*' || expression[i-1] == '/' || expression[i-1] == '^' || expression[i-1] == '+')) {
                    // Unary minus
                    values.push(0);
                    ops.push("-");
                } else {
                    while (!ops.isEmpty() && precedence(ops.top()) >= precedence(op_str)) {
                         QString op = ops.pop();
                        if (isFunction(op)) {
                            applyUnaryOperation(op);
                        } else {
                            if (values.size() < 2) throw std::invalid_argument("Syntax Error");
                            long double val2 = values.pop();
                            long double val1 = values.pop();
                            values.push(applyOp(val1, val2, op));
                        }
                    }
                    ops.push(op_str);
                }
            }
        }

        while (!ops.isEmpty()) {
            QString op = ops.pop();
            if (isFunction(op)) {
                applyUnaryOperation(op);
            } else {
                if (values.size() < 2) throw std::invalid_argument("Syntax Error");
                long double val2 = values.pop();
                long double val1 = values.pop();
                values.push(applyOp(val1, val2, op));
            }
        }

        if (!values.isEmpty()) {
            lastResult = values.top();
            display->setText(QString::number(lastResult, 'g', 15));
        }

    } catch (const std::invalid_argument& e) {
        display->setText("Error: " + QString(e.what()));
    }

    waitingForOperand = true;
    hideMatrixResult();
}