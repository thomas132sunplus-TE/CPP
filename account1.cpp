#include <string>
#include "account1.h"
using namespace std;

Account::Account(string id, string name, double balance) {
    this->id = id;
    this->name = name;
    this->balance = balance;
}