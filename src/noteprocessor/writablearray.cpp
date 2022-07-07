// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034


#include "writablearray.h"
#include "factory.h"



WritableArray::WritableArray() : Writable() {}

WritableArray::WritableArray(std::string name) : Writable(name) {}

WritableArray::~WritableArray() {
  for (Writable* i : this->array)
    delete i;
}



/**
 * @brief type/code of this writable data
 */
uint16_t WritableArray::code() {
  return NOTE_WRITABLEARRAY_CODE;
}



/**
 * @brief size of this writable data
 */
uint32_t WritableArray::size() {
  data_length = COUNT_SIZE;
  for (size_t i = 0; i < array.size(); ++i)
    data_length += array[i]->size();

  return (HEADER_SIZE + name.length() + data_length);
}



/**
 * @brief add new element in array
 */
void WritableArray::add(Writable* data) {
  if (array.size() == MAX_ARRAY_SIZE)
    std::invalid_argument("Array already of max size: " + std::to_string(MAX_ARRAY_SIZE));

  array.push_back(data);
}



/**
 * @brief remove object by index
 */
void WritableArray::remove(size_t index) {
  if (index >= this->array.size())
    std::invalid_argument("Index out of range");

  delete this->array[index];
  this->array.erase(this->array.begin() + index);
}



/**
 * @brief get count of elements in array
 */
uint16_t WritableArray::count() {
  return this->array.size();
}



/**
 * @brief get element by index
 */
Writable* WritableArray::operator[] (size_t index) {
  if (index >= this->array.size())
    std::invalid_argument("Index out of range");

  return this->array[index];
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                                              PARSE
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// virtual function for writing data after header in buffer
uint32_t WritableArray::writeData(uint8_t* buff) {
  size_t padding = 0;

  uint16_t count = array.size();
  memcpy(buff, &count, sizeof(uint16_t));
  padding += sizeof(uint16_t);

  for (size_t i = 0; i < count; ++i) {
    array[i]->write(buff + padding);
    padding += array[i]->size();
  }

  return padding;
}



// virtual function for reading data after header from buffer
uint32_t WritableArray::readData(uint8_t* buff) {
  size_t padding = 0;
  // clear old data
  if (this->array.size() != 0) {
    for(Writable* i : this->array)
      delete i;
    this->array.clear();
  }

  // parse
  uint16_t count;
  memcpy(&count, buff, sizeof(uint16_t));
  padding += sizeof(uint16_t);
  
  this->array.resize(count);
  for (size_t i = 0; i < count; ++i) {
    uint16_t type;
    memcpy(&type, buff + padding, sizeof(uint16_t));
    this->array[i] = factory(type); // get new element from element's factory
    this->array[i]->read(buff + padding);
    padding += this->array[i]->size();
  }

  return padding;
}