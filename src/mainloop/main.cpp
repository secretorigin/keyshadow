#include <iostream>

#include "command_processor.h"



int main (int argc, char* argv[]) {
  try {
    command_processor(argc, argv);
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}