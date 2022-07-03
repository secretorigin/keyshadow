// Copyright (c) 2021 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



/**
 * @file
 * @brief encfile class declaration
 * 
 * Here is implementation for reading data from file (encfile::decrypt()) and writing in it (encfile::encrypt()).
 */



#ifndef ENC_ENCFILE_H
#define ENC_ENCFILE_H



#include "core/encdata.h"



/**
 * @class encfile
 * @brief encrypted data (std::iostream) processor
 * 
 * Just encdata class encapsulation. Encryptor and decryptor for files.
 **/
class encfile {
private:
  encdata* datastream_ = nullptr; ///< chipher
public:
  // init chipher
  encfile(uint16_t keySize);

  // decrypt data from file and get it in uint8_t*'s array
  uint32_t decrypt(std::string fileName, const uint8_t* key, uint8_t** data);

  // encrypt data and set it in file
  void encrypt(std::string fileName, const uint8_t* key,
               const uint8_t* data, uint32_t dataSize);

  // delete chipher
  ~encfile();
};



#endif