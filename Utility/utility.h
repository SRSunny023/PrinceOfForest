#ifndef UTILITY_H
#define UTILITY_H


#include <iostream>
#include <string>
using namespace std;


void sleepMS(int);


int clearScreen();


void pressToContinue();


string getEmailInput(string);

string getPasswordInput(string);


void loadingScreen(string);


void exitWindow();


void speak(string);


#endif