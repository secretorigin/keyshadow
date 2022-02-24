#include "command_processor.h"

#include <string>
#include <cstring>
#include <unistd.h>

#include <exception>


// work with std::cout and std::cin
void create(std::string path) {
  // get password
  char* password = getpass("Password: ");
  size_t password_size = std::strlen(password);
  char* repeated_password = getpass("Repeat password: ");
  if (strlen(repeated_password) != password_size || memcmp(password, repeated_password, password_size) != 0)
    throw std::invalid_argument("Different passwords.");
  delete[] repeated_password;

  
}



void command_processor(int argc, char* argv[]) {
  int first_index;
  if (argc > 1 && argv[1][0] == '-')
    first_index = 1;
  else 
    first_index = 2;



  for (int i = first_index; i < argc; +i) {
    if (argc[])
  }
}