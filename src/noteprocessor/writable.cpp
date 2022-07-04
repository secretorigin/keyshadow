// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include "writable.h"




Writable::Writable() {}



Writable::Writable(std::string name) {
  this->name = name;
}



/**
 * @brief set name to the writable object
 */
void Writable::setName(std::string name) {
  this->name = name;
}



/**
 * @brief get name of the writable object
 */
std::string Writable::getName() {
  return name;
}



/**
 * @brief delete name
 */
Writable::~Writable() {}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                                              PARSE
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/**
 * @brief set data in buffer
 */
uint32_t Writable::write(uint8_t* buff) {
  size_t padding = this->writeHeader(buff);
  padding += this->writeData(buff + padding);
  return padding;
}



/**
 * @brief parse data from buffer
 */
uint32_t Writable::read(uint8_t* buff) {
  size_t padding = this->readHeader(buff);
  padding += this->readData(buff + padding);
  return padding;
}



/**
 * @brief write header in the buffer in writable format
 */
uint32_t Writable::writeHeader(uint8_t* buff) {
  size_t padding = 0;
  uint8_t name_length = name.length();
  uint16_t code = this->code();

  memcpy(buff + padding, &code, sizeof(uint16_t));
  padding += sizeof(uint16_t);

  // write name length
  memcpy(buff + padding, &name_length, sizeof(uint8_t));
  padding += sizeof(uint8_t);
  // write name
  memcpy(buff + padding, name.c_str(), name_length * sizeof(uint8_t));
  padding += name_length * sizeof(uint8_t);
  // write data length
  memcpy(buff + padding, &data_length, sizeof(uint32_t));
  padding += sizeof(uint32_t);

  return padding;
}



/**
 * @brief read header from the buffer in writable format
 */
uint32_t Writable::readHeader(uint8_t* buff) {
  size_t padding = 0;
  uint8_t name_length;
  uint16_t code;

  memcpy(&code, buff + padding, sizeof(uint16_t));
  if (code != this->code())
    throw std::invalid_argument("Wrong onject type.");
  padding += sizeof(uint16_t);

  // read name length
  memcpy(&name_length, buff + padding, sizeof(uint8_t));
  padding += sizeof(uint8_t);

  // read name
  name.resize(name_length);
  for (size_t i = 0; i < name.length(); ++i)
    name[i] = buff[i + padding];
  padding += name_length * sizeof(uint8_t);
  // read data length
  memcpy(&data_length, buff + padding, sizeof(uint32_t));
  padding += sizeof(uint32_t);

  return padding;
}