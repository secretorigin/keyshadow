// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#ifndef NOTE_WRITABLELOGINNOTE_H
#define NOTE_WRITABLELOGINNOTE_H



#include <string>
#include "writable.h"



/**
 * @class WritableArray
 * @brief abstarct class for array of writable data
 * 
 * @code
 *                          < Count >           |          < Objects >
 *                           2 bytes            |         unknown bytes
 */
class WritableLoginNote : public Writable {
protected:
  std::string login;
  std::string password;

  uint32_t writeData(uint8_t* buff);
  uint32_t readData(uint8_t* buff);

public:
  WritableLoginNote();
  WritableLoginNote(std::string name);
  WritableLoginNote(std::string name, std::string login, std::string password);

  uint16_t code(); // get type/id/code of this object class
  uint32_t size(); // get full size of writed data

  using Writable::setName;
  using Writable::write;
  using Writable::read;

  ~WritableLoginNote();

  void setLogin(std::string login);
  void setPassword(std::string password);
  std::string getLogin();
  std::string getPassword();
};



#endif