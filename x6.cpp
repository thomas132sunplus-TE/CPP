#include <iostream>
#include <cmath>

int main() {
    double x;
    std::cout << "Enter x: ";
    if (!(std::cin >> x)) return 0;
    double y = std::pow(x, 6.0) + 1;
    std::cout << "y = x^6 + 1 = " << y << std::endl;
    return 0;
}
