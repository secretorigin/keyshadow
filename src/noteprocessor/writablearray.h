// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#ifndef NOTE_WRITABLEARRAY_H
#define NOTE_WRITABLEARRAY_H



#include <vector>
#include "writable.h"



#define NOTE_WRITABLEARRAY_CODE 1



/**
 * @class WritableArray
 * @brief abstarct class for array of writable data
 */
class WritableArray : public Writable {
private:
  std::vector<Writable*> array;

protected:
  uint32_t writeData(uint8_t* buff);
  uint32_t readData(uint8_t* buff);

public:
  WritableArray();
  WritableArray(std::string name);

  void add(Writable* data);

  // virtual 
  uint16_t getCode();
  uint32_t getSize(); //<- full size of writed data

  /*
    There are a lot of methods which are not implemented here, but implenmented in writable class
  */
};



#endif