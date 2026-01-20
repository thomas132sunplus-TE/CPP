#include<iostream>
#include<string>
using namespace std;

int main() {

    string str1 ;
    string str2 = "lyida";
    string str3(str2);

    cout << " str1 是否為空字串" << str1.empty()<< endl;
    cout << " str2 的長度為 : "  << str2.size() << endl;
    cout << " str3 的長度為 : "  << str3.size() << endl;

    cout << " str1 是否等於 str2 ? " << ( str1 == str2 ) << endl;
    cout << " str2 是否等於 str3 ? " << ( str2 == str3 ) << endl;
}