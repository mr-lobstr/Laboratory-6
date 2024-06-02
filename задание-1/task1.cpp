#include <iostream>
#include <vector>
#include <string>
#include "matrix_func.h"
using namespace std;

auto max_sequence (vector<int> const& v)
{
    auto beg = v.begin();
    auto it = beg;
    auto rangeMax = make_pair(beg, beg);

    while (++it != v.end())
    {
        if (*it > *prev(it))
            continue;

        auto [fst, snd] = rangeMax;
        if (it - beg > snd - fst)
        {
            rangeMax = {beg, it};
        }

        beg = it;
    }

    auto [fst, snd] = rangeMax;
    if (it - beg > snd - fst)
        return make_pair(beg, it);

    return rangeMax;
}

int main()
{
    size_t M, N;
    cin >> M >> N;

    auto mtx = random_matrix(M, N, -50, 50);
    cout << mtx << endl;

    auto [b, e] = max_sequence(mtx[0]);
    for (auto const& v : mtx)
    {
        auto [fst, snd] = max_sequence(v);
        if (snd - fst > e - b)
        {
            b = fst;
            e = snd;
        }
    }

    vector<int> vi (b, e);
    for (auto el : vi)
    {
        cout << el << " ";
    }
}