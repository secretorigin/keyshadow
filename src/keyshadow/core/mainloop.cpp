// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include "keyshadow.h"

#define PADDING_SYMBOLS "> "



void mainloop(std::string path, std::string password, bool exist) {
  KeyshadowFile file(path);
  if (exist)
    file.read(password);
  else
    file.setPassword(password);

  std::string command;
  while(true) {
    std::cout << PADDING_SYMBOLS;
    std::cin >> command;

    if (command == "add") {
      std::string login, password;
      std::cout << PADDING_SYMBOLS << "Resource: ";
      std::cin >> command;
      std::cout << PADDING_SYMBOLS << "Login: ";
      std::cin >> login;
      std::cout << PADDING_SYMBOLS << "Password: ";
      std::cin >> password;
      file.addLoginInfo(command, login, password);
      std::cout << "Data was added." << std::endl;
      continue;
    }

    if (command == "remove") {
      size_t index;
      std::cout << PADDING_SYMBOLS << "Resource: ";
      std::cin >> command;
      std::cout << PADDING_SYMBOLS << "Index: ";
      std::cin >> index;
      file.removeNote(command, index);
      std::cout << "Data was removed." << std::endl;
      continue;
    }

    if (command == "find") {
      std::cout << PADDING_SYMBOLS << "Resource: ";
      std::cin >> command;
      login_password_t* findeddata = file.findLoginPassword(command);
      std::cout << PADDING_SYMBOLS << "Found:\n";
      for (size_t i = 0; i < findeddata->size(); ++i)
        std::cout << PADDING_SYMBOLS << (*findeddata)[i].first << " " << (*findeddata)[i].second << std::endl;
      delete findeddata;
      continue;
    }

    if (command == "change password") {
      std::cout << PADDING_SYMBOLS << "New password: ";
      std::cin >> command;
      file.setPassword(command);
      std::cout << "Password was changed." << std::endl;
      continue;
    }
    
    if (command == "list") {
      type_resource_t* alldata = file.list();
      std::cout << PADDING_SYMBOLS << "All data:\n";
      for (size_t i = 0; i < alldata->size(); ++i)
        std::cout << PADDING_SYMBOLS << (*alldata)[i].first << " " << (*alldata)[i].second << std::endl;
      delete alldata;
      continue;
    }

    if (command == "save") {
      file.write();
      std::cout << "File was saved." << std::endl;
      continue;
    }

    if (command == "exit")
      std::cout << "...the end." << std::endl;
      break;
  }
}



int main(int argc, char* argv[]) {
  try {
    if (argc == 3)
      mainloop(argv[1], argv[2], true);
    else if (argc == 4 && std::string(argv[1]) == "-create")
      mainloop(argv[2], argv[3], false);
    else if (argc == 2 && std::string(argv[1]) == "-help")
      std::cout << "Description: ...\n"; // we need to add description
    else
      throw std::invalid_argument("Unknown parameters.");

  } catch(const std::exception& e) {
    std::cout << e.what() << "\n";
  }
}