#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int N = 8;
double x[N] = {4.0, 4.2, 4.5, 4.7, 5.1, 5.5, 5.9, 6.3};
double y[N] = {102.6, 113.2, 130.1, 142.1, 167.5, 195.1, 224.9, 256.8};

int main() {
    double Slnx = 0, Slnx2 = 0, Slny = 0, Slnxlny = 0;

    for (int i = 0; i < N; i++) {
        double lnx = log(x[i]);
        double lny = log(y[i]);

        Slnx += lnx;
        Slnx2 += lnx * lnx;
        Slny += lny;
        Slnxlny += lnx * lny;
    }

    // Solve linear regression: ln(y) = n ln(x) + ln(b)
    double denominator = N * Slnx2 - Slnx * Slnx;
    double n = (N * Slnxlny - Slnx * Slny) / denominator;
    double ln_b = (Slnx2 * Slny - Slnx * Slnxlny) / denominator;
    double b = exp(ln_b);

    cout << fixed << setprecision(6);
    cout << "Power fit: y = " << b << " * x^" << n << endl;

    // Compute sum of squared errors
    double error = 0;
    for (int i = 0; i < N; i++) {
        double y_fit = b * pow(x[i], n);
        error += pow(y[i] - y_fit, 2);
    }

    cout << "Sum of squared errors: " << error << endl;
    return 0;
}


