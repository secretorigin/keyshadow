// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#ifndef FORTEST_FUNCIONS_H
#define FORTEST_FUNCIONS_H



void printArray(const uint8_t* data, uint32_t dataSize) {
  for(size_t i = 0; i < dataSize; ++i)
    if (('a' <= data[i] && data[i] <= 'z') || ('A' <= data[i] && data[i] <= 'Z') ||
        data[i] == '.' || data[i] == ' ' || data[i] == ',')
      std::cout << data[i];
    else
      std::cout << "\\" << int(data[i]);
  std::cout << std::endl;
}



#endif