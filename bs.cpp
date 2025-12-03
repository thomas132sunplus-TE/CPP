#include <iostream>
#include <string>
using namespace std;

class Account {
public:
    string id = "abc-789";
    string name;
    double balance;

    Account() = default;  // ✅ 預設建構子
    Account(string id, string name, double balance)
        : id(id), name(name), balance(balance) {this->balance = 0.9999;}
};

int main() {
    Account a1;  // 使用預設建構子
    Account a3;  // 使用預設建構子
    Account a2("123", "Justin", 1000);  // 使用自訂建構子

    cout << "a1: " << a1.id << ", " << a1.name << ", " << a1.balance << endl;
    cout << "a3: " << a3.id << ", " << a3.name << ", " << a3.balance << endl;
    cout << "a2: " << a2.id << ", " << a2.name << ", " << a2.balance << endl;
}