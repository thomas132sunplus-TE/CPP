// calculator.cpp
#include "calculator.h"
#include <cmath>
#include <stdexcept>

double Calculator::add(double a, double b) const { return a + b; }
double Calculator::sub(double a, double b) const { return a - b; }
double Calculator::mul(double a, double b) const { return a * b; }
double Calculator::div(double a, double b) const {
    if (b == 0.0) throw std::domain_error("Division by zero");
    return a / b;
}
double Calculator::power(double a, double b) const { return std::pow(a, b); }
double Calculator::log_ab(double a, double b) const {
    if (a <= 0.0) throw std::domain_error("log domain error: a must be > 0");
    if (b <= 0.0 || b == 1.0) throw std::domain_error("log base error: b must be > 0 and != 1");
    return std::log(a) / std::log(b);
}
double Calculator::sinx(double x) const { return std::sin(x); }
double Calculator::cosx(double x) const { return std::cos(x); }