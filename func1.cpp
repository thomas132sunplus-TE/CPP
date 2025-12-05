// 簡易互動式計算機
// 支援：加、減、乘、除、次方、以 b 為底的對數、sin(x)、cos(x)
// 使用者介面：選單 + 輸入數值並顯示結果

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <string>

// Calculator 類別：封裝所有數學運算
class Calculator {
public:
    // 加法 a + b
    double add(double a, double b) const { return a + b; }

    // 減法 a - b
    double sub(double a, double b) const { return a - b; }

    // 乘法 a * b
    double mul(double a, double b) const { return a * b; }

    // 除法 a / b（若 b == 0 則丟出例外）
    double div(double a, double b) const {
        if (b == 0.0) throw std::domain_error("Division by zero");
        return a / b;
    }

    // 次方 a^b
    double power(double a, double b) const { return std::pow(a, b); }

    // 以 b 為底的對數 log_b(a) = ln(a) / ln(b)
    // 要求 a > 0, b > 0 且 b != 1，否則丟出例外
    double log_ab(double a, double b) const {
        if (a <= 0.0) throw std::domain_error("log domain error: a must be > 0");
        if (b <= 0.0 || b == 1.0) throw std::domain_error("log base error: b must be > 0 and != 1");
        return std::log(a) / std::log(b);
    }

    // 正弦（以弧度為單位）
    double sinx(double x) const { return std::sin(x); }

    // 餘弦（以弧度為單位）
    double cosx(double x) const { return std::cos(x); }
};

// 清除 stdin 的剩餘資料（用於輸入錯誤後恢復）
void clear_stdin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// 讀取 double 並做基本驗證（若輸入非數字會重試）
double read_double(const std::string& prompt) {
    double v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) {
            clear_stdin();
            return v;
        }
        std::cout << "Invalid number, please try again.\n";
        clear_stdin();
    }
}

// 讀取整數選項並限制在 [minv, maxv]
int read_int_choice(int minv, int maxv, const std::string& prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v && v >= minv && v <= maxv) {
            clear_stdin();
            return v;
        }
        std::cout << "Please enter a number between " << minv << " and " << maxv << ".\n";
        clear_stdin();
    }
}

int main() {
    Calculator calc;

    // 固定數字輸出格式（小數點後 9 位）
    std::cout << std::fixed << std::setprecision(9);

    // 主迴圈：顯示選單並處理使用者輸入
    while (true) {
        std::cout << "\n=== Calculator Menu ===\n"
                  << "1) add(a,b)\n"
                  << "2) sub(a,b)\n"
                  << "3) mul(a,b)\n"
                  << "4) div(a,b)\n"
                  << "5) power(a,b)\n"
                  << "6) log(a,b)   (log base b of a)\n"
                  << "7) sin(x)     (x in radians)\n"
                  << "8) cos(x)     (x in radians)\n"
                  << "0) Exit\n";
        // 讀取使用者選項（0-8）
        int opt = read_int_choice(0, 8, "Choose an option: ");

        if (opt == 0) {
            // 使用者選離開
            std::cout << "Goodbye.\n";
            break;
        }

        try {
            // 根據選項讀取參數並呼叫 Calculator 的對應方法
            switch (opt) {
                case 1: {
                    // 加法
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.add(a, b) << '\n';
                    break;
                }
                case 2: {
                    // 減法
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.sub(a, b) << '\n';
                    break;
                }
                case 3: {
                    // 乘法
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.mul(a, b) << '\n';
                    break;
                }
                case 4: {
                    // 除法（若 b 為 0 會拋出例外並被 catch）
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.div(a, b) << '\n';
                    break;
                }
                case 5: {
                    // 次方
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.power(a, b) << '\n';
                    break;
                }
                case 6: {
                    // 對數（以 b 為底）
                    double a = read_double("a = ");
                    double b = read_double("base b = ");
                    std::cout << "result = " << calc.log_ab(a, b) << '\n';
                    break;
                }
                case 7: {
                    // sin（輸入以弧度）
                    double x = read_double("x (radians) = ");
                    std::cout << "result = " << calc.sinx(x) << '\n';
                    break;
                }
                case 8: {
                    // cos（輸入以弧度）
                    double x = read_double("x (radians) = ");
                    std::cout << "result = " << calc.cosx(x) << '\n';
                    break;
                }
                default:
                    std::cout << "Unknown option.\n";
            }
        } catch (const std::exception& e) {
            // 捕捉所有例外並印出錯誤訊息，程式會繼續回到選單
            std::cout << "Error: " << e.what() << '\n';
        }
    }

    return 0;
}