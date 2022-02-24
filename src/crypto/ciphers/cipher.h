#ifndef CIPHER_H
#define CIPHER_H

#include <cstdint>
#include <istream>
#include <ostream>

#define CIPHER_STD_SIZE 8



class cipher {
public:
  virtual const char* get_name() = 0;

  virtual void set(std::istream& is, std::ostream& os) = 0;

  virtual char* encrypt(char* data, uint64_t data_size, uint8_t* key, uint16_t key_size, uint64_t& enc_size) = 0;

  virtual char* decrypt(char* data, uint64_t data_size, uint8_t* key, uint16_t key_size) = 0;

  virtual uint64_t header_size() = 0;

  virtual uint16_t key_size() = 0;

  virtual void read(char* begin) = 0;

  virtual void write(char* begin) = 0;
};



#endif