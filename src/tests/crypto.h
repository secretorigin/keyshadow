#ifndef CRYPTO_H
#define CRYPTO_H


#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <exception>

#include "aes.h"
#include "textprocessor.h"
#include "pbkdf2.h"


// standarts
#define AES_ECB "AECB"
#define PBKDF2_HMAC_SHA512 "PHS5"



#define STD_SIZE 4

#define PARAMS_SIZE 22

// 22 + saltsize
struct crypto_parameters {
  uint16_t key_size;
  uint64_t data_size;
  char encr_std[STD_SIZE];
  char hash_std[STD_SIZE];
  uint16_t iterations;
  uint16_t salt_size;
  char* salt;
  uint8_t extension_size;
  char* extension;

  ~crypto_parameters() {
    delete[] salt;
    delete[] extension;
  }
};



void set_params(char* buff, const crypto_parameters& params) {
  size_t padding = 0;
  memcpy(buff, &params.key_size, sizeof(params.key_size));
  padding += sizeof(params.key_size);
  memcpy(buff + padding, &params.data_size, sizeof(params.data_size));
  padding += sizeof(params.data_size);
  memcpy(buff + padding, params.encr_std, STD_SIZE);
  padding += STD_SIZE;
  memcpy(buff + padding, params.hash_std, STD_SIZE);
  padding += STD_SIZE;
  memcpy(buff + padding, &params.iterations, sizeof(params.iterations));
  padding += sizeof(params.iterations);
  memcpy(buff + padding, &params.salt_size, sizeof(params.salt_size));
  padding += sizeof(params.salt_size);
  memcpy(buff + padding, params.salt, params.salt_size);
  padding += params.salt_size;
  memcpy(buff + padding, &params.extension_size, sizeof(params.extension_size));
  padding += sizeof(params.extension_size);
  memcpy(buff + padding, params.extension, params.extension_size);
}

size_t get_params(char* buff, crypto_parameters& params) {
  size_t padding = 0;
  memcpy(&params.key_size, buff + padding, sizeof(params.key_size));
  padding += sizeof(params.key_size);
  memcpy(&params.data_size, buff + padding, sizeof(params.data_size));
  padding += sizeof(params.data_size);
  memcpy(params.encr_std, buff + padding, STD_SIZE);
  padding += STD_SIZE;
  memcpy(params.hash_std, buff + padding, STD_SIZE);
  padding += STD_SIZE;
  memcpy(&params.iterations, buff + padding, sizeof(params.iterations));
  padding += sizeof(params.iterations);
  memcpy(&params.salt_size, buff + padding, sizeof(params.salt_size));
  padding += sizeof(params.salt_size);
  params.salt = new char[params.salt_size];
  memcpy(params.salt, buff + padding, params.salt_size);
  padding += params.salt_size;
  memcpy(&params.extension_size, buff + padding, sizeof(params.extension_size));
  padding += sizeof(params.extension_size);
  params.extension = new char[params.extension_size];
  memcpy(params.extension, buff + padding, params.extension_size);
  padding += params.extension_size;

  return padding;
}



char* encrypt_data(char* data, uint64_t data_size, 
                   char* password, size_t password_size, size_t& encrypted_data_size, uint16_t key_size) {
  // init main values
  AES* aes;
  crypto_parameters params;
  
  if (key_size == 32)
    aes = new AES(AESKeyLength::AES_256);
  else if (key_size == 24)
    aes = new AES(AESKeyLength::AES_192);
  else if (key_size = 16)
    aes = new AES(AESKeyLength::AES_128);
  else
    throw std::invalid_argument("Key size must be 128/192/256");
  
  // set params
  params.key_size = key_size;
  params.data_size = data_size;
  
  memcpy(params.encr_std, AES_ECB, STD_SIZE);
  memcpy(params.hash_std, PBKDF2_HMAC_SHA512, STD_SIZE);
  
  params.iterations = rand() % 512 + 2048;

  params.salt_size = rand() % 4 + 16;
  params.salt = new char[params.salt_size];
  memcpy(params.salt, TextProcessor().numbers().lowercase().uppercase().genrand(params.salt_size).c_str(), params.salt_size);


  // data_size must be muliptied of 16
  encrypted_data_size = data_size % 16 == 0 ? data_size : data_size - (data_size % 16) + 16;
  char* padded_data = new char[encrypted_data_size];
  memcpy(padded_data, data, data_size);
  memset(padded_data + data_size, '0', encrypted_data_size - data_size);

  // get key
  uint8_t* key = new uint8_t[params.key_size];
  PBKDF2_HMAC_SHA_512(password, password_size, params.salt, params.salt_size, 
                      params.iterations, params.key_size, key);
  
  // encrypt
  char* encrypted_data = reinterpret_cast<char*>(aes->EncryptECB(reinterpret_cast<uint8_t*>(padded_data), encrypted_data_size, key));
  
  // assembly
  size_t params_size = PARAMS_SIZE + params.salt_size;
  char* assembled_data = new char[params_size + encrypted_data_size];
  set_params(assembled_data, params);
  memcpy(assembled_data + params_size, encrypted_data, encrypted_data_size);
  
  delete[] aes;
  delete[] params.salt;
  delete[] padded_data;
  delete[] key;
  delete[] encrypted_data;
  
  encrypted_data_size += params_size;
  return assembled_data;
}




char* decrypt_data(char* data, uint64_t data_size, 
                   char* password, size_t password_size, size_t& clear_data_size) {
  AES* aes;
  crypto_parameters params;
  // init params
  size_t params_size = get_params(data, params);
  
  // init aes
  if (params.key_size == 32)
    aes = new AES(AESKeyLength::AES_256);
  else if (params.key_size == 24)
    aes = new AES(AESKeyLength::AES_192);
  else if (params.key_size = 16)
    aes = new AES(AESKeyLength::AES_128);
  else
    throw std::invalid_argument("Key size must be 128/192/256");

  // get key
  uint8_t* key = new uint8_t[params.key_size];
  PBKDF2_HMAC_SHA_512(password, password_size, params.salt, params.salt_size, 
                      params.iterations, params.key_size, key);

  size_t encrypted_data_size = data_size - params_size;
  char* encrypted_data = new char[encrypted_data_size];
  memcpy(encrypted_data, data + params_size, encrypted_data_size);

  // encrypt
  char* decrypted_data = reinterpret_cast<char*>(aes->DecryptECB(reinterpret_cast<uint8_t*>(encrypted_data), encrypted_data_size, key));
  
  char* clear_data = new char[params.data_size];
  memcpy(clear_data, decrypted_data, params.data_size);
  clear_data_size = params.data_size;

  delete[] aes;
  delete[] params.salt;
  delete[] key;
  delete[] encrypted_data;
  delete[] decrypted_data;
  
  return clear_data;
}


#endif