// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include "writableloginnote.h"
#include "factory.h"



WritableLoginNote::WritableLoginNote() : Writable() {}

WritableLoginNote::WritableLoginNote(std::string name) : Writable(name) {}

WritableLoginNote::WritableLoginNote(std::string name, std::string login, std::string password) : Writable(name) {
  if (MAX_LOGIN_SIZE < login.length())
    std::invalid_argument("Login can be up to " + std::to_string(MAX_LOGIN_SIZE));
  if (MAX_PASSWORD_SIZE < password.length())
    std::invalid_argument("Password can be up to " + std::to_string(MAX_PASSWORD_SIZE));
  
  this->login = login;
  this->password = password;
}



/**
 * @brief type/code of this writable data
 */
uint16_t WritableLoginNote::code() {
  return NOTE_WRITABLELOGINNOTE_CODE;
}



/**
 * @brief size of this writable data
 */
uint32_t WritableLoginNote::size() {
  data_length = 4 + login.length() + password.length();
  return (HEADER_SIZE + name.length() + data_length);
}



WritableLoginNote::~WritableLoginNote() {}



/**
 * @brief set login in note
 * 
 * @param [in] login one of the note parameters
 */
void WritableLoginNote::setLogin(std::string login) {
  if (MAX_LOGIN_SIZE < login.length())
    std::invalid_argument("Login can be up to " + std::to_string(MAX_LOGIN_SIZE));

  this->login = login;
}



/**
 * @brief set password in note
 * 
 * @param [in] password one of the note parameters
 */
void WritableLoginNote::setPassword(std::string password) {
  if (MAX_PASSWORD_SIZE < password.length())
    std::invalid_argument("Password can be up to " + std::to_string(MAX_PASSWORD_SIZE));
    
  this->password = password;
}


/**
 * @brief get login from note
 * 
 * @return login
 */
std::string WritableLoginNote::getLogin() {
  return login;
}



/**
 * @brief get password from note
 * 
 * @return password
 */
std::string WritableLoginNote::getPassword() {
  return password;
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                                              PARSE
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// virtual function for writing data after header in buffer
uint32_t WritableLoginNote::writeData(uint8_t* buff) {
  size_t padding = 0;
  uint16_t size;

  // write login
  size = login.length();
  memcpy(buff + padding, &size, sizeof(uint16_t));
  padding += sizeof(uint16_t);
  memcpy(buff + padding, login.c_str(), size * sizeof(uint8_t));
  padding += size * sizeof(uint8_t);
  
  // write password
  size = password.length();
  memcpy(buff + padding, &size, sizeof(uint16_t));
  padding += sizeof(uint16_t);
  memcpy(buff + padding, password.c_str(), size * sizeof(uint8_t));
  padding += size * sizeof(uint8_t);

  return padding;
}



// virtual function for reading data after header from buffer
uint32_t WritableLoginNote::readData(uint8_t* buff) {
  size_t padding = 0;
  uint16_t size;

  // read password
  size = login.length();
  memcpy(&size, buff + padding, sizeof(uint16_t));
  padding += sizeof(uint16_t);
  login.resize(size);
  for (size_t i = 0; i < size; ++i)
    login[i] = buff[padding + i];
  padding += size * sizeof(uint8_t);
  
  // read password
  size = password.length();
  memcpy(&size, buff + padding, sizeof(uint16_t));
  padding += sizeof(uint16_t);
  password.resize(size);
  for (size_t i = 0; i < size; ++i)
    password[i] = buff[padding + i];
  padding += size * sizeof(uint8_t);

  return padding;
}