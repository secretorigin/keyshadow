#include "aes_ecb.h"

#include <cstring>

#include "../core/aes.h"



const char* aes_ecb::get_name() {
  return AES_ECB_STD; 
}



void aes_ecb::set(std::istream& is, std::ostream& os) {
  os << "Key length in bytes: ";
  is >> this->key_length_;
}



char* aes_ecb::encrypt(const char* data, uint64_t data_size, const uint8_t* key, uint16_t key_size, uint64_t& enc_size) {
  AES* aes;
  if (key_size == 32)
    aes = new AES(AESKeyLength::AES_256);
  else if (key_size == 24)
    aes = new AES(AESKeyLength::AES_192);
  else if (key_size == 16)
    aes = new AES(AESKeyLength::AES_128);
  else
    throw std::invalid_argument("Key size must be 128/192/256");

  enc_size = data_size % 16 == 0 ? data_size : data_size - (data_size % 16) + 16;
  char* padded_data = new char[enc_size];
  memcpy(padded_data, data, data_size);
  memset(padded_data + data_size, AES_ECB_PADDING_SYMBOL, enc_size - data_size);


  char* encrypted_data = reinterpret_cast<char*>(aes->EncryptECB(reinterpret_cast<uint8_t*>(padded_data), enc_size, key));

  delete[] padded_data;
  delete aes;

  return encrypted_data;
}



char* aes_ecb::decrypt(const char* data, uint64_t data_size, const uint8_t* key, uint16_t key_size) {
  AES* aes;
  if (key_size == 32)
    aes = new AES(AESKeyLength::AES_256);
  else if (key_size == 24)
    aes = new AES(AESKeyLength::AES_192);
  else if (key_size == 16)
    aes = new AES(AESKeyLength::AES_128);
  else
    throw std::invalid_argument("Key size must be 128/192/256");

  char* decrypted_data = reinterpret_cast<char*>(aes->DecryptECB(reinterpret_cast<uint8_t*>(data), data_size, key));

  delete aes;

  return decrypted_data;
}



uint64_t aes_ecb::header_size() {
  return AES_ECB_HEADER_SIZE;
}



uint16_t aes_ecb::key_size() {
  return this->key_length_;
}



void aes_ecb::write(char* begin) {
  memcpy(begin, &(this->key_length_), sizeof(this->key_length_));
}



void aes_ecb::read(char* begin) {
  memcpy(&(this->key_length_), begin, sizeof(this->key_length_));
}