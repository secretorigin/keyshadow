#include "file_opener.h"

#include <fstream>



char* read_file(const std::string& path, size_t& data_size) {
  std::ifstream is;
  
  is.open(path, std::ios::binary);
  if (!is.is_open())
    throw std::invalid_argument("Can not create file: " + path + "!\n");

  is.seekg(0, std::ios::end);
  data_size = is.tellg();
  char* data = new char[data_size];

  is.read(data, data_size);

  is.close();
  if (!is.good())
    throw std::invalid_argument("Error occurred at writing time!\n");

  return data;
}



void write_file(const std::string& path, size_t data_size, const char* data) {
  std::ofstream os;
  
  os.open(path, std::ios::binary);
  if (!os.is_open())
    throw std::invalid_argument("Can not create file: " + path + "!\n");

  os.write(data, data_size);

  os.close();
  if (!os.good())
    throw std::invalid_argument("Error occurred at writing time!\n");
}