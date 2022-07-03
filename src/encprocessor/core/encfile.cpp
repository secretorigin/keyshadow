// Copyright (c) 2021 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



/**
 * @file
 * @brief encfile class implementation
 * 
 * Here is implementation for reading data from file (encfile::decrypt()) and writing in it (encfile::encrypt()).
 */



#include <fstream>
#include <stdexcept>

#include "core/encdata.h"
#include "core/encfile.h"



/**
 * @brief init chipher
 */
encfile::encfile(uint16_t keySize) {
  datastream_ = new encdata(keySize);
}



/**
 * @brief decrypts data from file
 *
 * @param [in] fileName path to the file
 * @param [in] key key for decryption
 * @param [out] data decrypted data
 * 
 * @throw std::invalid_argument if signature is wrong, or if key is of wrong size
 * @throw std::invalid_argument if we can not find file with this path
 *
 * @return size of decrypted data
 */
uint32_t encfile::decrypt(std::string fileName, const uint8_t* key, uint8_t** data) {
  std::ifstream file; ///< std::istream for encdata::decrypt()

  uint32_t dataSize; ///< decrypted data size

  // get decrypted data from file
  file.open(fileName); {
    if (!file.is_open())
      throw std::invalid_argument("Can not open file '" + fileName + "'");

    dataSize = datastream_->decrypt(&file, key, data);
  } file.close();

  return dataSize; 
}


/**
 * @brief encrypts data in file
 *
 * @param [in] fileName path to the file
 * @param [in] key key for AES encryption must be 128, 192 or 256 bits
 * @param [in] data data which we must encrypt and set in file
 * @param [in] dataSize size of the data

 * @throw std::invalid_argument if key is of wrong size
 * @throw std::runtime_error if something is changed in crypto and encrypted tail size != EC_ENCRYPTED_TAIL_SIZE
 * @throw std::invalid_argument if we can not find file with this path
 *
 * Encrypt data and write it in the file using specific data format described in encformat.h.
 */
void encfile::encrypt(std::string fileName, const uint8_t* key,
                      const uint8_t* data, uint32_t dataSize) {
  std::ofstream file; ///< std::ostream for decdata::decrypt()

  // write data in file
  file.open(fileName); {
    if (!file.is_open())
      throw std::invalid_argument("Can not open file '" + fileName + "'");

    datastream_->encrypt(&file, key, data, dataSize);
  } file.close();
}



encfile::~encfile() {
  if (datastream_ != nullptr)
    delete datastream_;
}