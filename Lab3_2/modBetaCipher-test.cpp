#include <UnitTest++/UnitTest++.h>
#include <string>
#include "modBetaCipher.h"
#include <locale>
#include <codecvt>
struct Key4_fixture {
    modBetaCipher * p;
    Key4_fixture()
    {
        p = new modBetaCipher(2);
    }
    ~Key4_fixture()
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
        std::wstring wres=modBetaCipher(5).encrypt(L"ТЕЛЕСКОП");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("СЕЛПЕОТК", res);
    }
    TEST(UselessKey) {
        CHECK_THROW(modBetaCipher tb(0), cipher_error);
    }    
    TEST(NegativeKey) {
        CHECK_THROW(modBetaCipher tb(-6), cipher_error);
    }
    TEST(LongKey) {
        std::wstring wres=modBetaCipher(10).encrypt(L"КОМПРОМИС");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("СИМОРПМОК", res);
    }

}
SUITE(encrypt)
{
    TEST_FIXTURE(Key4_fixture, UpperString) {
        std::wstring wres=p->encrypt(L"НАУШНИКИ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("АШИИНУНК", res);
    }
    TEST_FIXTURE(Key4_fixture, WhitespaceInString) {
        CHECK_THROW(p->encrypt(L"Н А У Ш Н  И КИ"), cipher_error);
    }
    TEST_FIXTURE(Key4_fixture, PunctuationInString) {
        std::wstring wres=p->encrypt(L"Н.,АУШ;:НИКИ");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL(".АШ:ИИН,У;НК", res);
    }
    TEST_FIXTURE(Key4_fixture, DigitsInString) {
        std::wstring wres=p->encrypt(L"НА12УШ72НИК45И");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("А2Ш2И4ИН1У7НК5", res);
    }
    TEST_FIXTURE(Key4_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L" "), cipher_error);
    }
}
SUITE(decrypt)
{
    TEST_FIXTURE(Key4_fixture, UpperString) {
        std::wstring wres=p->decrypt(L"АШИИНУНК");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("НАУШНИКИ", res);
    }
    TEST_FIXTURE(Key4_fixture, WhitespaceInString) {
        CHECK_THROW(p->decrypt(L"АШИ ИН УН К"), cipher_error);
    }
    TEST_FIXTURE(Key4_fixture, PunctuationInString) {
        std::wstring wres=p->decrypt(L".АШ:ИИН,У;НК");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("Н.,АУШ;:НИКИ", res);
    }
    TEST_FIXTURE(Key4_fixture, DigitsInString) {
        std::wstring wres=p->decrypt(L"А2Ш2И4ИН1У7НК5");
        std::string res = converter.to_bytes(wres);
        CHECK_EQUAL("НА12УШ72НИК45И", res);
    }
    TEST_FIXTURE(Key4_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L" "), cipher_error);
    }

}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
