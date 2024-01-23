#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cctype>
#include <locale>
#include <codecvt>
class modBetaCipher
{
private:
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
    int key1; // кол-во столбцов
public:
    modBetaCipher(std::wstring & ws_key);
    modBetaCipher()=delete; // запрет конструктора без параметров
    int getValidKey(std::wstring& ws_key);
    modBetaCipher(const int key1);
    std::wstring encrypt(const std::wstring& open_text); // зашифрование
    std::wstring decrypt(const std::wstring& cipher_text); // расшифрование
};

class cipher_error: public std::invalid_argument
{
public:
	explicit cipher_error (const std::string& what_arg):
		std::invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):
		std::invalid_argument(what_arg) {}
};
