#include <iostream>
using namespace std;

double dy(double x, double y){
    return y;}

int main()
{
    double x0 = 0.0;
    double y0 = 1.0;
    double h  = 0.5;
    double k1, k2, k3, k4, x1, y1;

    k1 = h*dy(x0, y0);
    k2 = h*dy(x0+h/2., y0+k1/2.);
    k3 = h*dy(x0+h/2., y0+k2/2.);
    k4 = h*dy(x0+h, y0+k3);
    
    cout << x0 << " " << y0 << endl;
    cout << x0+h << " " << y0+k1 << endl;

    cout << x0+h/2. << " " << y0+k1/2. << endl;
    cout << x0+h/2.+h << " " << y0+k1/2.+k2 << endl;

    cout << x0+h/2. << " " << y0+k2/2. << endl;
    cout << x0+h/2.+h << " " << y0+k2/2.+k3 << endl;

    cout << x0+h << " " << y0+k3 << endl;
    cout << x0+h+h << " " << y0+k3+k4 << endl;

    cout << x0 << " " << y0 << endl;
    cout << x0+h << " " << y0+(k1+2.*k2+2.*k3+k4)/6. << endl;

    return 0;}

