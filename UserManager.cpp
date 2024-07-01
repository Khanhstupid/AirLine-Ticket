#include "UserManager.h"

UserManager::UserManager() : loggedInUser(nullptr) {
	loadUsersFromFile("data/users.txt");
}

UserManager::~UserManager() {
	for (auto& user : users) {
		delete user.second;
	}
}

void UserManager::loadUsersFromFile(const string& filename) {
	ifstream infile(filename);
	if (!infile) {
		cerr << "Error opening users file for reading.\n";
		return;
	}
	
	string line;
	while (getline(infile, line)) {
		stringstream ss(line);
		string username, password, role;
		getline(ss, username, ',');
		getline(ss, password, ',');
		getline(ss, role, ',');

		users[username] = new User(username, password, role);

	}
	infile.close();
}

void UserManager::saveUsersToFile(const string& filename) {
	ofstream outFile(filename);
	
	if (!outFile) {
		cerr << "Error opening users file for writing.\n";
		return;
	}
	for (const auto& user : users) {
		outFile << user.first << "," << user.second->getPassword() << "," << user.second->getRole() << "\n";
	}
	outFile.close();
}

bool UserManager::login(const string& username, const string& password) {
	if (users.find(username) != users.end() && users[username]->getPassword() == password) {
		loggedInUser = users[username];
		cout << "Login successful.\n";
		return true;
	}
	cout << "Invalid username or password.\n";
	return false;
}

void UserManager::logout() {
	if (loggedInUser) {
		loggedInUser = nullptr;
		cout << "Logged out successfully.\n";
	}
	else {
		cout << "No user is currently logged in.\n";
	}
}

bool UserManager::isLoggedIn() const {
	return loggedInUser != nullptr;
}

User* UserManager::getLoggedInUser() const {
	return loggedInUser;
}
bool UserManager::registerUser(const string& username, const string& password, const string& role) {
	if (users.find(username) != users.end()) {
		cout << "Username already exists. Please choose a different username.\n";
		return false;
	}

	users[username] = new User(username, password, role);

	saveUsersToFile("data/users.txt");

	cout << "Registration successful. You can now log in with your new account.\n";

	return true;
}
