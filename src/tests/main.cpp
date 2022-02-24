#include <iostream>
#include <fstream>
#include <exception>

#include <unistd.h>

#include "crypto/crypto.h"



#define INPUT_BUFFER_SIZE 1024

/**
 * @brief get the line from input
 * 
 * @param [out] buff free buff of buff_size 
 * @param buff_size max size of input
 * @return size_t size of input
 */
size_t get_line(char* buff, size_t buff_size, char separator) {
  size_t i;
  for (i = 0; i < buff_size; i++)
    if (i > 0 && buff[i - 1] == separator)
      break;
    else
      std::cin.read((buff + i), 1);

  return i;
}



char* get_file(std::string path, size_t& file_size) {
  std::ifstream is;
  
  is.open(path);
  if (!is.is_open())
    throw std::invalid_argument("Can not create file: " + path + "!\n");

  is.seekg(0, std::ios::end);
  file_size = is.tellg();
  char* buff = new char[file_size];

  is.read(buff, file_size);

  is.close();
  if (!is.good())
    throw std::invalid_argument("Error occurred at writing time!\n");

  return buff;
}



int main (int argc, char* argv[]) {
  try {
    std::string file_name = "a.shadow";
    char command = 0;
    for (int i = 0; i < argc; ++i)
      if (argv[i][0] == '-') {
        if (std::strlen(argv[i]) == 1)
          throw std::invalid_argument("Error: Invalid command with single '-'.");

        if (argv[i] == "-f" || argv[i] == "-file") {
          if ((argc-1) == i)
            throw std::invalid_argument("Error: Invalid command with out file path after flag '-f'.");
          
        } else if (argv[i] == "-h" || argv[i] == "-help") {
          std::cout << "-f (-file) - add file\n\
                        -h (-help) - help" << std::endl;
        } else {
          throw std::invalid_argument("Error: Invalid command with flag '" + std::string(argv[i]) + "'.");
        }
      } else {

      }

    char* password = getpass("Password: ");
    std::cout << password  << " " << std::strlen(password) << std::endl;
  } catch(std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}