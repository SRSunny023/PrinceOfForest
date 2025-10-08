#include "authentication.h"
#include "colors.h"
#include "utility.h"
#include "main_menu.h"


#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using namespace std;




/********************************************************************************/
/* Function Name: loginMenu                                                     */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This will login User                                          */
/********************************************************************************/

void loginMenu(){
    
    string email,password,savedEmailEnc,savedPasswordEnc,savedUsernameEnc,savedUsername;

    string command;

    bool valid = false;

    User person;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do{

        clearScreen();

        cout << BGGREEN() << RED() << "╔═══════════════════════LOGIN═══════════════════════╗\n" << RESET();

        email = getEmailInput("Enter Your Email: ");

        if(email == "-")    return;

        if(!isEmailExist(email)){

            command = "Email Address Not Found. Create A New Account Or Try Again With Different Email!";
            
            cout << RED() << command << RESET() << endl;

            speak(command);

            if(!VOICE_ENABLED){

                #ifdef _WIN32
                    sleepMS(2000);
                    while (_kbhit()) _getch();
                #else
                    sleepIgnoreInput(2000);
                #endif

            }

            continue;

        }

        password = getPasswordInput("Enter Your Password: ");

        if(password == "-") return;

        ifstream file("Database/authentication.txt");

        bool found = false;

        while(file >> savedEmailEnc >> savedPasswordEnc >> savedUsernameEnc){

            string savedEmail = decryptFromHex(savedEmailEnc);
            string savedPassword = decryptFromHex(savedPasswordEnc);
            savedUsername = decryptFromHex(savedUsernameEnc);
            
            if(savedEmail == email && savedPassword == password){

                command = "Login Successfull!";

                loadingScreen("Login In Progress...");

                cout << RED() << command << RESET() << endl;

                speak(command);

                valid = true;

                found = true;

                file.close();

                if(!VOICE_ENABLED){

                    #ifdef _WIN32
                        sleepMS(2000);
                        while (_kbhit()) _getch();
                    #else
                        sleepIgnoreInput(2000);
                    #endif

                }

                break;

            }

        }

        if(!found){

            command = "Password Didn't Matched!";

            cout << RED() << command << RESET() << endl;

            speak(command);

            if(!VOICE_ENABLED){

                #ifdef _WIN32
                    sleepMS(2000);
                    while (_kbhit()) _getch();
                #else
                    sleepIgnoreInput(2000);
                #endif

            }

        }
        
    }   while(!valid);
    
    if(valid){

        person.email = email;
        
        person.username = savedUsername;

        saveSession(person.username);

        mainMenu(person);

    }

}