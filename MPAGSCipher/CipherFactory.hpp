#ifndef MPAGSCIPHER_CIPHERFACTORY_HPP
#define MPAGSCIPHER_CIPHERFACTORY_HPP
// to include smart pointers
#include <memory>
#include <string>

#include "Cipher.hpp"
#include "CipherType.hpp"

/**
Constructs the Cipher depending on the requested cipher type

/param type The type of Cipher to be used
/param the key used to encrpt or Decrypt the text
/return The smart pointer to the constructed object
 */
std::unique_ptr<Cipher> cipherFactory(const CipherType type, const std::string key);

#endif
