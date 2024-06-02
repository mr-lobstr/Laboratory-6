#include "file.h"
using namespace std;

double & at (Matrix& m, size_t i, size_t j)
{
    return m[i-1][j-1];
}

double & at (Vector& v, size_t i)
{
    return v[i-1];
}

double compute_u (Matrix& a, Matrix& L, Matrix& U, size_t i, size_t j)
{
    if (i == 1)
        return at(a, 1, j) / at(L, 1, 1);

    double sum = 0;

    for (size_t k = 1; k <= i-1; ++k)
    {
        sum += (at(L, i, k) * at(U, k, j));
    }

    return (at(a, i, j) - sum) / at(L, i, i);
}

double compute_l (Matrix& a, Matrix& L, Matrix& U, size_t i, size_t j)
{
    if (j == 1)
        return at(a, i, 1);

    double sum = 0;

    for (size_t k = 1; k <= j-1; ++k)
    {
        sum += (at(L, i, k) * at(U, k, j));
    }

    return at(a, i, j) - sum;
}

pair<Matrix, Matrix>
func_LU (Matrix& m)
{
    size_t n = m.size();
    Matrix l (n, Vector (n));
    Matrix u (n, Vector (n));

    for (size_t i = 1; i <= n; ++i)
    {
        for (size_t j = 1; j <= n; ++j)
        {
            if (i >= j)
                at(l, i, j) = compute_l(m, l, u, i, j);

            if (j >= i)
                at(u, i, j) = compute_u(m, l, u, i, j);

        }
    }

    return {l, u};
}

ostream & operator<< (ostream& out, Matrix const& m)
{
    cout << fixed << setprecision(3);

    for (auto& v : m)
    {
        for (auto el : v)
        {
            cout << left << setw(10) << el;
        }
        cout << endl;
    }
    
    return out;
}

Vector compute_x (Matrix& m, Vector B)
{
    auto [l, u] = func_LU(m);
    size_t n =  m.size();

    cout << "Матрица L:\n" << l << endl
         << "Матрица U:\n" << u << endl;

    Vector y (n);
    at(y, 1) = at(B, 1) / at(l, 1, 1);

    for (size_t i = 2; i <= n; ++i)
    {
        double sum = 0;

        for (size_t k = 1; k <= i-1; ++k)
        {
            sum += (at(l, i, k) * at(y, k));
        }

        at(y, i) = (at(B, i) - sum) / at(l, i, i);
    }

    Vector x (n);
    at(x, n) = at(y, n);

    for (size_t i = n - 1; i >= 1; --i)
    {
        double sum = 0;

        for (size_t k = i + 1; k <= n; ++k)
        {
            sum += (at(u, i, k) * at(x, k));
        }

        at(x, i) = at(y, i) - sum;
    }

    return x;
}