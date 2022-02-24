#include "command_processor.h"

#include <exception>
#include <string>
#include <cstring>
#include <unistd.h>
#include <iostream>

#include "database/encrypted_file.h"
#include "../crypto/core/crc32.h"



std::string new_password_input() {
  std::string password = getpass("Password: ");
  
  std::string repeated_password = getpass("Repeat password: ");
  
  if (repeated_password.length() != password.length() || 
      memcmp(password.c_str(), repeated_password.c_str(), password.length()) != 0)
    throw std::invalid_argument("Passwords are not same.");

  return password;
}



std::string old_password_input() {
  return std::string(getpass("Password: "));
}



void add() {

}



void create(int argc, char* argv[]) {
  std::string file_name = "test.out";
  parsed_header main_info = {new aes_ecb, new pbkdf2_hmac_sha512, 0, 0, 0, nullptr};

  if ((argc - 1) % 2 != 0)
    throw std::invalid_argument("Invalid count of arguments.");

  for (int i = 1; i < argc; i += 2)
    if (argv[i] == "-f" || argv[i] == "-file")
      file_name = argv[i + 1];
    else if (argv[i] == "-a" || argv[i] == "-alg")
      if (argv[i + 1] == "AES") {
        delete main_info.c;
        main_info.c = new aes_ecb;
      } else {
        throw std::invalid_argument("Unknown cipher '" + std::string(argv[i + 1]) + "'.");
      }
    else if (argv[i] == "-h" || argv[i] == "-hash")
      if (argv[i + 1] == "SHA512") {
        delete main_info.hf;
        main_info.hf = new pbkdf2_hmac_sha512;
      } else {
        throw std::invalid_argument("Unknown hash function '" + std::string(argv[i + 1]) + "'.");
      }
    else
      throw std::invalid_argument("Invalid flag '" + std::string(argv[i]) + "'.");
  
  main_info.c->set(std::cin, std::cout);
  main_info.hf->set(std::cin, std::cout);

  std::string password = new_password_input();
  main_info.hash = crcdetail::compute(password.c_str(), password.length());

  size_t buff_size;
  char* buff = write_header(main_info, buff_size);
  write_file(file_name, buff_size, buff);
  delete buff;
}



void open(int argc, char* argv[]) {
  if (argc == 2)
    throw std::invalid_argument("Invalid command.");

  if (argv[2] == "-add")
    ;
  else if (argv[2] == "-del")
    ;
  else if (argv[2] == "-get")
    ;
  else if (argv[2] == "-ls")
    ;
  else if (argv[2] == "-info")
    ;
  else
    throw std::invalid_argument("Invalid command.");
}



void command_processor(int argc, char* argv[]) {
  if (argc == 1)
    throw std::invalid_argument("Invalid command.");

  if (argv[1][0] == '-') {
    create(argc, argv);
  } else {
    open(argc, argv);
  }
}