#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int N = 8;

double x[N] = {4.0, 4.2, 4.5, 4.7, 5.1, 5.5, 5.9, 6.3};
double y[N] = {102.6, 113.2, 130.1, 142.1, 167.5, 195.1, 224.9, 256.8};

int main() {
    double Sx = 0, Sx2 = 0, Sx3 = 0, Sx4 = 0;
    double Sy = 0, Sxy = 0, Sx2y = 0;

    for (int i = 0; i < N; i++) {
        double xi = x[i];
        double yi = y[i];
        double xi2 = xi * xi;
        double xi3 = xi2 * xi;
        double xi4 = xi3 * xi;

        Sx += xi;
        Sx2 += xi2;
        Sx3 += xi3;
        Sx4 += xi4;
        Sy += yi;
        Sxy += xi * yi;
        Sx2y += xi2 * yi;
    }

    // Construct normal equations matrix
    double A[3][4] = {
        {Sx4, Sx3, Sx2, Sx2y},
        {Sx3, Sx2, Sx, Sxy},
        {Sx2, Sx, 8, Sy}
    };

    // Gaussian elimination
    for (int i = 0; i < 3; i++) {
        double pivot = A[i][i];
        for (int j = 0; j < 4; j++) A[i][j] /= pivot;

        for (int k = 0; k < 3; k++) {
            if (k == i) continue;
            double factor = A[k][i];
            for (int j = 0; j < 4; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }

    double a = A[0][3];
    double b = A[1][3];
    double c = A[2][3];

    cout << fixed << setprecision(6);
    cout << "Best-fit quadratic polynomial: y = "
         << a << "x^2 + " << b << "x + " << c << endl;

    // Compute the error (sum of squared errors)
    double error = 0.0;
    for (int i = 0; i < N; i++) {
        double y_fit = a * x[i] * x[i] + b * x[i] + c;
        error += pow(y[i] - y_fit, 2);
    }
    cout << "Sum of squared errors: " << error << endl;

    return 0;
}

