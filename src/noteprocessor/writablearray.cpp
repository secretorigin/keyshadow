// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include "writablearray.h"



WritableArray::WritableArray() : Writable() {}

WritableArray::WritableArray(std::string name) : Writable(name) {}



/**
 * @brief add new element in array
 */
template<class WritableType>
void WritableArray::add(const WritableType& data) {
  // check: is WritableType derived from Writable?
  static_assert(std::is_base_of<Writable<WritableType>, WritableType>::value, "WritableType not derived from Writable.");

  this->array.push_back(new WritableType());

  this->array[this->array.size() - 1]->copy(data);
}



/**
 * @brief add new element in array
 */
template<class WritableType>
void WritableArray::add(WritableType&& data) {
  // check: is WritableType derived from Writable?
  static_assert(std::is_base_of<Writable<WritableType>, WritableType>::value, "WritableType not derived from Writable.");

  array.push_back(new WritableType());

  array[array.size() - 1]->copy(data);
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
  data_length = 0;
  for (size_t i = 0; i < array.size(); ++i)
    data_length += array[i]->size();

  return (7 + name_length + data_length);
}



WritableArray::~WritableArray() {
  for (Writable* i : this->array)
    delete i;
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                                              PARSE
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

uint32_t WritableArray::writeData(uint8_t* buff) {
  size_t padding = 0;
  for (size_t i = 0; i < array.size(); ++i) {
    array[i]->write(buff + padding);
    padding += array[i]->size();
  }

  return padding;
}



uint32_t WritableArray::readData(uint8_t* buff) {
  size_t padding = 0;
  for (size_t i = 0; i < array.size(); ++i) {
    array[i]->read(buff + padding);
    padding += array[i]->size();
  }

  return padding;
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                                              COPY
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/**
 * @brief get copy allocated with operator new
 */
WritableArray* WritableArray::copy() {
  WritableArray* copied = (WritableArray*) new WritableArray;
  copied->copy(*this);
  return copied;
}



// copy data function
void WritableArray::copyData(const WritableArray& object) {
  // clear ouir array
  if (this->array.size() != 0) {
    for(Writable* i : this->array)
      delete i;
    this->array.clear();
  }

  this->array.resize(object.array.size());
  for (size_t i = 0; i < object.array.size(); ++i)
    this->array[i] = object.array[i]->copy();
}



// move data function
void WritableArray::copyData(WritableArray&& object) {
  // clear ouir array
  if (this->array.size() != 0) {
    for(Writable* i : this->array)
      delete i;
    this->array.clear();
  }

  this->array.resize(object.array.size());
  for (size_t i = 0; i < object.array.size(); ++i)
    this->array[i] = object.array[i];
}