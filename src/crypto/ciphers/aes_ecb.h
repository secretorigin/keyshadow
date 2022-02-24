#ifndef AES_ECB_H
#define AES_ECB_H

#include <cstdint>
#include <istream>
#include <ostream>

#include "cipher.h"



#define AES_ECB_PADDING_SYMBOL '0'

#define AES_ECB_STD "AESECB\0\0"

#define AES_ECB_HEADER_SIZE 2



class aes_ecb : public cipher {
public:
  const char* get_name();

  void set(std::istream& is, std::ostream& os);

  char* encrypt(char* data, uint64_t data_size, uint8_t* key, uint16_t key_size, uint64_t& enc_size);

  char* decrypt(char* data, uint64_t data_size, uint8_t* key, uint16_t key_size);

  uint64_t header_size();

  uint16_t key_size();

  void write(char* begin);

  void read(char* begin);

private:
  uint16_t key_length_;
};



#endif