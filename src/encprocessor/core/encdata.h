// Copyright (c) 2021 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



/**
 * @file
 * @brief class encdata declaration
 */



#ifndef ENC_ENCDATA_H
#define ENC_ENCDATA_H



#include "crypto/aes.h"



/**
 * @class encdata
 * @brief encrypted data (std::iostream) processor
 * 
 * Encryptor and decryptor for std::iostream. It is using AES(128/192/256), 
 * which implements in crypto/aes.cpp and crypto/aes.h.
 */
class encdata {
private:
  AES* aes_ = nullptr; ///< chipher
public:
  // init AES
  encdata(uint16_t keySize);
  
  // decrypt data from istr
  uint32_t decrypt(std::istream* istr, const uint8_t* key, uint8_t** data);

  // encrypt data with set it in ostr
  void encrypt(std::ostream* ostr, const uint8_t* key, 
               const uint8_t* data, uint32_t dataSize);

  // delete AES object
  ~encdata();
};



#endif