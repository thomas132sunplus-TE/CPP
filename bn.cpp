#include <iostream>
#include "account0.h"
using namespace std;

void printAcct(Account *acct) {
    cout << "Account (*ptr)"
         << "(" << acct->id
         << "," << acct->name
         << "," << acct->balance
         << ")" << endl;
}


void printAcct(Account &acct) {
    cout << "Account (&ref)"
         << "(" << acct.id
         << "," << acct.name
         << "," << acct.balance
         << ")" << endl;
}

int main() {
    Account acct1;
    acct1.id = "123-456-789";
    acct1.name = "Justin Lin";
    acct1.balance = 1000;
    printAcct(acct1);   // ✅ 呼叫參考版本

    Account *acct2 = new Account();
    acct2->id = "987-654-321";
    acct2->name = "Monica Huang";
    acct2->balance = 2000;
    printAcct(acct2);   // ✅ 呼叫指標版本

    delete acct2;  // 記得釋放
    return 0;
}
