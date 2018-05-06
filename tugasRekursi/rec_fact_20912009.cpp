#include<iostream>
using namespace std;

double fact(double n){ //double: agar bisa untuk int(n) yang besar
    double res;
    if (n == 0){res = 1;}
    else{res = n*fact(n-1);}
    return res;}
    

int main(){
    int n;
    cout << "Program menghitung n!\n" ;
    cout << "n = "; cin >> n;
    if (n < 0) {cout << "hanya untuk bilangan n>=0\n"; return 0;}
    else{cout << n << "! = " << fact(n) << "\n";}
    
    return 0;}
