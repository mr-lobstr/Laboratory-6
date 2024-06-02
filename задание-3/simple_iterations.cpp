#include "file.h"
using namespace std;

double matrix_norm (Matrix const& m)
{
    double mx = 0;
    auto absAdd = [] (double prev, double d) { return prev + fabs(d); };

    for (auto const& v : m)
    {
        double absSum = accumulate(v.begin(), v.end(), 0, absAdd);
        mx = max(mx, absSum);
    }

    return mx;
}

double max_diff (Vector const& v, Vector const& v2)
{
    double mx = 0;

    for (size_t i = 0; i < v.size(); ++i)
    {
        mx = max(mx, fabs(v[i] - v2[i]));
    }

    return mx;
}

Vector operator* (Matrix const& m, Vector const& v)
{
    Vector res (v.size(), 0);

    for (size_t i = 0; i < m.size(); ++i)
    {
        for (size_t j = 0; j < m.size(); ++j)
        {
            res[i] += m[i][j] * v[j];
        }
    } 

    return res;
}

Vector operator+ (Vector v, Vector const& v2)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        v[i] += v2[i];
    }

    return v;
}

pair<Matrix, Vector>
canonical (Matrix const& A, Vector const& b)
{
    size_t n = A.size();
    Matrix C (n, Vector (n));
    Vector f (n);

    for (size_t i = 0; i < n; ++i)
    {
        f[i] = b[i] / A[i][i];

        for (size_t j = 0; j < n; ++j)
        {
            C[i][j] = (i != j)
                        ? -A[i][j] / A[i][i]
                        : 0;
        }
    }

    return {C, f};
}

Vector simple_iterations (Matrix const& A, Vector const& b, double eps, size_t maxIters)
{
    Vector x (A.size(), 0);
    auto [C, f] = canonical(A, b);

    cout << "Метод простых итераций ("
         << (matrix_norm(C) > 1 ? "не " : "") << "сходится): "
         << endl;
    
    static auto titles = {"N", "x1", "x2", "x3", "x4", "eps"};
    copy(titles.begin(), titles.end(), ostream_iterator<string> (cout, "\t"));
    cout << endl;

    for (size_t k = 0; k < maxIters; ++k)
    {   
        Vector nextX = C * x + f;
        double maxDiff = max_diff(nextX, x);

        x = nextX;

        if (maxDiff < eps)
            break;

        cout << fixed << setprecision(3) << (k + 1) << "\t";
        copy(x.begin(), x.end(), ostream_iterator<double> (cout, "\t"));
        cout << maxDiff << endl;
    }

    return x;
}