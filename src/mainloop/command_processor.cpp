#include "command_processor.h"

#include <exception>
#include <string>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <functional>
#include <utility>

#include "database/encrypted_file.h"
#include "../crypto/core/crc32.h"



std::string new_password_input() {
  std::string password = getpass("Password: ");
  
  std::string repeated_password = getpass("Repeat password: ");
  
  if (repeated_password.length() != password.length() || 
      memcmp(password.c_str(), repeated_password.c_str(), password.length()) != 0)
    throw std::invalid_argument("Passwords are not same.");

  return password;
}



std::string old_password_input() {
  return std::string(getpass("Password: "));
}



void command_processor(int argc, char* argv[]) {
  parsed_encrypted_file file;

  char* buff = read_file();

}