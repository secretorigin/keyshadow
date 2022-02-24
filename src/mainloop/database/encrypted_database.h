#ifndef ENCRYPTED_DATABASE_H
#define ENCRYPTED_DATABASE_H

#include "../../crypto/ciphers/cipher.h"
#include "../../crypto/hash_functions/hash_function.h"

#include <fstream>
#include <string>



class EncryptedDB {
public:
  EncryptedDB();
  EncryptedDB(std::string path);

  void open(std::string path);

  void set_cipher(cipher* c);
  void set_hash_function(hash_function* hf);
  char* write();
  
  void read(char* data);

  void close();

private:
  cipher* cipher_;
  hash_function* hash_function_;
  uint64_t data_size_;
  uint32_t hash_;
  char* data_;

  std::string path_;

  std::fstream fs_;
};



#endif