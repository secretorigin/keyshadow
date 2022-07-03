// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include "writable.h"



/**
 * @brief write header in the buffer in writable format
 */
uint32_t Writable::writeHeader(uint8_t* buff) {
  size_t padding = 0;

  memcpy(buff + padding, &code, sizeof(uint16_t));
  padding += sizeof(uint16_t);
  memcpy(buff + padding, &name_length, sizeof(uint8_t));
  padding += sizeof(uint8_t);
  memcpy(buff + padding, name, name_length * sizeof(uint8_t));
  padding += name_length * sizeof(uint8_t);
  memcpy(buff + padding, &data_length, sizeof(uint32_t));
  padding += sizeof(uint32_t);

  return padding;
}



/**
 * @brief read header from the buffer in writable format
 */
uint32_t Writable::readHeader(uint8_t* buff) {
  size_t padding = 0;

  // write code
  memcpy(&code, buff + padding, sizeof(uint16_t));
  padding += sizeof(uint16_t);
  // write name length
  memcpy(&name_length, buff + padding, sizeof(uint8_t));
  padding += sizeof(uint8_t);
  // write name
  memcpy(name, buff + padding, name_length * sizeof(uint8_t));
  padding += name_length * sizeof(uint8_t);
  // write data length
  memcpy(&data_length, buff + padding, sizeof(uint32_t));
  padding += sizeof(uint32_t);

  return padding;
}



Writable::Writable() {
  this->code = NOTE_DEFAULT_CODE;
  this->name_length = 0;
  this->name = nullptr;
}



Writable::Writable(uint16_t code, std::string name) {
  this->code = code;
  this->name_length = name.length();
  memcpy(this->name, name.c_str(), this->name_length * sizeof(uint8_t));
}



/**
 * @brief set name to the writable object
 */
void Writable::setName(std::string name) {
  if (this->name != nullptr)
    delete[] this->name;

  this->name_length = name.length();
  memcpy(this->name, name.c_str(), this->name_length * sizeof(uint8_t));
}



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
 * @brief delete name
 */
Writable::~Writable() {
  if (name != nullptr)
    delete[] name;
}
