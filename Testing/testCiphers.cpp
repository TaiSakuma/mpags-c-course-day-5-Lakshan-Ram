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

TEST_CASE("All Cipher encrytion", "[encryption]") {

  std::vector<std::unique_ptr<Cipher>> ciphercollect = {};
  ciphercollect.push_back(cipherFactory(CipherType::Caesar, "10"));
  ciphercollect.push_back(cipherFactory(CipherType::Playfair, "hello"));
  ciphercollect.push_back(cipherFactory(CipherType::Vigenere, "KEY"));

  std::vector<std::string> puretext = {"HELLOWORLD", "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING", "HELLOWORLD"};
  std::vector<std::string> encrypttext = {"ROVVYGYBVN", "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA", "RIJVSUYVJN"};

  for (size_t i = 0; i < ciphercollect.size(); ++ i) {
    REQUIRE( testCipher(*ciphercollect[i], CipherMode::Encrypt, puretext[i], encrypttext[i] ));
  }
}

TEST_CASE("Caesar Cipher decryption", "[caesar]") {
  CaesarCipher cc{10};
  REQUIRE( testCipher(cc, CipherMode::Decrypt, "ROVVYGYBVN", "HELLOWORLD"));
}


TEST_CASE("Playfair Cipher decryption", "[playfair]") {
  PlayfairCipher cc{"hello"};
  REQUIRE( testCipher(cc, CipherMode::Decrypt, "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA", "BOBISXSOMESORTOFIUNIORCOMPLEXQXENOPHONEONEZEROTHINGZ"));
}

TEST_CASE("Vigenere Cipher decryption", "[vigenere]") {
  VigenereCipher cc{"KEY"};
  REQUIRE(testCipher(cc, CipherMode::Decrypt,"RIJVSUYVJN", "HELLOWORLD"));
}

