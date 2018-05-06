#include<iostream>
#include<stdlib.h>
#include<time.h>
#include "lcg.h"
using namespace std;

int main(){
    srand(time(NULL));
    for (int i=0;i<5;i++){
        cout << rand() << endl;}
    cout << RAND_MAX;
    cout << "\n";
    rseed(time(NULL));
    for (int i=0;i<5;i++){
        cout << randu() << endl;}
    cout << MAX_RAND;
    return 0;
}
