#include "modBetaCipher.h"
using namespace std;

modBetaCipher::modBetaCipher(int key1) :
    key1(key1)
{
    if (key1 < 2) {
        throw(cipher_error("Invalid key"));
    }
}

std::wstring modBetaCipher::encrypt(const std::wstring& open_text) // шифрование
{
    
    if (open_text.empty()) {
        throw(cipher_error("Ciphertext should not be empty"));
    }
    if (open_text.find(' ') != std::wstring::npos) {
        throw(cipher_error("Ciphertext should not contain spaces"));
    }
    
    wstring tabl = open_text;
    int dl, nstrok, index, x;
    dl = open_text.length(); // введенный текст
    nstrok = (dl - 1) / key1 + 1; // кол-во столбцов
    x = 0;
    for (int i = key1; i > 0; i--) { // столбцы
        for (int j = 0; j < nstrok; j++) { // строки
            index = i+key1*j;
            if (index-1 < dl) {
                tabl[x] = open_text[index-1];
                x++;
            }
        }
    }
    return tabl;
}

std::wstring modBetaCipher::decrypt(const std::wstring& cipher_text) // расшифрование
{

	if (cipher_text.empty()) {
        throw(cipher_error("Plaintext should not be empty"));
    }
    if (cipher_text.find(' ') != std::wstring::npos) {
        throw(cipher_error("Plaintext should not contain spaces"));
    }

    wstring tabl = cipher_text;
    int dl, nstrok, index, x;
    dl = cipher_text.length();
    nstrok = (dl - 1) / key1 + 1; // кол-во столбцов
    x = 0;
    for (int i = key1; i > 0; i--) { // столбцы
        for (int j = 0; j < nstrok; j++) { // строки
            index = i+key1*j;
            if (index-1 < dl) {
                tabl[index-1] = cipher_text[x];
                x++;
            }
        }
    }
    return tabl;
}
