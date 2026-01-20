#include<iostream>
#include<string>
#include"account2.h"
using namespace std;

Account::Account(string id, string name, double balance){
      this->id = id;
      this->name = name;
      this->balance = balance;
} 
string Account::to_string(){
      return string( "Account(" )+
      this->id + " , " +
      this->name + " , " +
      std::to_string(this->balance)+")";
}
void Account::deposit(double amount){
      if (amount<=0){
            cout << "需存入整數"; 
            return;
      }
      this->balance += amount;
}
void Account::withdraw(double amount){
      if (this->balance < amount ){
            cout << "餘額不足";
            return;
      }
      this->balance -= amount;
}
