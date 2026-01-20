#include<iostream>
#include<windows.h>
using namespace std;

int* makeArray(int m, int initial = 0 ){
    int *a = new int[m];
    for (int i = 0; i < m ; i++) {
        a[i] = initial ;
    } 
    return a;
}

void deleteArray (int *arr){
    delete [] arr;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int m = 0;
    cout << " 請輸入陣列長度 m -> ";
    cin >> m;

    int *arr = makeArray(m,6);
    for (int i = 0 ; i < m ; i++){
        cout << "arr[" << i << "]" << " = " << arr[i] << endl;
    }
   
    delete [] arr; 
return 0;


}