#include <iostream>
#include <windows.h>
#include "account0.h"
using namespace std;

// --- 值版本 (call by value) ---
void printAcct(Account acct) {
    cout << "Account (值傳遞)"
         << "(" << acct.id
         << "," << acct.name
         << "," << acct.balance
         << ")" << endl;
}

// --- 參考版本 (call by reference) ---
void printAcctRef(Account &acct) {
    cout << "Account (參考傳遞)"
         << "(" << acct.id
         << "," << acct.name
         << "," << acct.balance
         << ")" << endl;
}

// --- 指標版本 (call by pointer) ---
void printAcctPtr(Account *acct) {
    cout << "Account (指標傳遞)"
         << "(" << acct->id
         << "," << acct->name
         << "," << acct->balance
         << ")" << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Account acct1;
    acct1.id = "123-456-789";
    acct1.name = "Justin Lin";
    acct1.balance = 1000;
    
    printAcct(acct1);// 呼叫值傳遞    
    printAcctRef(acct1);// 呼叫參考傳遞    
    printAcctPtr(&acct1);// 呼叫指標傳遞

    // 動態配置一個帳號
    Account *acct2 = new Account();
    acct2->id = "987-654-321";
    acct2->name = "Monica Huang";
    acct2->balance = 2000;

    // 這裡只能用參考傳遞和指標傳遞
    printAcct(*acct2);     // 值傳遞 (會複製一份)
    printAcctRef(*acct2);  // 參考傳遞
    printAcctPtr(acct2);   // 指標傳遞

    delete acct2; // 釋放記憶體
    return 0;
}
