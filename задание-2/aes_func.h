#ifndef AES_FUNC_H
#define AES_FUNC_H

#include <iostream>
#include <string>
#include "blocks_words_bytes.h"

std::string aes_encrypt (std::string const& str, Block_128 const& key);
std::string aes_decrypt (std::string const& str, Block_128 const& key);
std::ostream & operator<< (std::ostream &out, Block_128 const& block);

#endif