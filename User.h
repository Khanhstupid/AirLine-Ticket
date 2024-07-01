#pragma once
#include <iostream>
#include <string>
using namespace std;

class User {
private:
    string username;
    string password;
    string role;

public:
    User(const string& user, const string& pass, const string& r);

    // Getters
    string getUsername() const;
    string getPassword() const;
    string getRole() const;

};

