#ifndef MPAGSCIPHER_CIPHER_HPP
#define MPAGSCIPHER_CIPHER_HPP

// standard include package
#include <string>


#include "CipherMode.hpp"
/**
 * \file Cipher.hpp
 * \brief Contains the declartion of applyCipher to be publically inheirited by other  all the ciphers
 */

/**
 * \class Cipher
 * \brief Dynamic declaration of applyCipher to be shared between ciphers
 */


class Cipher {

public: 
  Cipher() = default;
  Cipher(const Cipher& rhs) = default;
  Cipher(Cipher&& rhs) = default;
  Cipher& operator=(const Cipher& rhs) = default;
  Cipher& operator=(Cipher&& rhs) = default;
  
  virtual ~Cipher() = default;
  

  /**
   * Apply the cipher to the provided text
   *
   * \param inputText the text to encrypt or decrypt
   * \param cipherMode whether to encrypt or decrypt the input text
   * \return the result of applying the cipher to the input text
   */

  virtual std::string applyCipher(const std::string& input, const CipherMode cipherMode) const =0;


};

#endif
