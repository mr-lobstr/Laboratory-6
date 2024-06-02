#ifndef BYTE_ITERATOR_H
#define BYTE_ITERATOR_H

#include <cstdint>
#include <algorithm>

using word_t = uint32_t;
using byte_t = uint8_t;

template <class T> byte_t * byte_begin (T& obj)
{
    return reinterpret_cast<byte_t *> (&obj);
}

template <class T> byte_t const* byte_begin (T const& obj)
{
    return reinterpret_cast<byte_t const*> (&obj);
}

template <class T> auto byte_end (T& obj)
{
    return byte_begin(obj) + sizeof(T);
}

template <class T> void rot_n_bytes (T& obj, int n)
{
    std::rotate (byte_begin(obj), byte_begin(obj) + n, byte_end(obj));
}

struct Block_128
{
    Block_128 () = default;
    Block_128 (std::initializer_list<byte_t> il)
    {
        std::copy(il.begin(), il.end(), reinterpret_cast<byte_t *> (words));
    }

    byte_t * operator[] (size_t i)
    {
        return reinterpret_cast<byte_t *> (&words[i]);
    }

    byte_t const* operator[] (size_t i) const
    {
        return reinterpret_cast<byte_t const*> (&words[i]);
    }

    word_t words [4] = {};
};

#endif