//! Unit Tests for MPAGSCipher VigenereCioher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "VigenereCipher.hpp"

TEST_CASE("Vigenere Cipher encryption", "[vigenere]") {
  VigenereCipher cc{"KEY"};
  REQUIRE( cc.applyCipher("HELLOWORLD", CipherMode::Encrypt) == "RIJVSUYVJN");
}

TEST_CASE("Playfair Cipher decryption", "[vigenere]") {
  VigenereCipher cc{"KEY"};
  REQUIRE( cc.applyCipher("RIJVSUYVJN", CipherMode::Decrypt) == "HELLOWORLD");
}
