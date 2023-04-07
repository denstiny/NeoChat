#pragma once
#include <string>
#include <unordered_map>
class User {
  public:
    // current user socket
    int socket;
    // user account
    std::string user_account;
    // user name
    std::string name;
    // user password
    std::string password;
    // key: user name,value: User
    std::unordered_map<std::string, User&> friends;
  public:
    User (int socket);
};
