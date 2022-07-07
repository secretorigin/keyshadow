// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#ifndef NOTE_WRITABLEARRAY_H
#define NOTE_WRITABLEARRAY_H



#include <vector>
#include "writable.h"



/**
 * @class WritableArray
 * @brief class for array of writable data
 * 
 * @code
 * Data of this Writable implementation (also of course there is a header):
 *                < Count >           |          < Objects >
 *                 2 bytes            |         unknown bytes
 */
class WritableArray : public Writable {
protected:
  std::vector<Writable*> array;

  uint32_t writeData(uint8_t* buff);
  uint32_t readData(uint8_t* buff);

public:
  WritableArray();
  WritableArray(std::string name);

  uint16_t code(); // get type/id/code of this object class
  uint32_t size(); // get full size of writed data

  using Writable::setName;
  using Writable::write;
  using Writable::read;

  ~WritableArray();

  // WritableArray methods
  void add(Writable* object);
  void remove(size_t index);
  uint16_t count();
  
  // do not delete this objects !!!
  Writable* operator[] (size_t index);
};



#endif