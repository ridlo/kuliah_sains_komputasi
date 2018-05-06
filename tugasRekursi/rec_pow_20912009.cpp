#include<iostream>
using namespace std;

double pow(double x, int n){
    double res;
    if (n == 0) {res = 1;}
    else {res = x*pow(x, n-1);}
    return res;}

int main(){
    double x;
    int n;
    cout << " x = "; cin >> x;
    cout << " n = "; cin >> n;
    if (n < 0) { n = -n; cout << 1/pow(x, n) << "\n";}
    else { cout << pow(x, n) << "\n";}
    return 0;}
