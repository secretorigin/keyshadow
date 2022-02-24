#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

#include <cstdint>
#include <istream>
#include <ostream>

#define HASH_FUNCTION_STD_SIZE 8



class hash_function {
public:
  virtual const char* get_name() = 0;

  virtual void set(std::istream& is, std::ostream& os) = 0;

  virtual uint8_t* hash(char* password, uint16_t password_size, uint16_t key_size) = 0;

  virtual uint64_t read(char* begin) = 0;

  virtual uint64_t write(char* begin) = 0;
};



#endif