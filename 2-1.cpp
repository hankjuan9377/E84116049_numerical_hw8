#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int degree = 2;     // 多?式次?
const int n_points = 1000; // ?分分段?量

double a = -1.0, b = 1.0;

// 原函? f(x)
double f(double x) {
    return 0.5 * cos(x) + 0.25 * sin(2 * x);
}

// 基函? phi_i(x) = x^i
double phi(int i, double x) {
    return pow(x, i);
}

// 梯形?分法
double integrate_f_phi(int i) {
    double h = (b - a) / n_points;
    double sum = 0.5 * (f(a) * phi(i, a) + f(b) * phi(i, b));
    for (int k = 1; k < n_points; ++k) {
        double x = a + k * h;
        sum += f(x) * phi(i, x);
    }
    return h * sum;
}

// 梯形?分法用于基函??? <phi_i, phi_j>
double integrate_phi_phi(int i, int j) {
    double h = (b - a) / n_points;
    double sum = 0.5 * (phi(i, a) * phi(j, a) + phi(i, b) * phi(j, b));
    for (int k = 1; k < n_points; ++k) {
        double x = a + k * h;
        sum += phi(i, x) * phi(j, x);
    }
    return h * sum;
}

// 高斯消元法解?性方程? A * c = b
vector<double> gaussian_elimination(vector<vector<double> > A, vector<double> b) {
    int n = b.size();
    for (int i = 0; i < n; ++i) {
        // 主元?一
        double pivot = A[i][i];
        for (int j = 0; j < n; ++j) A[i][j] /= pivot;
        b[i] /= pivot;

        // 消元
        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = A[k][i];
            for (int j = 0; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }
    return b; // 此? b 即?解向量 c
}

int main() {
    vector<vector<double> > A(degree + 1, vector<double>(degree + 1));
    vector<double> B(degree + 1);

    // 构造 A 和 B
    for (int i = 0; i <= degree; ++i) {
        B[i] = integrate_f_phi(i);
        for (int j = 0; j <= degree; ++j) {
            A[i][j] = integrate_phi_phi(i, j);
        }
    }

    // 解方程 A * c = B
    vector<double> c = gaussian_elimination(A, B);

    // ?出?合多?式系?
    cout << "Least squares polynomial approximation (degree " << degree << "):" << endl;
    cout << "P(x) = ";
    for (int i = 0; i <= degree; ++i) {
        cout << c[i];
        if (i >= 1) cout << "*x";
        if (i > 1) cout << "^" << i;
        if (i < degree) cout << " + ";
    }
    cout << endl;

    return 0;
}

