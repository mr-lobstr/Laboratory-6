#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

using Koord = pair<size_t, size_t>;

bool find_word(vector<string> const& m, Koord k, string const& s, set<Koord> st)
{
    auto [i, j] = k;
    if (i < 0 or j < 0 or i >= m.size() or j >= m[0].size())
        return false;

    if (st.count({i, j})) return false;
    if (s == "")          return true;
    if (s[0] != m[i][j])  return false;
    
    auto newStr = s.substr(1, s.size() - 1);
    st.insert({i, j});

    return find_word(m, {i-1, j}, newStr, st)
        or find_word(m, {i+1, j}, newStr, st)
        or find_word(m, {i, j-1}, newStr, st)
        or find_word(m, {i, j+1}, newStr, st);
}

bool f (vector<string> const& m, string const& s)
{
    for (size_t i = 0; i < m.size(); ++i)
    {
        for (size_t j = 0; j < m[0].size(); ++j)
        {
            if (find_word(m, {i, j}, s, {}))
                return true;
        }
    }
    
    return false;
}

int main()
{
    vector<string> mtx = 
    {
        "QWERH",
        "JSPES",
        "SFRSF",
        "ADOGS",
        "SSGFI"
    };

    cout << (f(mtx, "JSPROGS") ? "true" : "false") << endl;
}