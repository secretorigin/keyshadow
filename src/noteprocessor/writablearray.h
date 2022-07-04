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
class WritableArray : public Writable<WritableArray> {
private:
  std::vector<Writable*> array;

protected:
  uint32_t writeData(uint8_t* buff);
  uint32_t readData(uint8_t* buff);

  void copyData(const WritableArray& object);
  void copyData(WritableArray&& object);

public:
  WritableArray();
  WritableArray(std::string name);

  // get pointer to the copy of this class
  using Writable<WritableArray>::copy;
  WritableArray* copy();

  template<class WritableType>
  void add(const WritableType& data);
  template<class WritableType>
  void add(WritableType&& data);

  // get type/id/code of this object class
  uint16_t code();
  // get full size of writed data
  uint32_t size();

  ~WritableArray();

  /*
    There are a lot of methods which are not implemented here, but implenmented in writable class
  */
};



#endif