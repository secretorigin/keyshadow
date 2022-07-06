// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

// encprocessor
#include "../encprocessor/core/encdata.h"
#include "../encprocessor/core/encfile.h"

// noteprocessor
#include "../noteprocessor/writable.h"
#include "../noteprocessor/writablearray.h"
#include "../noteprocessor/writableloginnote.h"


using logininfo_t = std::vector<std::pair<std::string, std::string>>;


    
class KeyshadowFile {
private:
  WritableArray array;
  std::string path;
  uint32_t keySize;
  uint8_t* key;

  void getKey(std::string password) {
    this->keySize = 32;
    this->key = (uint8_t*) new uint8_t[keySize];

    // generate key from password
    // this must be created using sha256 and pbkdf2
    for (size_t i = 0; i < keySize; ++i) {
      if (password.length() <= i) {
        key[i] = '0';
      } else {
        key[i] = password[i];
      }
    }
  }

public:
  KeyshadowFile() : array("keyshadow_database") {}
  KeyshadowFile(std::string path) {
    this->path = path;
  }

  void setPath(std::string path) {
    this->path = path;
  }

  // notes
  void addLoginInfo(std::string resource, std::string login, std::string password) {
    array.add(new WritableLoginNote(resource, login, password));
  }

  logininfo_t* find(std::string resource) {
    logininfo_t* info = (logininfo_t*) new logininfo_t;

    for (size_t i = 0; i < array.count(); ++i) {
      if (array[i]->getName() == resource)
        info->push_back(std::make_pair(
          reinterpret_cast<WritableLoginNote*>(array[i])->getLogin(), 
          reinterpret_cast<WritableLoginNote*>(array[i])->getPassword()
        ));
    }

    return info;
  }

  // file
  void read(std::string password) {
    getKey(password);

    uint8_t* data;
    encfile file(this->keySize);
    file.decrypt(this->path, this->key, &data);

    this->array.read(data);
    if (array.getName() != "keyshadow_database")
      throw std::invalid_argument("Thsi is not keyshadow database");

    delete[] data;
  }

  void write() {
    uint32_t dataSize = this->array.size();
    uint8_t* data = (uint8_t*) new uint8_t*[dataSize];
    this->array.write(data);
    
    encfile file(keySize);
    file.encrypt(this->path, key, data, dataSize);
  }

  ~KeyshadowFile() {
    if (key != nullptr)
      delete[] key;
  }
};



void mainloop() {
  std::cout << "mainloop" << std::endl;
}