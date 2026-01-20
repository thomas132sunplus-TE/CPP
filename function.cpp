#include <iostream>
#include <cmath>
#include <stdexcept>
#include <windows.h>
#include <iomanip>

class Calculator {
public:
    // 基本算術
    double add(double a, double b) const { return a + b; }
    double sub(double a, double b) const { return a - b; }
    double mul(double a, double b) const { return a * b; }
    double div(double a, double b) const {
        if (b == 0.0) throw std::domain_error("Division by zero");
        return a / b;
    }

    // 自然對數（ln），對非正數丟例外
    double ln(double x) const {
        if (x <= 0.0) throw std::domain_error("Log domain error: x must be > 0");
        return std::log(x);
    }

    // 次方 a^b
    double power(double a, double b) const { return std::pow(a, b); }

    // 正弦（以弧度為單位）
    double sinx(double x) const { return std::sin(x); }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);        // 啟用 UTF-8 輸出
    Calculator calc;
    try {
        std::cout << std::fixed << std::setprecision(9);
        std::cout << "3 + 2 = " << calc.add(3,2) << '\n';
        std::cout << "3 - 2 = " << calc.sub(3,2) << '\n';
        std::cout << "3 * 2 = " << calc.mul(3,2) << '\n';
        std::cout << "3 / 2 = " << calc.div(3,2) << '\n';
        std::cout << "ln(2.718281828) ≈ " << calc.ln(2.718281828) << '\n';
        std::cout << "2^8 = " << calc.power(2,8) << '\n';
        std::cout << "sin(pi/2) = " << calc.sinx(3.14159265358979323846/2.0) << '\n';
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}