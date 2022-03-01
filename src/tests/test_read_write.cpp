#include <exception>
#include <string>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <functional>
#include <utility>

#include "../mainloop/database/encrypted_file.h"
#include "../crypto/core/crc32.h"




int main() {
  std::string path = "my_test.txt";
  std::string message = "Hello World!";
  std::string key = "ABCDEFU";

  // create rules
  parsed_encrypted_file file = {new aes_ecb, new pbkdf2_hmac_sha512, message.length(), 0, 0, new char[16]};
  std::cout << "Message: " << message << "\n Key: " << key << std::endl;
  
  // encrypt
  file.encrypted_data = file.c->encrypt(message.c_str(), message.length(), 
                                         reinterpret_cast<const uint8_t*>(key.c_str()), key.length(), 
                                         file.encrypted_data_size);
  (std::cout << "Encrypted data: ").write(file.encrypted_data, file.encrypted_data_size);

  size_t buff_size;
  char* buff = write_encrypted_file(file, buff_size);
  write_file(path, buff_size, buff);

  return 0;
}