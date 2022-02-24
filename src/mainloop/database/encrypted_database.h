#ifndef ENCRYPTED_DATABASE_H
#define ENCRYPTED_DATABASE_H

#include "../../crypto/ciphers/cipher.h"
#include "../../crypto/hash_functions/hash_function.h"

#include <fstream>
#include <string>



struct header {
  cipher* c;
  hash_function* hf;
  
};


class EncryptedDB {
public:

private:

};



#endif