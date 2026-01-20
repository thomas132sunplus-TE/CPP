#include<iostream>
#include<windows.h>
using namespace std;

int gcd(int m , int n);

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int m = 0;
    int n = 0;

    cout << "請輸入兩數 : " ;
    cin >> m >> n;
    cout << " gcd : " << gcd(m,n) << endl;
    
    return 0;
}

int gcd(int m, int n ){
    if (n == 0){
       return m;
    }
    else{
        cout << '('<< n << ',' << m%n << ')'<<"->"; 
        gcd(n,m%n) ;
    }
}
