#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <string>
#include <vector>
#include <cmath>

// Define Matrix as a vector of vectors of doubles
using Matrix = std::vector<std::vector<double>>;

class CalculatorEngine
{
public:
    CalculatorEngine();

    // Basic Arithmetic
    double add(const std::vector<double>& numbers);
    double multiply(const std::vector<double>& numbers);
    long long modulo(long long a, long long b); // New: Modulo function

    // Trigonometric Functions
    double sine(double angleDegrees);
    double cosine(double angleDegrees);
    double tangent(double angleDegrees);
    double cosecant(double angleDegrees);
    double secant(double angleDegrees);
    double cotangent(double angleDegrees);

    // Exponentiation and Roots
    double power(double base, double exponent);
    long double root(long double number, int r);
    double exponential(double x);

    // Logarithms
    double naturalLog(double number);
    double logBase(double number, double base);

    // Hyperbolic Functions
    double sinh(double x);
    double cosh(double x);
    double tanh(double x);
    double cosech(double x);
    double sech(double x);
    double coth(double x);
    double arcsinh(double x);
    double arccosh(double x);
    double arctanh(double x);
    double arcsin(double x);
    double arccos(double x);
    double arctan(double x);
    double arcsec(double x);
    double arccsc(double x);
    double arccot(double x);
    double arccosech(double x);
    double arcsech(double x);
    double arccoth(double x);

    // Factorial
    long long factorial(int n);

    // Quadratic Equation Solver
    struct QuadraticSolution {
        bool hasRealRoots;
        double root1;
        double root2;
        std::string errorMessage;
    };
    QuadraticSolution solveQuadratic(double a, double b, double c);

    // Simultaneous Equation Solver (2x2)
    struct SimultaneousSolution {
        bool hasSolution;
        double x;
        double y;
        std::string errorMessage;
    };
    SimultaneousSolution solveSimultaneous(double a1, double b1, double c1, double a2, double b2, double c2);

    // Combinatorics
    long long permutation(int n, int r);
    long long combination(int n, int r);

    // Number Theory
    long long gcd(long long a, long long b);
    long long lcm(long long a, long long b);
    long long modularInverse(long long a, long long m);
    bool areCoprime(const std::vector<long long>& numbers);

    // Chinese Remainder Theorem
    struct CRTEquation {
        long long a;
        long long b;
        long long m;
    };
    struct CRTResult {
        bool solvable;
        long long solutionX;
        long long modulusM;
        std::string errorMessage;
    };
    CRTResult solveChineseRemainderTheorem(const std::vector<CRTEquation>& equations);

    // Matrix Operations
    Matrix matrixAdd(const Matrix& a, const Matrix& b);
    Matrix matrixMultiply(const Matrix& a, const Matrix& b);

private:
    // Helper functions

};

#endif // CALCULATORENGINE_H