#ifndef MATRIX_FUNC_H
#define MATRIX_FUNC_H

#include <vector>
#include <iostream>
#include <iomanip>

template <class T>
std::ostream & operator<< (std::ostream& out, std::vector<std::vector<T>> const& m)
{
    for (auto const& v : m)
    {
        for (auto el : v)
        {
            out << std::setw(5) << std::left << el;
        }
        out << std::endl;
    }

    return out;
}

template <class T>
std::vector<std::vector<T>>
random_matrix (size_t M, size_t N, T minV, T maxV)
{
    std::vector<std::vector<T>> m(M, std::vector<T>(N));

    for (auto& v : m)
    {
        for (auto& el : v)
        {
            el = minV + (rand() % (maxV - minV));
        }
    }

    return m;
}

#endif