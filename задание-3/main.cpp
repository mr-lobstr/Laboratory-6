#include "file.h"
using namespace std;

int main()
{
    system("chcp 65001");

    Matrix A =
    {
        {-1.21, -0.04, 0.21, -0.18},
        { 0.25, -1.23,  0.2, -0.09},
        {-0.21,   0.2,  0.8, -0.13},
        { 0.15, -1.31, 0.06,  0.88}
    };

    Vector b = {-1.24, 0.88, 2.56, 0.1};

    cout << "Метод LU-разложения: " << endl << endl;
    Vector x = compute_x(A, b);
    cout << fixed << setprecision(3)
         << "x1 = " << x[0] << endl
         << "x2 = " << x[1] << endl
         << "x3 = " << x[2] << endl
         << "x4 = " << x[3] << endl
         << endl;


    x = simple_iterations(A, b, 0.01, 10);
    cout << fixed << setprecision(3)
         << endl
         << "x1 = " << x[0] << endl
         << "x2 = " << x[1] << endl
         << "x3 = " << x[2] << endl
         << "x4 = " << x[3] << endl;
} 