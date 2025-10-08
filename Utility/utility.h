#ifndef UTILITY_H
#define UTILITY_H


#include <iostream>
#include <string>
using namespace std;


extern bool VOICE_ENABLED;

extern bool COLOR_ENABLED;


void sleepMS(int);


int clearScreen();


void pressToContinue(int);


string getEmailInput(string);

string getPasswordInput(const string &prompt);


void loadingScreen(string);


void exitWindow();


void speak(string);


int getIntInput(string);


void loadConfig();


void saveConfig(bool,bool);


void sleepIgnoreInput(int);

#endif