#include <iostream>
#include <string>
using namespace std;

class Account {
public:
    string id = "000-000-000";
    string name = "Anonymous";
    double balance ;  // 沒初始化！
};

int main() {
    Account acct1;
    Account acct2;
    cout << "id: " << acct1.id << endl;
    cout << "name: " << acct1.name << endl;
    cout << "balance: " << acct1.balance << endl;  // ⚠️ 不可預期！

    cout << "id: " << acct2.id << endl;
    cout << "name: " << acct2.name << endl;
    cout << "balance: " << acct2.balance << endl;  // ⚠️ 不可預期！
}