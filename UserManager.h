#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "User.h"

using namespace std;

class UserManager {
private:
    unordered_map<string, User*> users;
    User* loggedInUser;

public:
    UserManager();
    ~UserManager();

    void loadUsersFromFile(const string& filename);
    void saveUsersToFile(const string& filename);

    bool login(const string& username, const string& password);
    void logout();

    bool isLoggedIn() const;
    User* getLoggedInUser() const;
    bool registerUser(const string& username, const string& password, const string& role);
};

