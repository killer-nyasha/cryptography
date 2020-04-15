#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "Affine.h"
#include "Vigenere.h"

int wmain()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    TableAlphabet alphabet(33);
    
    for (size_t i = 0; i < alphabet.length(); i++)
        //alphabet.table[i] = 'a' + i;
        alphabet.table[i] = L'а' + i;

    alphabet.makeReverseTable();

    AffineEncryptor<TableAlphabet> affine(alphabet);
    VigenereEncryptor<TableAlphabet> vigenere(alphabet);

    wchar_t* keystr = new wchar_t[1024];
    wchar_t* str = new wchar_t[1024];

    Buffer input;
    input.data = str;
    input.size = 0;

    Buffer key;
    key.data = keystr;
    key.size = 0;


    std::wcin.getline(keystr, 1024);
    key.size = wcslen(keystr);

    while (true)
    {
        std::wcin.getline(str, 1024);
        input.size = wcslen(str);

        Buffer encrypted = vigenere.encrypt(input, key);
        std::wcout << encrypted.data << "\n";

        Buffer decrypted = vigenere.decrypt(encrypted, key);
        std::wcout << decrypted.data << "\n";
    }

    //while (true)
    //{
    //    std::wcin.getline(str, 1024);
    //    input.size = wcslen(str);

    //    Buffer encrypted = affine.encrypt(input, 19, 7);
    //    std::wcout << encrypted.data << "\n";

    //    Buffer decrypted = affine.decrypt(encrypted, 19, 7);
    //    std::wcout << decrypted.data << "\n";
    //}


}