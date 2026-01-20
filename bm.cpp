#include <iostream>
#include "account0.h"
using namespace std;

void printAcct (Account *acct){
    cout << "Account ("  
         << acct->id << ","
         << acct->name << ","
         << acct->balance<< ")"
         << endl;
}

void printAcct(Account &acct){
     printAcct(&acct);
}

int main(){
    Account acct1;
    acct1.id = "123-456-789";
    acct1.name = "Justin Lin";
    acct1.balance = 1000;
    printAcct(acct1); 

    Account *acct2 = new Account(); 
    acct2->id = "987-654-321";
    acct2->name = "Monica Huang";
    acct2->balance = 1000;
    printAcct(acct2);
    delete acct2;
    
    return 0;
}