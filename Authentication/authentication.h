#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
using namespace std;

struct User{

    string email,username,password;

};


bool isEmailExist(string);

void authenticationMenu();

void printAuthenticationMenu();

string encrypt(const string &data, const string key = "gjeiog*(#^(*QofhFui@*($&6484165486)))");

string encryptToHex(const string &data);

string decryptFromHex(const string &hexData);

void loginMenu();

void registrationMenu();

void saveSession(const string &username);

string loadSession();

void clearSession();

void updateUsernameMenu();

void updatePasswordMenu();

#endif