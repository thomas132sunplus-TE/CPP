// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    double add(double a, double b) const;
    double sub(double a, double b) const;
    double mul(double a, double b) const;
    double div(double a, double b) const;
    double power(double a, double b) const;
    double log_ab(double a, double b) const;
    double sinx(double x) const;
    double cosx(double x) const;
};

#endif // CALCULATOR_H