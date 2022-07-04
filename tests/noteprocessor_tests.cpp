// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include <iostream>
#include "../src/noteprocessor/writable.h"
#include "../src/noteprocessor/writablearray.h"



void WritableArray_test() {
  WritableArray a;

  a.setName("superarray");
  uint8_t* buff = new uint8_t[a.size()];
  a.write(buff);
}