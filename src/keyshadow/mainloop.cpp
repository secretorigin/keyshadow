// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



#include "keyshadow.h"



void mainloop(std::string path, std::string password, bool exist) {
  KeyshadowFile file(path);
  if (exist)
    file.read(password);
  else
    file.setPassword(password);

  std::string command;
  while(true) {
    std::cin >> command;

    if (command == "add") {
      std::string login, password;
      std::cout << "Resource: ";
      std::cin >> command;
      std::cout << "Login: ";
      std::cin >> login;
      std::cout << "Password: ";
      std::cin >> password;
      file.addLoginInfo(command, login, password);
    }

    if (command == "remove") {
      size_t index;
      std::cout << "Resource: ";
      std::cin >> command;
      std::cout << "Index: ";
      std::cin >> index;
      file.removeNote(command, index);
    }

    if (command == "find") {
      std::cout << "Resource: ";
      std::cin >> command;
      login_password_t* findeddata = file.findLoginPassword(command);
      std::cout << "Found:\n";
      for (size_t i = 0; i < findeddata->size(); ++i)
        std::cout << (*findeddata)[i].first << " " << (*findeddata)[i].second << std::endl;
      delete findeddata;
    }

    if (command == "change password") {
      std::cout << "New password: ";
      std::cin >> command;
      file.setPassword(command);
    }
    
    if (command == "list") {
      type_resource_t* alldata = file.list();
      std::cout << "All data:\n";
      for (size_t i = 0; i < alldata->size(); ++i)
        std::cout << (*alldata)[i].first << " " << (*alldata)[i].second << std::endl;
      delete alldata;
      continue;
    }

    if (command == "save") {
      file.write();
      continue;
    }

    if (command == "exit")
      break;
  }
}



int main(int argc, char* argv[]) {
  try {
    if (argc == 3) {
      std::cout << "Open" << std::endl;
      mainloop(argv[1], argv[2], true);
    } else if (argc == 4 && argv[1] == "-create") { // here is the problem
      std::cout << "Create" << std::endl;
      mainloop(argv[1], argv[2], false);
    } else {
      throw std::invalid_argument("Unknown parameters.");
    }

  } catch(const std::exception& e) {
    std::cout << e.what() << "\n";
  }
}