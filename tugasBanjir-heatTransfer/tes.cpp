#include<iostream>
#include<math.h>
using namespace std;

float f(float a){
    float d[2] = {1.,4.};
    return d;}

int main(){
    float a = 3.5 - 4.1;
    
    cout << fabs(a) << endl;
    cout << (float) 2/ (float) 3 << endl ;
    cout << pow(2, 4) << endl;
    cout << min(3.12, 5.24) << endl;
    cout << sqrt(100.1) << endl;
    cout << sqrt(0.0) << endl;
    float b[3] = {1.,4.,3};
    float c[2];
    c[2] = f(a);
    cout << c[1] << "\n";
    cout << "tes\n";
    /*float c[2][3];
    for (int i=0;i<3;i++){
        c[0][i] = b[i];}
    
    for (int i=0;i<3;i++){
        cout << c[0][i] << " ";}
        cout << "\n";
*/
    return 0;
}
