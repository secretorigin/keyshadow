// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include <iostream>
#include "../src/noteprocessor/writable.h"
#include "../src/noteprocessor/writablearray.h"
#include "../src/noteprocessor/writableloginnote.h"



void WritableArray_test() {
  WritableArray a;
  a.setName("first");
  a.add(new WritableArray("second"));
  a.add(new WritableLoginNote("third", "login", "password"));
  uint8_t* buff = new uint8_t[a.size()];
  a.write(buff);

  for (size_t i = 0; i < a.size(); ++i)
    if (('a' <= buff[i] && buff[i] <= 'z'))
      std::cout << i << ": " << buff[i] << std::endl;
    else
      std::cout << i << ": " << "\\" << int(buff[i]) << "\\" << std::endl;

  a.read(buff);
}