#include <vector>
#include "sbox.h"
#include "aes_func.h"
using namespace std;

vector<Block_128> key_expansion (const Block_128& ikey, int Np, int Nk);

// ------------------------------ для Block_128 ------------------------------
ostream & operator<<(ostream &out, Block_128 const& block)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            out << hex << (int) block[i][j] << " ";
        }
        out << endl;
    }

    return out;
}


pair<vector<Block_128>, size_t>
string_to_blocks (const string& s)
{
    vector<Block_128> blocks (s.size() / 16);
    auto it = s.begin();

    for (auto& block : blocks)
    {
        copy(it, it + 16, byte_begin(block));
        it += 16;
    }

    blocks.push_back({});
    copy(it, s.end(), byte_begin(blocks.back()));

    return { blocks, 16 - (s.size() % 16) };
}


string blocks_to_string (vector<Block_128> const& blocks)
{
    string res;
    for (auto const& block : blocks)
    {
        copy(byte_begin(block), byte_end(block), back_inserter(res));
    }

    return res;
}


// ------------------------------ общие функции ------------------------------
byte_t powX_GF (byte_t a, int n)
{
    while (n--)
    {
        byte_t highBit = a & 0x80;
        byte_t shl = (a << 1) & 0xff;
        a = (highBit == 0) ? shl : shl ^ 0x1b;
    }
    return a;
}

byte_t mul_GF (byte_t a, byte_t b)
{
    word_t res = 0, pwr = 0;

    for (; b > 0; b /= 2, ++pwr)
    {
        if (b % 2 == 1)
            res ^= powX_GF(a, pwr);
    }

    return res;
}

void mul_by_column (Block_128& block, Block_128& mtx, size_t n)
{
    byte_t temp[4] = {};
    
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            temp[i] ^= mul_GF(mtx[i][j], block[j][n]);
        }
    }

    for (size_t i = 0; i < 4; ++i)
    {
        block[i][n] = temp[i];
    }
}


void mix_columns (Block_128& block, Block_128& mtx)
{
    for (size_t i = 0; i < 4; ++i)
    {
        mul_by_column (block, mtx, i);
    }
}


void add_round_key (Block_128& block, const Block_128& key)
{
    transform (byte_begin(block), byte_end(block), byte_begin(key), byte_begin(block), bit_xor<>{});   
}


// ------------------------------ зашифровка ------------------------------
void sub_bytes (Block_128& block)
{
    transform (byte_begin(block), byte_end(block), byte_begin(block), sBox);
}


void shift_rows (Block_128& block)
{
    rot_n_bytes(block.words[1], 3);
    rot_n_bytes(block.words[2], 2);
    rot_n_bytes(block.words[3], 1);
}


void encrypt_block (Block_128& block, vector<Block_128> const& keys)
{
    Block_128 mtx = {
        0x02, 0x03, 0x01, 0x01,
        0x01, 0x02, 0x03, 0x01,
        0x01, 0x01, 0x02, 0x03,
        0x03, 0x01, 0x01, 0x02
    };
    
    add_round_key(block, keys[0]);

    for (size_t i = 1; i <= 10 - 1; ++i)
    {
        sub_bytes(block);
        shift_rows(block);
        mix_columns(block, mtx);
        add_round_key(block, keys[i]);
    }

    sub_bytes(block);
    shift_rows(block);
    add_round_key(block, keys[10]);
}


string aes_encrypt (string const& str, Block_128 const& key)
{
    auto [blocks, cnt] = string_to_blocks(str);
    vector<Block_128> keys = key_expansion(key, 10, 4);

    cout << "Промежуточные ключи:" << endl;
    for (auto const& k : keys)
    {
        cout << k << endl;
    }

    for (auto& block : blocks)
    {
        encrypt_block(block, keys);
    }

    return blocks_to_string(blocks);
}


// ------------------------------ расшифровка ------------------------------
void inv_sub_bytes (Block_128& block)
{
    transform (byte_begin(block), byte_end(block), byte_begin(block), inv_sBox);
}


void inv_shift_rows (Block_128& block)
{
    rot_n_bytes(block.words[1], 1);
    rot_n_bytes(block.words[2], 2);
    rot_n_bytes(block.words[3], 3);
}


void decrypt_block (Block_128& block, vector<Block_128> const& keys)
{
    Block_128 mtx = {
        0x0e, 0x0b, 0x0d, 0x09,
        0x09, 0x0e, 0x0b, 0x0d,
        0x0d, 0x09, 0x0e, 0x0b,
        0x0b, 0x0d, 0x09, 0x0e,
    };

    add_round_key(block, keys[10]);
    inv_shift_rows(block);
    inv_sub_bytes(block);
    
    for (size_t i = 10-1; i >= 1; --i)
    {
        add_round_key(block, keys[i]);
        mix_columns(block, mtx);
        inv_sub_bytes(block);
        inv_shift_rows(block);
    }

    add_round_key(block, keys[0]);
}


string aes_decrypt (string const& str, Block_128 const& key)
{
    auto [blocks, cnt]  = string_to_blocks(str);
    vector<Block_128> keys = key_expansion(key, 10, 4);

    for (auto& block : blocks)
    {
        decrypt_block(block, keys);
    }

    auto s = blocks_to_string(blocks);
    s.erase(s.end() - cnt, s.end());

    return s;
}