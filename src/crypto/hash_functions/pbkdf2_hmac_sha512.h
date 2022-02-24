#ifndef PBKDF2_HMAC_SHA512_H
#define PBKDF2_HMAC_SHA512_H

#include <cstdint>
#include <istream>
#include <ostream>

#include "hash_function.h"

#define PBKDF2_HMAC_SH512_STD "PHSHA512"



class pbkdf2_hmac_sha512 : public hash_function {
public:
  const char* get_name();
  
  void set(std::istream& is, std::ostream& os);

  uint8_t* hash(char* password, uint16_t password_size, uint16_t key_size);

  uint64_t header_size();

  void read(char* begin);

  void write(char* begin);

private:
  uint16_t iterations_;
  uint16_t salt_size_;
  char* salt_;
};



#endif