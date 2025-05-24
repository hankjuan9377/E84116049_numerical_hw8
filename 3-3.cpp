#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793;


double f(double x) {
    return x * x * sin(x);
}


double S4(double x) {
    double a0 = 0.459205;
    double a[] = {-0.146756, 0.054608, -0.038929, 0.033542};
    double b[] = {0.232287, -0.124941, 0.082932, 0};
    double sum = a0 ;
    for (int k = 1; k <= 4; ++k) {
        sum += a[k - 1] * cos(k * PI*(2*x-1));
        sum += b[k - 1] * sin(k * PI*(2*x-1));
    }
    return sum;
}

int main() {
    int m = 32;
    double error = 0.0;

    for (int j = 0; j < m; ++j) {
        double xj = static_cast<double>(j) / m;
        double diff = f(xj) - S4(xj);
        error += diff * diff;
    }

    cout << "E(S4) = " << error << endl;
    return 0;
}

