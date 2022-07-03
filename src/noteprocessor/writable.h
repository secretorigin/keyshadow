// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#ifndef NOTE_WRITABLE_H
#define NOTE_WRITABLE_H



#include <stdint.h>
#include <string>



#define NOTE_DEFAULT_CODE 0



/**
 * @class Writable
 * @brief abstarct class for writable data
 * 
 * @code
 *    < Code > | < Name Length > |       < Name >      | < Data Length > |      < Data >
 *    2 bytes  |    1 bytes      | "Name Length" bytes |     4 bytes     | "Data Length" bytes  
 */
class Writable {
private:
  uint32_t writeHeader(uint8_t* buff);
  uint32_t readHeader(uint8_t* buff);

protected:
  uint8_t name_length;
  uint8_t* name;

  uint16_t code;
  uint32_t data_length;

  virtual uint32_t writeData(uint8_t* buff) = 0;
  virtual uint32_t readData(uint8_t* buff) = 0;

public:
  Writable();
  Writable(uint16_t code, std::string name);

  void setName(std::string name);

  virtual uint16_t getCode() = 0;
  virtual uint32_t getSize() = 0; //<- full size of writed data
  
  uint32_t write(uint8_t* buff);
  uint32_t read(uint8_t* buff);

  ~Writable();
};



#endif