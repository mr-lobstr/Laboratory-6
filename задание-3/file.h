#ifndef FILE_H
#define File_H

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <numeric>

using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

Vector compute_x (Matrix&, Vector);
std::ostream & operator<< (std::ostream&, Matrix const&);

Vector simple_iterations (Matrix const&, Vector const&, double, size_t);

#endif