// Copyright (c) 2021 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H



#include <string>



class TextProcessor {
public:
  TextProcessor() {
    extensionsNum = 8;
    extns = new extension[extensionsNum];

    extns[0] = {false, 10, '0', "numbers"};
    extns[1] = {false, 26, 'a', "lowercase"};
    extns[2] = {false, 26, 'A', "uppercase"};

    extns[3] = {false, 1, ' ', "space"};
    extns[4] = {false, 1, '_', "underscore"};
    extns[5] = {false, 1, '-', "hyphen"};
    extns[6] = {false, 1, '.', "dot"};
    extns[7] = {false, 1, '@', "at"};
  }

  // universal adder
  TextProcessor & add(std::string name) {
    size_t id;
    for (unsigned i = 0; i < extensionsNum; i++)
      if (extns[i].name == name)
        id = i;
    
    extns[id].status = true;
    count += extns[id].size;
    
    return *this;
  }

  // extension's functions
  TextProcessor & numbers() {
    extns[0].status = true;
    count += extns[0].size;
    
    return *this;
  }

  TextProcessor & lowercase() {
    extns[1].status = true;
    count += extns[1].size;
    
    return *this;
  }

  TextProcessor & uppercase() {
    extns[2].status = true;
    count += extns[2].size;
    
    return *this;
  }

  // generate random sequence
  std::string genrand(unsigned size) {
    std::string sequence(size, '0');

    for (size_t i = 0; i < size; i++) {
      size_t h = 0;
      size_t index = rand() % count;

      for (size_t j = 0; j < extensionsNum; j++) {
        if (extns[j].status == true) {
          if (h <= index && index < h + extns[j].size) {
            sequence[i] = extns[j].firstSymbol + (index - h);
            break;
          }
          h += extns[j].size;
        }
      }
    }
    
    for (size_t i = 0; i < extensionsNum; i++)
      extns[i].status = false;
    count = 0;

    return sequence;
  }



  // check std::string for all symbols in all extensions
  bool check(std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
      // try to find in all entensions
      bool isok = false;
      for (size_t j = 0; j < extensionsNum; j++)
        if (extns[j].status == true)
          if (extns[j].firstSymbol <= str[i] && 
              str[i] < (extns[j].firstSymbol + extns[j].size)) {
            isok = true;
            break;
          }
      // did not find this in extensions
      if (isok == false)
        return false;
    }

    for (size_t i = 0; i < extensionsNum; i++)
      extns[i].status = false;
    count = 0;

    return true;
  }



  // index of first symbol of the string which is in the extensions
  // -1 if there isn't
  int find(std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
      bool isok = false;
      for (size_t j = 0; j < extensionsNum; j++)
        if (extns[j].status == true)
          if (extns[j].firstSymbol <= str[i] && 
              str[i] < (extns[j].firstSymbol + extns[j].size))
            return i;
    }

    for (size_t i = 0; i < extensionsNum; i++)
      extns[i].status = false;
    count = 0;

    return -1;
  }


  // get count of symbols from extensions
  int countin(std::string str) {
    int c = 0;

    for (size_t i = 0; i < str.length(); i++)
      for (size_t j = 0; j < extensionsNum; j++)
        if (extns[j].status == true)
          if (extns[j].firstSymbol <= str[i] && 
              str[i] < (extns[j].firstSymbol + extns[j].size))
            ++c;

    for (size_t i = 0; i < extensionsNum; i++)
      extns[i].status = false;
    count = 0;

    return c;
  }



  ~TextProcessor() {
    delete[] extns;
  }

private:
  struct extension {
    bool status;
    unsigned size;
    char firstSymbol;
    std::string name;
  };
  typedef struct extension extension;

  extension * extns;
  size_t extensionsNum;
  
  size_t count = 0;
};



#endif