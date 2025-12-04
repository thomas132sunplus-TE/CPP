#include <iostream>
#include <string>

class Account {
public:
    std::string id = "abc-789";
    std::string name;
    double balance = 0.0;

    Account() = default;
    Account(const std::string& id, const std::string& name, double balance)
        : id(id), name(name), balance(balance) {}
};

int main() {
    Account a1;
    Account a3;
    Account a2("123456abcd", "Justin", 1000.0);

    std::cout << "a1: " << a1.id << ", " << a1.name << ", " << a1.balance << std::endl;
    std::cout << "a3: " << a3.id << ", " << a3.name << ", " << a3.balance << std::endl;
    std::cout << "a2: " << a2.id << ", " << a2.name << ", " << a2.balance << std::endl;
    return 0;
}