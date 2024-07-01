#include "User.h"
User::User(const string& user, const string& pass, const string& r)
    : username(user), password(pass), role(r) {}

// Getters
string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

string User::getRole() const {
    return role;
}

// Setters


