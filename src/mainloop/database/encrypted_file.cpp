#include "encrypted_file.h"

#include "../../crypto/ciphers/cipher.h"
#include "../../crypto/ciphers/aes_ecb.h"

#include "../../crypto/hash_functions/hash_function.h"
#include "../../crypto/hash_functions/pbkdf2_hmac_sha512.h"



#include <exception>
#include <fstream>
#include <string>
#include <cstring>



parsed_header read_header(char* buff, uint64_t buff_size) {
  parsed_header h;
  size_t padding = 0;

  char cipher_name[CIPHER_STD_SIZE];
  memcpy(cipher_name, buff, CIPHER_STD_SIZE);
  padding += CIPHER_STD_SIZE;
  if (memcmp(cipher_name, AES_ECB_STD, CIPHER_STD_SIZE) == 0)
    h.c = new aes_ecb;
  else
    throw std::invalid_argument("Unknown cipher '" + std::string(cipher_name) + "'.");

  h.c->read(buff + padding);
  padding += h.c->header_size();

  char hash_function_name[HASH_FUNCTION_STD_SIZE];
  memcpy(hash_function_name, buff + padding, HASH_FUNCTION_STD_SIZE);
  padding += HASH_FUNCTION_STD_SIZE;
  if (memcmp(hash_function_name, PBKDF2_HMAC_SHA512_STD, HASH_FUNCTION_STD_SIZE) == 0)
    h.hf = new pbkdf2_hmac_sha512;  
  else
    throw std::invalid_argument("Unknown hash function '" + std::string(hash_function_name) + "'.");
  
  h.hf->read(buff + padding);
  padding += h.hf->header_size();

  memcpy(&h.data_size, buff + padding, sizeof(h.data_size));
  padding += sizeof(h.data_size);

  memcpy(&h.hash, buff + padding, sizeof(h.hash));
  padding += sizeof(h.hash);

  h.encrypted_data_size = buff_size - padding;
  if (h.encrypted_data_size != 0) {
    h.encrypted_data = new char[h.encrypted_data_size];
    memcpy(h.encrypted_data, buff + padding, h.encrypted_data_size);
  }

  return h;
}



char* write_header(const parsed_header& h, size_t& buff_size) {
  size_t padding = 0;
  
  buff_size = 28 + h.encrypted_data_size + h.c->header_size() + h.hf->header_size();
  char* buff = new char[buff_size];

  memcpy(buff, h.c->get_name(), CIPHER_STD_SIZE);
  padding += CIPHER_STD_SIZE;

  h.c->write(buff + padding);
  padding += h.c->header_size();

  memcpy(buff + padding, h.hf->get_name() , HASH_FUNCTION_STD_SIZE);
  padding += HASH_FUNCTION_STD_SIZE;
  
  h.hf->write(buff + padding);
  padding += h.hf->header_size();

  memcpy(buff + padding, &h.data_size, sizeof(h.data_size));
  padding += sizeof(h.data_size);

  memcpy(buff + padding, &h.hash, sizeof(h.hash));
  padding += sizeof(h.hash);

  if (h.encrypted_data_size != 0)
    memcpy(buff + padding, h.encrypted_data, h.encrypted_data_size);

  return buff;
}



char* read_file(const std::string& path, size_t& data_size) {
  std::ifstream is;
  
  is.open(path, std::ios::binary);
  if (!is.is_open())
    throw std::invalid_argument("Can not create file: " + path + "!\n");

  is.seekg(0, std::ios::end);
  data_size = is.tellg();
  char* data = new char[data_size];

  is.read(data, data_size);

  is.close();
  if (!is.good())
    throw std::invalid_argument("Error occurred at writing time!\n");

  return data;
}



void write_file(const std::string& path, size_t data_size, const char* data) {
  std::ofstream os;
  
  os.open(path, std::ios::binary);
  if (!os.is_open())
    throw std::invalid_argument("Can not create file: " + path + "!\n");

  os.write(data, data_size);

  os.close();
  if (!os.good())
    throw std::invalid_argument("Error occurred at writing time!\n");
}