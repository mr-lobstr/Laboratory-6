#include <iostream>
#include <fstream>
#include <string>
#include "aes_func.h"
using namespace std;

Block_128 random_key ()
{
    Block_128 key;

    for (auto it = byte_begin(key); it != byte_end(key); ++it)
    {
        *it = rand() % 256;
    }

    return key;
}

string file_to_string (const string& name)
{
	string res, s;
	ifstream in (name);

	while (getline(in, s))
	{
		res += (s + "\n");
	}

	in.close();
	return res;
}

int main()
{
    Block_128 masterKey = random_key();
    cout << "Основной ключ:" << endl
         << masterKey << endl;

    string text = file_to_string("text.txt"); 
    string textEncrypt = aes_encrypt(text, masterKey);

    ofstream encrypt ("encrypt.txt");
    encrypt << textEncrypt;
    encrypt.close();

    textEncrypt = file_to_string("encrypt.txt");
    string textDecrypt = aes_decrypt(textEncrypt, masterKey);

    ofstream decrypt ("decrypt.txt");
    decrypt << textDecrypt;
    decrypt.close();
}