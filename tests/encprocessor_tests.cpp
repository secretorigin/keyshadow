// Copyright (c) 2021 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



/**
 * @file
 * @brief tests and examples for encdata and encfile
 */



#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <stdexcept>

#include "core/encdata.h"
#include "core/encfile.h"



// stream

void simpleTest(uint8_t* key, uint32_t keySize, uint8_t* data, uint32_t dataSize) {
  // encryption
  std::stringstream sstr;
  encdata datastream(keySize);
  datastream.encrypt(&sstr, key, data, dataSize);

  uint8_t* str;
  uint32_t strSize;

  strSize = datastream.decrypt(&sstr, key, &str);
  if (strSize == 0) {
    throw std::runtime_error("Wrong key");
  } else if (strSize != dataSize) {
    throw std::runtime_error("Wrong size");
  } else {
    bool check = true;
    for (int i = 0; i < dataSize; i++)
      if (data[i] != str[i])
        check = false;

    if (check == false)
      throw std::runtime_error("Wrong data after decryption");
  }
}



void globalTests() {
  uint8_t* data;
  uint32_t dataSize;
  uint8_t* key;
  uint32_t keySize;

  srand(time(NULL));

  for (int j = 1; j < 1000; j++) {
    keySize = 32;
    key = (uint8_t*) new uint8_t[keySize];
    for (int i = 0; i < keySize; i++)
      key[i] = rand() % 128;

    dataSize = j;
    data = (uint8_t*) new uint8_t[dataSize];
    for (int i = 0; i < dataSize; i++)
      data[i] = rand() % 128;

    simpleTest(key, keySize, data, dataSize);

    delete[] key;
    delete[] data;
  }
}



// file

void fileTest() {
  srand(time(NULL));

  uint8_t* data;
  uint32_t dataSize;
  uint8_t* key;
  uint32_t keySize;

  keySize = 32;

  encfile file(keySize);

  key = (uint8_t*) new uint8_t[keySize];
  for (int i = 0; i < keySize; i++)
    key[i] = rand() % 128;

  dataSize = 100;
  data = (uint8_t*) new uint8_t[dataSize];
  for (int i = 0; i < dataSize; i++)
    data[i] = rand() % 128;

  std::cout << "Data size: " << dataSize << std::endl;

  for (int i = 0; i < dataSize; i++)
    std::cout << data[i] << " ";
  std::cout << std::endl;

  uint8_t* data_;
  uint32_t dataSize_;

  file.encrypt("database.enc", key, data, dataSize);

  dataSize_ = file.decrypt("database.enc", key, &data_);

  std::cout << "Data size: " << dataSize_ << std::endl;

  for (int i = 0; i < dataSize_; i++)
    std::cout << data_[i] << " ";
  std::cout << std::endl;
}
