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

    TableAlphabet alphabet(66);
    
    for (size_t i = 0; i < 33; i++)
    {
        alphabet.table[i] = L'А' + i;  
        alphabet.table[i + 33] = L'а' + i;
    }

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


    while (true)
    {
        std::wcout << "A - affine, V - vigenere\n";
        
        std::wcin.getline(str, 1024);
        

        switch (str[0])
        {
            case L'A':
            {       
                std::wcout << "please enter some text\n";

                //std::wcin.ignore();
                std::wcin.getline(str, 1024);
                input.size = wcslen(str);
               // std::wcin.ignore();

                Buffer encrypted = affine.encrypt(input, 19, 7);
                std::wcout.write(encrypted.data, encrypted.size);
                std::wcout << "\n";

                Buffer decrypted = affine.decrypt(encrypted, 19, 7);
                std::wcout.write(decrypted.data, decrypted.size);
                std::wcout << "\n";
                break;
            }
            case 'V':
            {
                std::wcout << "please enter a key\n";

                //std::wcin.ignore();
                std::wcin.getline(keystr, 1024);
                key.size = wcslen(keystr);
               // std::wcin.ignore();

                std::wcout << "please enter some text\n";

                std::wcin.getline(str, 1024);
                input.size = wcslen(str);

                Buffer encrypted = vigenere.encrypt(input, key);
                std::wcout.write(encrypted.data, encrypted.size);
                std::wcout << "\n";

                Buffer decrypted = vigenere.decrypt(encrypted, key);
                std::wcout.write(decrypted.data, decrypted.size);
                std::wcout << "\n";
                break;
            }
        }

    }


}