// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include <iostream>
#include "../src/noteprocessor/writable.h"
#include "../src/noteprocessor/writablearray.h"
#include "../src/noteprocessor/writableloginnote.h"



void WritableArray_test() {
  WritableArray a, b;
  a.setName("first");
  for (size_t i = 0; i < 10; ++i)
    a.add(new WritableLoginNote("el " + std::to_string(i), "login", "password"));

  uint8_t* buff = new uint8_t[a.size()];
  a.write(buff);
  b.read(buff);

  std::cout << b.count() << std::endl;
  std::cout << b[9]->getName() << std::endl;
}