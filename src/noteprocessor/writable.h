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
template<class Derived>
class Writable {
protected:
  uint8_t name_length;
  uint8_t* name;

  uint32_t data_length;

  uint32_t writeHeader(uint8_t* buff);
  uint32_t readHeader(uint8_t* buff);
  virtual uint32_t writeData(uint8_t* buff) = 0;
  virtual uint32_t readData(uint8_t* buff) = 0;

  void copyHeader(const Derived& object);
  void copyHeader(Derived&& object);
  virtual void copyData(const Derived& object) = 0;
  virtual void copyData(Derived&& object) = 0;

public:
  Writable();
  Writable(std::string name);

  void setName(std::string name);

  void copy(const Derived& object);
  void copy(Derived&& object);
  virtual Derived* copy();

  virtual uint16_t code() = 0;
  virtual uint32_t size() = 0; //<- full size of writed data
  
  uint32_t write(uint8_t* buff);
  uint32_t read(uint8_t* buff);

  ~Writable();
};



#endif