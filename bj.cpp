#include<iostream>
using namespace std;

string&  longerStr (string &s1, string &s2) {
    return s1.length() > s2.length() ? s1 : s2 ;
} 

int main(){
    string s1  = " Merry and Jorge";
    string s2  = " Lydia thomas ";
    string &s3 = longerStr(s1, s2);

    cout << s3 << endl;
}