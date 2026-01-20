
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    double x = std::rand() % 100 + 1; // 1~100 的亂數
    std::cout << "Random x: " << x << std::endl;
    double y = std::pow(x, 2.0) + 100;
    std::cout << "y = x^2 + 100 = " << y << std::endl;
    return 0;
}
