#include <iostream>
#include <cmath>

int main() {
    double x;
    std::cout << "Enter x: ";
    if (!(std::cin >> x)) return 0;
    double y = std::pow(x, 5.0);
    std::cout << "y = x^5 = " << y << std::endl;
    return 0;
}