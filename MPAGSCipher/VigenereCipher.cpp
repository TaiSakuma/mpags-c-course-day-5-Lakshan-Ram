// Standard library includes
#include <string>
#include <algorithm>
#include <iostream>

// Out project headers
#include "Alphabet.hpp"
#include "VigenereCipher.hpp"

VigenereCipher::VigenereCipher( const std::string& key)
{
  // Set the given key
  setKey(key);
}

void VigenereCipher::setKey( const std::string& key )
{
  key_ = key;
  // Make sure the key is uppercase
  
  // Make sure the key is upper case
  std::transform( std::begin(key_), std::end(key_), std::begin(key_), ::toupper );

  // Remove non-alphabet characters
  key_.erase( std::remove_if( std::begin(key_), std::end(key_), [](char c){ return !std::isalpha(c); } ),
              std::end(key_) );

  // Check if the key is empty and 
  // replace with default if so
  if (key_.empty())
    { std::cout<<"No key given, key chosen to be DEFAULTFRAGON"<<std::endl;
      key_ = "DEFAULTDRAGON"; // Default Key
    }
  
  // loop over the key
     // Find the letter position in the alphabet
     // Create a CaesarCipher using this position as a key
     // Insert a std::pair of the letter and CaesarCipher into the lookup

  size_t letterpos{};
  for (size_t i=0; i<key_.size(); ++i)
    {
      letterpos = Alphabet::alphabet.find(key_[i]);
      
      CaesarCipher cipher{letterpos};
      
      auto p1 {std::make_pair(key_[i], cipher)};
      
      charLookup_.insert(p1);
            
    }
      

};


std::string VigenereCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
  std::string outputText{};
  // For each letter in input:
  for (size_t i=0; i<inputText.size();++i)
    {
      // Find the corresponding letter in the key,       
      // repeating/truncating as required
      
      char keyletter = key_[i%(key_.size())];
      
      // Find the Caesar cipher from the lookup      
      auto iter = charLookup_.find(keyletter);
      CaesarCipher cipher = (*iter).second;
      // Run the (de)encryption
      // Add the result to the output
      outputText+= cipher.applyCipher(std::string{inputText[i]}, cipherMode);

    }
  return outputText;;
};
