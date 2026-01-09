#include "CalculatorEngine.h"
#include <numeric>
#include <stdexcept>

CalculatorEngine::CalculatorEngine() {}

double CalculatorEngine::add(const std::vector<double>& numbers) {
    double sum = 0.0;
    for (double num : numbers) {
        sum += num;
    }
    return sum;
}

double CalculatorEngine::multiply(const std::vector<double>& numbers) {
    double product = 1.0;
    for (double num : numbers) {
        product *= num;
    }
    return product;
}

long long CalculatorEngine::modulo(long long a, long long b) {
    if (b == 0) {
        throw std::invalid_argument("Modulo by zero is undefined.");
    }
    return a % b;
}

double CalculatorEngine::sine(double angleDegrees) {
    return std::sin(angleDegrees * M_PI / 180.0);
}

double CalculatorEngine::cosine(double angleDegrees) {
    return std::cos(angleDegrees * M_PI / 180.0);
}

double CalculatorEngine::tangent(double angleDegrees) {
    return std::tan(angleDegrees * M_PI / 180.0);
}

double CalculatorEngine::cosecant(double angleDegrees) {
    return 1.0 / sine(angleDegrees);
}

double CalculatorEngine::secant(double angleDegrees) {
    return 1.0 / cosine(angleDegrees);
}

double CalculatorEngine::cotangent(double angleDegrees) {
    return 1.0 / tangent(angleDegrees);
}

double CalculatorEngine::power(double base, double exponent) {
    return std::pow(base, exponent);
}

long double CalculatorEngine::root(long double number, int r) {
    if (number < 0 && r % 2 != 0) {
        return -std::powl(-number, 1.0L / r);
    }
    return std::powl(number, 1.0L / r);
}

double CalculatorEngine::exponential(double x) {
    return std::exp(x);
}

double CalculatorEngine::naturalLog(double number) {
    return std::log(number);
}

double CalculatorEngine::logBase(double number, double base) {
    return std::log(number) / std::log(base);
}

double CalculatorEngine::sinh(double x) {
    return std::sinh(x);
}

double CalculatorEngine::cosh(double x) {
    return std::cosh(x);
}

double CalculatorEngine::tanh(double x) {
    return std::tanh(x);
}

double CalculatorEngine::cosech(double x) {
    return 1.0 / std::sinh(x);
}

double CalculatorEngine::sech(double x) {
    return 1.0 / std::cosh(x);
}

double CalculatorEngine::coth(double x) {
    return 1.0 / std::tanh(x);
}

double CalculatorEngine::arcsinh(double x) {
    return std::asinh(x);
}

double CalculatorEngine::arccosh(double x) {
    return std::acosh(x);
}

double CalculatorEngine::arctanh(double x) {
    return std::atanh(x);
}

double CalculatorEngine::arcsin(double x) {
    return std::asin(x) * 180.0 / M_PI;
}

double CalculatorEngine::arccos(double x) {
    return std::acos(x) * 180.0 / M_PI;
}

double CalculatorEngine::arctan(double x) {
    return std::atan(x) * 180.0 / M_PI;
}

double CalculatorEngine::arcsec(double x) {
    return std::acos(1.0 / x) * 180.0 / M_PI;
}

double CalculatorEngine::arccsc(double x) {
    return std::asin(1.0 / x) * 180.0 / M_PI;
}

double CalculatorEngine::arccot(double x) {
    return std::atan(1.0 / x) * 180.0 / M_PI;
}

double CalculatorEngine::arccosech(double x) {
    return std::asinh(1.0 / x);
}

double CalculatorEngine::arcsech(double x) {
    return std::acosh(1.0 / x);
}

double CalculatorEngine::arccoth(double x) {
    return std::atanh(1.0 / x);
}

long long CalculatorEngine::factorial(int n) {
    if (n < 0) {
        return -1; // Or throw an exception
    }
    if (n == 0) {
        return 1;
    }
    long long res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

CalculatorEngine::QuadraticSolution CalculatorEngine::solveQuadratic(double a, double b, double c) {
    QuadraticSolution solution;
    if (a == 0) {
        solution.hasRealRoots = false;
        solution.errorMessage = "Coefficient 'a' cannot be zero.";
        return solution;
    }
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        solution.hasRealRoots = true;
        solution.root1 = (-b + std::sqrt(discriminant)) / (2 * a);
        solution.root2 = (-b - std::sqrt(discriminant)) / (2 * a);
    } else if (discriminant == 0) {
        solution.hasRealRoots = true;
        solution.root1 = solution.root2 = -b / (2 * a);
    } else {
        solution.hasRealRoots = false;
        solution.errorMessage = "No real roots.";
    }
    return solution;
}

CalculatorEngine::SimultaneousSolution CalculatorEngine::solveSimultaneous(double a1, double b1, double c1, double a2, double b2, double c2) {
    SimultaneousSolution solution;
    double determinant = a1 * b2 - a2 * b1;
    if (determinant == 0) {
        solution.hasSolution = false;
        solution.errorMessage = "No unique solution.";
    } else {
        solution.hasSolution = true;
        solution.x = (c1 * b2 - c2 * b1) / determinant;
        solution.y = (a1 * c2 - a2 * c1) / determinant;
    }
    return solution;
}

long long CalculatorEngine::permutation(int n, int r) {
    if (n < r || n < 0 || r < 0) {
        return -1; // Invalid input
    }
    return factorial(n) / factorial(n - r);
}

long long CalculatorEngine::combination(int n, int r) {
    if (n < r || n < 0 || r < 0) {
        return -1; // Invalid input
    }
    return permutation(n, r) / factorial(r);
}

long long CalculatorEngine::gcd(long long a, long long b) {
    return std::abs(std::gcd(a, b));
}

long long CalculatorEngine::lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return std::abs(a * b) / gcd(a, b);
}

long long CalculatorEngine::modularInverse(long long a, long long m) {
    a = a % m;
    for (long long x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

bool CalculatorEngine::areCoprime(const std::vector<long long>& numbers) {
    for (size_t i = 0; i < numbers.size(); ++i) {
        for (size_t j = i + 1; j < numbers.size(); ++j) {
            if (gcd(numbers[i], numbers[j]) != 1) {
                return false;
            }
        }
    }
    return true;
}

CalculatorEngine::CRTResult CalculatorEngine::solveChineseRemainderTheorem(const std::vector<CRTEquation>& equations) {
    CRTResult result;
    if (equations.empty()) {
        result.solvable = false;
        result.errorMessage = "No equations provided.";
        return result;
    }

    std::vector<long long> a_coeffs, b_coeffs, m_moduli;
    for (const auto& eq : equations) {
        a_coeffs.push_back(eq.a);
        b_coeffs.push_back(eq.b);
        m_moduli.push_back(eq.m);
    }

    if (!areCoprime(m_moduli)) {
        result.solvable = false;
        result.errorMessage = "Moduli are not pairwise coprime.";
        return result;
    }

    long long M = 1;
    for (long long m : m_moduli) {
        M *= m;
    }

    long long solution = 0;
    for (size_t i = 0; i < equations.size(); ++i) {
        long long a_i = a_coeffs[i];
        long long b_i = b_coeffs[i];
        long long m_i = m_moduli[i];
        long long M_i = M / m_i;
        long long inv_M_i = modularInverse(M_i, m_i);
        long long inv_a_i = modularInverse(a_i, m_i);
        if (inv_a_i == -1) {
            result.solvable = false;
            result.errorMessage = "Modular inverse does not exist for one of the equations.";
            return result;
        }
        solution += (b_i * inv_a_i % m_i) * M_i * inv_M_i;
    }

    result.solvable = true;
    result.solutionX = solution % M;
    result.modulusM = M;
    return result;
}

Matrix CalculatorEngine::matrixAdd(const Matrix& a, const Matrix& b) {
    if (a.size() != b.size() || a[0].size() != b[0].size()) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }
    Matrix result(a.size(), std::vector<double>(a[0].size()));
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[0].size(); ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}

Matrix CalculatorEngine::matrixMultiply(const Matrix& a, const Matrix& b) {
    if (a[0].size() != b.size()) {
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }
    Matrix result(a.size(), std::vector<double>(b[0].size(), 0.0));
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b[0].size(); ++j) {
            for (size_t k = 0; k < a[0].size(); ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}