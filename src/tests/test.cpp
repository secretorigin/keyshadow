#include <iostream>

#include <filesystem>



int main () {
  std::string s = "README.m";

  std::cout << std::filesystem::exists(s) << std::endl;

  return 0;
}