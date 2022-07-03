// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include "writablearray.h"



uint32_t WritableArray::writeData(uint8_t* buff) {
  size_t padding = 0;
  for (size_t i = 0; i < array.size(); ++i) {
    array[i]->write(buff + padding);
    padding += array[i]->getSize();
  }

  return padding;
}



uint32_t WritableArray::readData(uint8_t* buff) {
  size_t padding = 0;
  for (size_t i = 0; i < array.size(); ++i) {
    array[i]->read(buff + padding);
    padding += array[i]->getSize();
  }

  return padding;
}



WritableArray::WritableArray() : Writable() {
  this->code = NOTE_WRITABLEARRAY_CODE;
}



WritableArray::WritableArray(std::string name) : Writable(NOTE_WRITABLEARRAY_CODE, name) {}



/**
 * @brief type/code of this writable data
 */
uint16_t WritableArray::getCode() {
  return code;
}



/**
 * @brief size of this writable data
 */
uint32_t WritableArray::getSize() {
  data_length = 0;
  for (size_t i = 0; i < array.size(); ++i)
    data_length += array[i]->getSize();

  return (7 + name_length + data_length);
}