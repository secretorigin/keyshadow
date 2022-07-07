// Copyright (c) 2022 Kandakov Danil (p2034 or the_lll_end)
// https://github.com/p2034



/**
 * @file
 * @brief tests and examples for KeyshadowFile
 */



#include "../src/keyshadow/keyshadow.h"



void mainloop() {
  std::string domain = "www.google.com";
  std::string fake_domain = "www.google.com";

  /* creating database */

  KeyshadowFile f1("testdata");
  f1.setPassword("password12345");
  f1.addLoginInfo(domain, "admin", "iamthebestadmin");
  f1.write();

  /* reading */

  KeyshadowFile f2("testdata");
  f2.read("password12345");
  f2.addLoginInfo(domain, "admin2", "iamthebestadmin12345");

  login_password_t* findeddata = f2.findLoginPassword(fake_domain);
  std::cout << "\t" + fake_domain + ":\n";
  for (size_t i = 0; i < findeddata->size(); ++i)
    std::cout << (*findeddata)[i].first << " " << (*findeddata)[i].second << std::endl;
  delete findeddata;

  findeddata = f2.findLoginPassword(domain);
  std::cout << "\t" + domain + ":\n";
  for (size_t i = 0; i < findeddata->size(); ++i)
    std::cout << (*findeddata)[i].first << " " << (*findeddata)[i].second << std::endl;
  delete findeddata;

  f2.removeNote(domain, 0);
  std::cout << "\tremove " + domain + "[0]:\n";

  findeddata = f2.findLoginPassword(domain);
  std::cout << "\t" + domain + ":\n";
  for (size_t i = 0; i < findeddata->size(); ++i)
    std::cout << (*findeddata)[i].first << " " << (*findeddata)[i].second << std::endl;
  delete findeddata;

  std::cout << "\tadd something\n";
  f2.addLoginInfo(domain + "0", "admin", "iamthebestadmin");
  f2.addLoginInfo(domain + "0", "admin", "iamthebestadmin");
  f2.addLoginInfo(domain + "1", "admin", "iamthebestadmin");
  f2.addLoginInfo(domain + "0", "admin", "iamthebestadmin");
  f2.addLoginInfo(domain + "1", "admin", "iamthebestadmin");
  f2.addLoginInfo(domain + "2", "admin", "iamthebestadmin");

  type_resource_t* alldata = f2.list();
  std::cout << "\t" + domain + ":\n";
  for (size_t i = 0; i < alldata->size(); ++i)
    std::cout << (*alldata)[i].first << " " << (*alldata)[i].second << std::endl;
  delete alldata;
}