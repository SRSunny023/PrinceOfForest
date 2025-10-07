#include "main_menu.h"
#include "authentication.h"
#include "utility.h"


#include <iostream>
#include <string>
using namespace std;


void mainMenu(User person){

    clearScreen();

    cout << person.email << endl;

    cout << person.username << endl;

    pressToContinue();

    exitWindow();

}