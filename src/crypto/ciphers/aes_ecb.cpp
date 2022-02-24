#include "aes_ecb.h"

#include <cstring>

#include "../core/aes.h"



const char* get_name() {
  return AES_ECB_STD; 
}



void AES_ECB::set(std::istream& is, std::ostream& os) {
  os << "Key length in bytes: ";
  is >> this->key_length_;
}



char* AES_ECB::encrypt(char* data, uint64_t data_size, uint8_t* key, uint16_t key_size, uint64_t& enc_size) {
  AES* aes;
  if (key_size == 32)
    aes = new AES(AESKeyLength::AES_256);
  else if (key_size == 24)
    aes = new AES(AESKeyLength::AES_192);
  else if (key_size = 16)
    aes = new AES(AESKeyLength::AES_128);
  else
    throw std::invalid_argument("Key size must be 128/192/256");

  uint64_t enc_size = data_size % 16 == 0 ? data_size : data_size - (data_size % 16) + 16;
  char* padded_data = new char[enc_size];
  memcpy(padded_data, data, data_size);
  memset(padded_data + data_size, AES_ECB_PADDING_SYMBOL, enc_size - data_size);


  char* encrypted_data = reinterpret_cast<char*>(aes->EncryptECB(reinterpret_cast<uint8_t*>(padded_data), enc_size, key));

  delete[] padded_data;
  delete aes;

  return encrypted_data;
}



char* AES_ECB::decrypt(char* data, uint64_t data_size, uint8_t* key, uint16_t key_size) {
  AES* aes;
  if (key_size == 32)
    aes = new AES(AESKeyLength::AES_256);
  else if (key_size == 24)
    aes = new AES(AESKeyLength::AES_192);
  else if (key_size = 16)
    aes = new AES(AESKeyLength::AES_128);
  else
    throw std::invalid_argument("Key size must be 128/192/256");

  char* decrypted_data = reinterpret_cast<char*>(aes->DecryptECB(reinterpret_cast<uint8_t*>(data), data_size, key));

  delete aes;

  return decrypted_data;
}



uint64_t AES_ECB::write(char* begin) {
  uint64_t padding = 0;
  memcpy(begin, AES_ECB_STD, CIPHER_STD_SIZE);
  padding += CIPHER_STD_SIZE;
  memcpy(begin + padding, &(this->key_length_), sizeof(this->key_length_));
  padding += sizeof(this->key_length_);

  return padding;
}



uint64_t AES_ECB::read(char* begin) {
  memcpy(&(this->key_length_), begin, sizeof(this->key_length_));
  
  return sizeof(this->key_length_);
}