#include <iostream>
#include <stdlib.h>
#include "lcg.h"
using namespace std;

int main(){
    int i;
    srand(time(NULL));
    for (i=0;i<10;i++){
        cout << rand()%2 << endl;}

    rseed(time(NULL));
    for (i=0;i<10;i++){
        cout << "\n" << randu()%2;}
    return 0;
}
