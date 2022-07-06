// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#ifndef NOTE_WRITABLE_H
#define NOTE_WRITABLE_H



#include <stdint.h>
#include <string>



/**
 * @class Writable
 * @brief abstarct class for writable data
 * 
 * @code
 *    < Code > | < Name Length > |       < Name >      | < Data Length > |      < Data >
 *    2 bytes  |    1 bytes      | "Name Length" bytes |     4 bytes     | "Data Length" bytes  
 */
class Writable {
protected:
  std::string name;
  uint32_t data_length;

  uint32_t writeHeader(uint8_t* buff);
  uint32_t readHeader(uint8_t* buff);
  virtual uint32_t writeData(uint8_t* buff) = 0;
  virtual uint32_t readData(uint8_t* buff) = 0;

public:
  Writable();
  Writable(std::string name);

  virtual uint16_t code() = 0; // get type/id/code of this object class
  virtual uint32_t size() = 0; // get full size of writed data

  void setName(std::string name);
  std::string getName();
  
  uint32_t write(uint8_t* buff); //<- write data in buffer
  uint32_t read(uint8_t* buff); //<- read data from buffer

  virtual ~Writable();
};



#endif