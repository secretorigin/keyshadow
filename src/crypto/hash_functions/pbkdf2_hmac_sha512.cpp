#include "pbkdf2_hmac_sha512.h"

#include <cstring>
#include <ctime>

#include "../core/pbkdf2.h"
#include "../core/textprocessor.h"



const char* get_name() {
  return PBKDF2_HMAC_SHA512_STD;
}



void pbkdf2_hmac_sha512::set(std::istream& is, std::ostream& os) {
  std::string salt;
  char answer;
  srand(time(0));

  os << "Gen parameters by chance?(y/n): ";
  is >> answer;
  if (answer == 'y') {
    this->iterations_ = rand() % 512 + 2048;
    this->salt_size_ = rand() % 4 + 16;
    this->salt_ = new char[this->salt_size_];
    memcpy(this->salt_, TextProcessor().numbers()
                                .lowercase()
                                .uppercase()
                                .genrand(this->salt_size_).c_str(), this->salt_size_);
  } else {
    os << "Iterations count: ";
    is >> this->iterations_;
    os << "Salt: ";
    is >> salt;
  }

  memcpy(this->salt_, salt.c_str(), salt.length());
  this->salt_size_ = salt.length();
}



uint8_t* pbkdf2_hmac_sha512::hash(char* password, uint16_t password_size, uint16_t key_size) {
  // get key
  uint8_t* key = new uint8_t[key_size];
  PBKDF2_HMAC_SHA_512(password, password_size, this->salt_, this->salt_size_, 
                      this->iterations_, key_size, key);
  
  return key;
}



uint64_t pbkdf2_hmac_sha512::header_size() {
  return 4 + this->salt_size_;
}



void pbkdf2_hmac_sha512::read(char* begin) {
  uint64_t padding = 0;
  memcpy(begin + padding, &(this->iterations_), sizeof(this->iterations_));
  padding += sizeof(this->iterations_);
  memcpy(begin + padding, &(this->salt_size_), sizeof(this->salt_size_));
  padding += sizeof(this->salt_size_);
  memcpy(begin + padding, this->salt_, this->salt_size_);
}



void pbkdf2_hmac_sha512::write(char* begin) {
  uint64_t padding = 0;
  memcpy(&(this->iterations_), begin, sizeof(this->iterations_));
  padding += sizeof(this->iterations_);
  memcpy(&(this->salt_size_), begin + padding, sizeof(this->salt_size_));
  padding += sizeof(this->salt_size_);
  memcpy(this->salt_, begin + padding, this->salt_size_);
}



pbkdf2_hmac_sha512::~pbkdf2_hmac_sha512() {
  delete[] this->salt_;
}