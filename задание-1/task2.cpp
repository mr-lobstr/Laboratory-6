#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include "matrix_func.h"
using namespace std;

void sorted_main_diagonal(vector<vector<int>> &m, bool rev)
{
    size_t n = min(m.size(), m[0].size());
    vector<int> v(n);

    for (size_t i = 0; i < n; ++i)
    {
        v[i] = m[i][i];
    }

    sort(v.begin(), v.end());

    if (rev)
        reverse(v.begin(), v.end());

    for (size_t i = 0; i < n; ++i)
    {
        m[i][i] = v[i];
    }
}

int main()
{
    size_t M, N;
    cin >> M >> N;

    auto mtx = random_matrix(M, N, 100, 200);
    cout << mtx << endl;

    double sumRows = 0;
    for (size_t i = 1; i < M; i += 2)
    {
        sumRows += accumulate(mtx[i].begin(), mtx[i].end(), 0);
    }

    double sumColumns = 0;
    for (size_t i = 0; i < N; i += 2)
    {
        double sum = 0;
        for (size_t j = 0; j < M; ++j)
        {
            sum += mtx[j][i];
        }
        sumColumns += sum;
    }

    size_t cntRows = M / 2;
    size_t cntColumns = (N + 1) / 2;

    if (sumRows / cntRows > sumColumns / cntColumns)
    {
        cout << "больше среднее арифметическое нечётных строк" << endl;
        sorted_main_diagonal(mtx, false);
    }
    else
    {
        cout << "больше среднее арифметическое чётных столбцов" << endl;
        sorted_main_diagonal(mtx, true);
    }

    cout << mtx;
}