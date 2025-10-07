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

#endif