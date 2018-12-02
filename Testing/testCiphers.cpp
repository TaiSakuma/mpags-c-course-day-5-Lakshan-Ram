//! Unit Tests for MPAGSCipher CaesarCipher Class
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <string>
#include <vector>
#include <memory>

#include "CaesarCipher.hpp"
#include "PlayfairCipher.hpp"
#include "VigenereCipher.hpp"
#include "Cipher.hpp"
#include "CipherFactory.hpp"
#include "CipherMode.hpp"
#include "CipherType.hpp"

bool testCipher(const Cipher& cipher, const CipherMode mode, const std::string inputText, const std::string outputText)
{

  std::string outtext = cipher.applyCipher(inputText, mode);
  return (outtext == outputText);
    
}


std::vector<std::unique_ptr<Cipher>> ciphercollect = {};

ciphercollect.push_back(cipherFactory(CipherType::Caesar, 10));
ciphercollect.push_back(cipherFactory(CipherType::Playfair, "hello"));
ciphercollect.push_back(cipherFactory(CipherType::Vigenere, "KEY"));

std::vector<std::string> puretext = {"HELLOWORLD", "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING", "HELLOWORLD"};
std::vector<std::string> encrypttext = "ROVVYGYBVN", "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA", "RIJVSUYVJN"};


TEST_CASE("All Cipher encrytion", "[encryption]") {
  size_t i =0;
  for (const auto& c : ciphercollect) {
    REQUIRE (ciphercollect->applyCiphers(puretext[i],CipherMode::Encrypt) == encrypttext[i]);
    ++i;
  }
}


TEST_CASE("All Ciphers decrytion", "[decryption]") {
  size_t i =0;
  for (const auto& c : ciphercollect) {
    REQUIRE (ciphercollect->applyCiphers(encrypttext[i],CipherMode::Decrypt) == puretext[i]);
    ++i;
  }
}


TEST_CASE("Caesar Cipher encryption", "[caesar]") {
  CaesarCipher cc{10};
  REQUIRE( testCipher(cc,CipherMode::Encrypt, "HELLOWORLD", "ROVVYGYBVN"));
}

TEST_CASE("Caesar Cipher decryption", "[caesar]") {
  CaesarCipher cc{10};
  REQUIRE( testCipher(cc, CipherMode::Decrypt, "ROVVYGYBVN", "HELLOWORLD"));
}


TEST_CASE("Playfair Cipher encryption", "[playfair]") {
  PlayfairCipher cc{"hello"};
  REQUIRE( testCipher(cc, CipherMode::Encrypt, "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING",  "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA"));
}

TEST_CASE("Playfair Cipher decryption", "[playfair]") {
  PlayfairCipher cc{"hello"};
  REQUIRE( testCipher(cc, CipherMode::Decrypt, "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA", "BOBISXSOMESORTOFIUNIORCOMPLEXQXENOPHONEONEZEROTHINGZ"));
}


TEST_CASE("Vigenere Cipher encryption", "[vigenere]") {
  VigenereCipher cc{"KEY"};
  REQUIRE( testCipher(cc,CipherMode::Encrypt, "HELLOWORLD", "RIJVSUYVJN"));
}

TEST_CASE("Vigenere Cipher decryption", "[vigenere]") {
  VigenereCipher cc{"KEY"};
  REQUIRE(testCipher(cc, CipherMode::Decrypt,"RIJVSUYVJN", "HELLOWORLD"));
}

