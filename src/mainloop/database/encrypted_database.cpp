#include "encrypted_database.h"

#include <filesystem>

#include "../../crypto/ciphers/aes_ecb.h"
#include "../../crypto/hash_functions/pbkdf2_hmac_sha512.h"



EncryptedDB::EncryptedDB() {}



EncryptedDB::EncryptedDB(std::string path) {
  this->open(path);
}



void EncryptedDB::open(std::string path) {
  this->path_ = path;
  if (std::filesystem::exists(this->path_)) {
    // open file

  } else {
    // create new
    // set default parameters
    this->cipher_ = new AES_ECB;
    this->hash_function_ = new pbkdf2_hmac_sha512;

  }
}



void EncryptedDB::set_cipher(cipher* c) {

}



void EncryptedDB::set_hash_function(hash_function* hf) {

}



char* EncryptedDB::write() {

}



void EncryptedDB::read(char* data) {

}



void EncryptedDB::close() {

}