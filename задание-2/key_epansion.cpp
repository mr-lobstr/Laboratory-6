#include <vector>
#include "sbox.h"
#include "blocks_words_bytes.h"
using namespace std;

word_t rCon (int round)
{
    word_t w = 0;
    byte_begin(w)[3] = (round == 10) ? 0x36 :
                       (round == 9)  ? 0x1b :
                       1 << (round -1 );
    return w;
}

word_t rotWord (word_t w)
{
    rot_n_bytes(w, 3);
    return w;
}

word_t subWord(word_t w)
{
    transform (byte_begin(w), byte_end(w), byte_begin(w), sBox);
    return w;
}

vector<Block_128> key_expansion (const Block_128& ikey, int Np, int Nk)
{   

    size_t wordsCnt = (Np + 1) * Nk;
    vector<Block_128> keys(Np + 1);
    keys[0] = ikey;

    auto get_word = [&keys, Nk] (size_t i) -> word_t &
    {
        return keys[i / Nk].words[i % Nk];
    };

    for (size_t i = Nk; i < wordsCnt; ++i)
    {
        auto temp = (i % Nk != 0)
                        ? get_word(i - 1)
                        : subWord(rotWord(get_word(i - 1))) ^ rCon(i / Nk);

        get_word(i) = temp ^ get_word(i - Nk);
    }

    return keys;
}