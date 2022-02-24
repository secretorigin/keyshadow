#ifndef FILE_OPENER_H
#define FILE_OPENER_H

#include <string>



char* read_file(const std::string& path, size_t& data_size);

void write_file(const std::string& path, size_t data_size, const char* data);



#endif