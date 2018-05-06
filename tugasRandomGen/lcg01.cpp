#include <iostream>
#include <fstream>
#include <math.h>
#include <limits.h>
using namespace std;

int main(){
    unsigned int state_i, state_f;
    unsigned int seed, multiplier, increment, modulo;

    seed = 10;
    
    // Linear Congruential Generator
    unsigned int N = INT_MAX;//2147483648; 
    multiplier = 1103515245;
    increment = 12345;
    modulo = pow(2,31);
    state_i = seed;

    ofstream out("random.txt");
    out << state_i;
    for (int i=1;i<N;i++){
        state_f = (multiplier*state_i + increment)%modulo;
        out <<  endl << state_f;
        state_i = state_f;}
    out.close();

    // output file, random number
    //ofstream out("random.txt");
    //for (int i=0;i<1000;i++){
    //    out << state[i] << endl;}
    //out.close();

    cout << "finish\n";
    return 0;
}
