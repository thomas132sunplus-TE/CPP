#include<iostream>
#include<string>
#include"account1.h"
using namespace std;

string to_string (Account &acct) {
        return string( "Account(" ) +
               acct.id + " , " +
               acct.name + " , " +
               std::to_string(acct.balance)+")";  
    }

void deposit (Account &acct,double amount) {
     if (amount <= 0 ) {
        cout << "必須存入正數" << endl;
        return;
     }
     acct.balance += amount;
}

void withdraw (Account &acct,double amount) {
    if  (acct.balance < amount) {
        cout << "餘額不足" << endl;
        return;
    }
    acct.balance -= amount;
}

int main() {

    Account acct1("123-456-789","Justin-Lin",1000 );
    cout << to_string(acct1) << endl;

    deposit(acct1,500);
    cout << to_string(acct1) << endl;

    withdraw(acct1,700);
    cout << to_string(acct1) << endl;

    return 0;
}