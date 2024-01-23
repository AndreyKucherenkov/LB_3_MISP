#include <UnitTest++/UnitTest++.h>
#include <string>
#include "modBetaCipher.h"
#include <locale>
#include <codecvt>

struct KeyB_fixture {
    modBetaCipher * p;
    KeyB_fixture()
    {
        p = new modBetaCipher(L"В");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};
//setup converter
using convert_type = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_type, wchar_t> converter;

SUITE(Costructor)
{

    TEST(NormalKey) {
        std::wstring wres=modBetaCipher(L"РАЗ").encrypt(L"РОЗА");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("РАЗР", res);	
    }
    TEST(LowerlKey) {
        std::wstring wres=modBetaCipher(L"один").encrypt(L"ПИЖАМА");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ОДИНОД", res);
    }
    TEST(LongKey) {
        std::wstring wres=modBetaCipher(L"ОПЕРАТОР").encrypt(L"СМС");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("ОПЕ", res);
    }

    TEST(DigitsInKey) {
        CHECK_THROW(modBetaCipher cp(L"4"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modBetaCipher cp(L"П.п"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modBetaCipher cp(L"ПРО ВЕРКА"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modBetaCipher cp(L""),cipher_error);
    }
}
SUITE(encrypt)
{
    TEST_FIXTURE(KeyB_fixture, UpperString) {
        std::wstring wres=p->encrypt(L"ПРОБЕЛ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АААААА", res);
    }
    TEST_FIXTURE(KeyB_fixture, LowerString) {
        std::wstring wres=p->encrypt(L"ПРОбел");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АААБЁМ", res);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceInString) {
        CHECK_THROW(p->encrypt(L"ПРО БЕЛ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctuationInString) {
        CHECK_THROW(p->encrypt(L"ПРО.,.БЕЛ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsInString) {
        CHECK_THROW(p->encrypt(L"ПРО567БЕЛ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, Digits) {
        CHECK_THROW(p->encrypt(L"777"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }
}
SUITE(decrypt)
{
    TEST_FIXTURE(KeyB_fixture, UpperString) {
        std::wstring wres=p->decrypt(L"ОДПДУП");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АААААА", res);
    }
    TEST_FIXTURE(KeyB_fixture, LowerString) {
        std::wstring wres=p->decrypt(L"ПРЛпоаПРЛ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АААРПАААА", res);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceInString) {
        CHECK_THROW(p->decrypt(L"ПР ПА А"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctuationInString) {
        CHECK_THROW(p->decrypt(L"ПКП,ПКП,.П"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsInString) {
        CHECK_THROW(p->decrypt(L"П4ДДД89Л"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
