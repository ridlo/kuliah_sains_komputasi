#include<iostream>
using namespace std;

int gcd(int x, int y){
    int res;
    if (y == 0) {res = x;}
    else {res = gcd(y, x%y);}
    return res;}

int main(){
    int a, b, c;
    cout << "Program menghitung FPB dari dua bilangan\n";
    cout << "Bilangan pertama : "; cin >> a;
    cout << "Bilangan kedua   : "; cin >> b;
    if (a < 0 || b < 0) {cout << "Masukkan angka > 0 \n";}
    else {
        if (a < b) { c = a; a = b; b = c;}
        cout << "FPB " << a << " dan " << b << " = " << gcd(a, b) << "\n";}

    return 0;}
     
