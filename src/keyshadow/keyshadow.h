// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#ifndef KEYSHADOW_H
#define KEYSHADOW_H



#include <string>

// encprocessor
#include "../encprocessor/core/encfile.h"

// noteprocessor
#include "../noteprocessor/writablearray.h"
#include "../noteprocessor/writableloginnote.h"



using login_password_t = std::vector<std::pair<std::string, std::string>>;
using type_resource_t = std::vector<std::pair<std::string, std::string>>;

    
class KeyshadowFile {
private:
  WritableArray array;
  std::string path;
  uint32_t keySize;
  uint8_t* key = nullptr;

  void getKey(std::string password);

public:
  KeyshadowFile();
  KeyshadowFile(std::string path);

  // init
  void setPassword(std::string password);
  void setPath(std::string path);

  // note management
  void addLoginInfo(std::string resource, std::string login, std::string password);
  void removeNote(std::string resource, size_t index);
  login_password_t* findLoginPassword(std::string resource);
  type_resource_t* list();

  // file management
  void read(std::string password);
  void write();

  ~KeyshadowFile();
};



#endif