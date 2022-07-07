// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include "keyshadow.h"



void KeyshadowFile::getKey(std::string password) {
  if (key != nullptr)
    delete[] key;

  this->keySize = 32;
  this->key = (uint8_t*) new uint8_t[keySize];

  // generate key from password
  // this must be created using sha256 and pbkdf2
  for (size_t i = 0; i < keySize; ++i)
    if (password.length() <= i) {
      key[i] = '0';
    } else {
      key[i] = password[i];
    }
}



KeyshadowFile::KeyshadowFile() : array("keyshadow_database") {}

KeyshadowFile::KeyshadowFile(std::string path) : array("keyshadow_database") {
  this->path = path;
}



void KeyshadowFile::setPassword(std::string password) {
  getKey(password);
}

void KeyshadowFile::setPath(std::string path) {
  this->path = path;
}



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                                           note management
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/**
 * @brief add new login info to the file
 * 
 * @param [in] resource name of the resource, which login info you want to add
 * @param [in] login login to your account
 * @param [in] password password for your account
 */
void KeyshadowFile::addLoginInfo(std::string resource, std::string login, std::string password) {
  array.add(new WritableLoginNote(resource, login, password));
}



void KeyshadowFile::removeNote(std::string resource, size_t index) {
  size_t current_index = 0;

  for (size_t i = 0; i < array.count(); ++i)
    if (array[i]->getName() == resource) {
      if (current_index == index)
        array.remove(i);
      else
        ++current_index;
    }
}



/**
 * @brief get list of all login info for this resource
 * 
 * @param [in] resource name of the resource, which login info you want to see
 */
login_password_t* KeyshadowFile::findLoginPassword(std::string resource) {
  login_password_t* info = (login_password_t*) new login_password_t;

  for (size_t i = 0; i < array.count(); ++i)
    if (array[i]->getName() == resource) {
      if (array[i]->code() == 11)
        info->push_back(std::make_pair(
          reinterpret_cast<WritableLoginNote*>(array[i])->getLogin(), 
          reinterpret_cast<WritableLoginNote*>(array[i])->getPassword()
        ));
      else
        throw std::invalid_argument("Unknown type of note (" + std::to_string(array[i]->code()) + ")\n" + 
                                    "Update your application, or contact developers.");
    }

  return info;
}



/**
 * @brief get full list of notes
 */
type_resource_t* KeyshadowFile::list() {
  type_resource_t* info = (type_resource_t*) new type_resource_t;

  for (size_t i = 0; i < array.count(); ++i) {
    if (array[i]->code() == 11)
      info->push_back(std::make_pair("Login-Password", array[i]->getName()));
    else
      throw std::invalid_argument("Unknown type of note (" + std::to_string(array[i]->code()) + ")\n" + 
                                  "Update your application, or contact developers.");
  }

  return info;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                                           file management
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/**
 * @brief read data from encrypted file, and saving it in this object
 * 
 * @param [in] password password for opening encrypted file
 */
void KeyshadowFile::read(std::string password) {
  getKey(password);

  uint8_t* data;
  encfile file(this->keySize);
  file.decrypt(this->path, this->key, &data);

  this->array.read(data);
  if (array.getName() != "keyshadow_database")
    throw std::invalid_argument("This is not keyshadow database");

  delete[] data;
}



/**
 * @brief writing data from this object in readed file
 */
void KeyshadowFile::write() {
  uint32_t dataSize = this->array.size();
  uint8_t* data = (uint8_t*) new uint8_t*[dataSize];
  this->array.WritableArray::write(data);
  
  encfile file(keySize);
  file.encrypt(this->path, key, data, dataSize);
}




KeyshadowFile::~KeyshadowFile() {
  if (key != nullptr)
    delete[] key;
}