// Standard library includes
#include <string>
#include <iostream>
#include <algorithm>

// Out project headers
#include "Alphabet.hpp"
#include "VigenereCipher.hpp"

VigenereCipher::VigenereCipher ( const std::string& key )
{
  // Set the given key
  setKey(key);
}

void VigenereCipher::setKey( const std::string& key )
{
    // Store the key
    key_ = key;
    
    // Make sure the key is upper case
    std::transform( std::begin(key_), std::end(key_), std::begin(key_), ::toupper );

    // Remove non-alphabet characters
    key_.erase( std::remove_if( std::begin(key_), std::end(key_), [](char c){ return !std::isalpha(c); } ),
              std::end(key_) );

    // Check if the key is empty and replace with default if so
    if ( key_.empty() ) {
        key_ = defaultKey_;
    }

    // Loop over the key
    for ( const auto& elem : key_ ) {
        // Find the letter position in the alphabet
        std::size_t letterPosInAlpha = Alphabet::alphabet.find( elem );
      
        // Create a CaesarCipher using this position as key
        CaesarCipher cipher { letterPosInAlpha };

        // Insert a std::pair of the letter and CaesarCipher into the lookup
        charLookup_.insert( std::make_pair( elem, cipher) );
    }
}

std::string VigenereCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
  std::string outputText{""};

  std::size_t initialKey = 0;
  CaesarCipher cipher{initialKey};
  std::string inputToCipher{""};

  // For each letter in input:
  for ( std::string::size_type it = 0; it < inputText.size(); it++ ) {
    // Find the corresponding letter in the key
    char keyLetter = key_[it % key_.size()];
    // repeating/truncating as required
    
    // Find the CaesarCipher object from the lookup
    cipher = charLookup_.at( keyLetter );

    // Run the de(encryption)
    inputToCipher.clear();
    inputToCipher.push_back(inputText[it]);
    outputText += cipher.applyCipher( inputToCipher, cipherMode );

    // Add the result to the output
  }
  return outputText;
}