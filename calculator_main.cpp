// main.cpp
// 互動式選單與輸入處理（保留中文註解）
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

#include "calculator.h"

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
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.add(a, b) << '\n';
                    break;
                }
                case 2: {
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.sub(a, b) << '\n';
                    break;
                }
                case 3: {
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.mul(a, b) << '\n';
                    break;
                }
                case 4: {
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.div(a, b) << '\n';
                    break;
                }
                case 5: {
                    double a = read_double("a = ");
                    double b = read_double("b = ");
                    std::cout << "result = " << calc.power(a, b) << '\n';
                    break;
                }
                case 6: {
                    double a = read_double("a = ");
                    double b = read_double("base b = ");
                    std::cout << "result = " << calc.log_ab(a, b) << '\n';
                    break;
                }
                case 7: {
                    double x = read_double("x (radians) = ");
                    std::cout << "result = " << calc.sinx(x) << '\n';
                    break;
                }
                case 8: {
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