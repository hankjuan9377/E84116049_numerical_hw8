#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int N = 8;
double x[N] = {4.0, 4.2, 4.5, 4.7, 5.1, 5.5, 5.9, 6.3};
double y[N] = {102.6, 113.2, 130.1, 142.1, 167.5, 195.1, 224.9, 256.8};

int main() {
    double Sx = 0, Sx2 = 0, Sy = 0, Sxy = 0;

    for (int i = 0; i < N; i++) {
        double xi = x[i];
        double Yi = log(y[i]); // ln(y)
        Sx += xi;
        Sx2 += xi * xi;
        Sy += Yi;
        Sxy += xi * Yi;
    }

    // Solve linear system for ln(y) = a*x + ln(b)
    double denominator = N * Sx2 - Sx * Sx;
    double a = (N * Sxy - Sx * Sy) / denominator;
    double ln_b = (Sx2 * Sy - Sx * Sxy) / denominator;
    double b = exp(ln_b);

    cout << fixed << setprecision(6);
    cout << "Exponential fit: y = " << b << " * e^(" << a << "x)" << endl;

    // Compute sum of squared errors
    double error = 0;
    for (int i = 0; i < N; i++) {
        double y_fit = b * exp(a * x[i]);
        error += pow(y[i] - y_fit, 2);
    }

    cout << "Sum of squared errors: " << error << endl;
    return 0;
}

