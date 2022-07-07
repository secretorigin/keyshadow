// Copyright (c) 2021 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>



void letterByLetterOutput(std::string* str, int msec) {
  for (int i = 0; i < str->length(); i++) {
    std::cout << (*str)[i] << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(msec));
  }
}



int main() {
  try {
    // here tests
    
    std::string str = "It's ok!)";
    letterByLetterOutput(&str, 200);
    std::cout << std::endl;
  
  } catch(const std::exception& e) {
    std::cout << e.what() << "\n";
  }

	return 0;
}