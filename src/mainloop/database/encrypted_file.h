#ifndef ENCRYPTED_FILE_H
#define ENCRYPTED_FILE_H

#include "../../crypto/ciphers/cipher.h"
#include "../../crypto/ciphers/aes_ecb.h"

#include "../../crypto/hash_functions/hash_function.h"
#include "../../crypto/hash_functions/pbkdf2_hmac_sha512.h"



#include <exception>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdint>



struct parsed_encrypted_file {
  cipher* c;
  hash_function* hf;
  uint64_t data_size;
  uint32_t hash;

  uint64_t encrypted_data_size;
  char* encrypted_data;
};



parsed_encrypted_file read_encrypted_file(char* buff, uint64_t buff_size);

char* write_encrypted_file(const parsed_encrypted_file& h, size_t& buff_size);

char* read_file(const std::string& path, size_t& data_size);

void write_file(const std::string& path, size_t data_size, const char* data);



#endif