// Copyright (c) 2021 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



/**
 * @file
 * @brief class encdata implementation
 *
 * Here is implementation of functions for encryption (encdata::encrypt()) and 
 * deryption (encdata::decrypt())
 */



#include <stdexcept>

#include "crypto/aes.h"
#include "crypto/crc32.h"

#include "core/encformat.h"
#include "core/encdata.h"



/**
 * @brief init key size for encryptor and decryptor
 * 
 * @param [in] keySize key size in bytes (16, 24, 32)
 * 
 * Init AES object which implements in crypto/aes.cpp and crypto/aes.h.
 */
encdata::encdata(uint16_t keySize) {
  aes_ = new AES(keySize * 8);
}



/**
 * @brief gets data from std::istream and decrypts it
 *
 * @param [in] istr input stream
 * @param [in] key key for AES encryption must be 128, 192 or 256 bits
 * @param [out] data pointer to free space to return decrypted data
 * 
 * @throw std::invalid_argument if signature is wrong, or if key is of wrong size
 *
 * @return decrypted data size, if key is wrong it returns 0
 * 
 * This function is for decryption data from std::istream in encprocessor format.
 * It gets header, data and tail from std::istream, decrypt all it need and we needs,
 * check hash to get guarantees that the key is correct and gives decrypted data.
 * 
 * Data format is described in encformat.h.
 */
uint32_t encdata::decrypt(std::istream* istr, const uint8_t* key, uint8_t** data) {
  uint32_t ecdataSize = 0; ///< length of encrypted data
  // check signature and get encrypted data length from header
  {
    uint8_t* header; ///< header with signature and encrypted data length
    header = (uint8_t *) new uint8_t[ENC_SIGNATURE_SIZE + ENC_DATALENGTH_SIZE];
    istr->read(reinterpret_cast<char*>(header), ENC_SIGNATURE_SIZE + ENC_DATALENGTH_SIZE);

    // check signature
    for (int i = 0; i < ENC_SIGNATURE_SIZE; i++)
      if (header[i] != std::string(ENC_SIGNATURE)[i])
        throw std::invalid_argument("Signature in encrypted stream is wrong");
    // get length of encrypted data
    memcpy(&ecdataSize, &(header[ENC_SIGNATURE_SIZE]), ENC_DATALENGTH_SIZE);

    delete[] header;
  }

  uint8_t* dcdata; ///< pointer for decrypted data
  // get encrypted data and decrypt it
  {
    uint8_t* ecdata; ///< pointer for encrypted data
    ecdata = (uint8_t*) new uint8_t[ecdataSize];
    istr->read(reinterpret_cast<char*>(ecdata), ecdataSize);
    dcdata = aes_->DecryptECB(ecdata, ecdataSize, const_cast<uint8_t*>(key));

    delete[] ecdata;
  }
  
  uint32_t hashFromTail = 0; ///< hash from tail to check key
  uint32_t dcdataSize = 0; ///< data size after decryption
  // decrypt tail and get info from it
  {
    // get encrypted tail and decrypt it
    uint8_t* dctail; ///< pointer for decrypted tail
    uint8_t* ectail; ///< pointer for encrypted tail
    ectail = (uint8_t*) new uint8_t[ENC_ENCRYPTED_TAIL_SIZE];
    istr->read(reinterpret_cast<char*>(ectail), ENC_ENCRYPTED_TAIL_SIZE);
    dctail = aes_->DecryptECB(ectail, ENC_ENCRYPTED_TAIL_SIZE, const_cast<uint8_t*>(key));
    
    // get hash and decrypted data length from tail
    memcpy(&hashFromTail, dctail, ENC_HASH_SIZE);
    memcpy(&dcdataSize, &(dctail[ENC_HASH_SIZE]), ENC_DATALENGTH_SIZE);

    delete[] dctail;
    delete[] ectail;
  }

  // get hash from data
  uint32_t hashFromData = 0; ///< hash from decrypted data to check key
  hashFromData = crcdetail::compute(reinterpret_cast<const char*>(dcdata), dcdataSize);

  // check hashes
  if (hashFromData != hashFromTail) {
    // if key is wrong
    return 0;
  } else {
    // all is ok
    *data = dcdata;
    return dcdataSize;
  }
}



/**
 * @brief encrypts and sets encrypted data in std::ostream
 *
 * @param [out] ostr output stream
 * @param [in] key key for AES encryption must be 128, 192 or 256 bits
 * @param [in] data data which we must encrypt and set in std::ostream
 * @param [in] dataSize size of the data
 * 
 * @throw std::invalid_argument if key is of wrong size
 * @throw std::runtime_error if something is changed in crypto and encrypted tail size != EC_ENCRYPTED_TAIL_SIZE
 *
 * Encrypt data and write it in specific data format described in encformat.h.
 */
void encdata::encrypt(std::ostream* ostr, const uint8_t* key, 
                      const uint8_t* data, uint32_t dataSize) {
  uint8_t* ectail; ///< encrypted tail
  // creating encrypted tail
  {
    uint8_t* tail; ///< tail with hash and data length
    
    // get hash
    uint32_t hash = crcdetail::compute(reinterpret_cast<const char*>(data), dataSize);
    
    tail = (uint8_t*) new uint8_t[ENC_HASH_SIZE + ENC_DATALENGTH_SIZE];
    memcpy(tail, &hash, ENC_HASH_SIZE);
    memcpy(&(tail[ENC_HASH_SIZE]), &dataSize, ENC_DATALENGTH_SIZE);

    // encrypt tail length
    uint32_t ectailLength = 0;
    ectail = aes_->EncryptECB(reinterpret_cast<uint8_t*>(tail), ENC_HASH_SIZE + ENC_DATALENGTH_SIZE,
                            const_cast<uint8_t*>(key), ectailLength);
    // check changed something in encryption or not
    if (ectailLength != ENC_ENCRYPTED_TAIL_SIZE)
      // undefined error, something changed in crypto
      throw std::runtime_error("Something changed in crypto or in data length");
    
    delete[] tail;
  }

  uint8_t* ecdata; ///< our data after encryption
  uint32_t ecdataSize = 0; ///< encrypted data length
  uint8_t* header; ///< header with signature and encrypted data length
  // encrypt data and create header
  {
    ecdata = aes_->EncryptECB(const_cast<uint8_t*>(data), dataSize, const_cast<uint8_t*>(key),
                            ecdataSize);
    
    header = (uint8_t *) new uint8_t[ENC_SIGNATURE_SIZE + ENC_DATALENGTH_SIZE];
    // set signature in header
    for (int i = 0; i < ENC_SIGNATURE_SIZE; i++)
      header[i] = std::string(ENC_SIGNATURE)[i];
    // set encrypted data size in header
    memcpy(&(header[ENC_SIGNATURE_SIZE]), &ecdataSize, ENC_DATALENGTH_SIZE);
  }

  // write data
  ostr->write(reinterpret_cast<char*>(header), ENC_SIGNATURE_SIZE + ENC_DATALENGTH_SIZE);
  ostr->write(reinterpret_cast<char*>(ecdata), ecdataSize);
  ostr->write(reinterpret_cast<char*>(ectail), ENC_ENCRYPTED_TAIL_SIZE);
  
  delete[] ectail;
  delete[] ecdata;
  delete[] header;
}



encdata::~encdata() {
  if (aes_ != nullptr)
    delete aes_;
}