#include "authentication.h"
#include "colors.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using namespace std;





/********************************************************************************/
/* Function Name: registrationMenu                                              */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This will register User                                       */
/********************************************************************************/

void registrationMenu(){

    ofstream file("Database/authentication.txt", ios::app);
    
    string email,password,confirmPassword,userName;

    string command;

    bool valid = false;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do{

        clearScreen();
        
        cout << BGGREEN() << RED() << "╔═══════════════════════REGISTRATION═══════════════════════╗\n" << RESET();
        
        email = getEmailInput("Enter Your Email: ");

        if(email == "-")    return;

        if(isEmailExist(email)){

            command = "This Email Address Is Already Exist. Wether Login Or Enter Another Email!";
            
            cout << RED() << command << RESET() << endl;

            speak(command);

            continue;

        }

        password = getPasswordInput("Enter Your Password: ");

        if(password == "-") return;

        confirmPassword = getPasswordInput("Confirm Your Password: ");

        if(confirmPassword == "-")  return; 

        if(password != confirmPassword){

            command = "Sorry! Password Didn't Matched! Try Again!";

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

        cout << "Enter Your Username: " << flush;

        speak("Enter Your Username");

        cin >> userName;

        if(userName == "*"){

            exitWindow();

        }

        if(userName == "-") return;

        loadingScreen("Registration In Progress...");

        command = "Registration Successfull!";
        
        cout << RED() << command << RESET() << endl;

        speak(command);

        valid = true;

        if(!VOICE_ENABLED){

            #ifdef _WIN32
                sleepMS(2000);
                while (_kbhit()) _getch();
            #else
                sleepIgnoreInput(2000);
            #endif

        }

    }   while(!valid);
    
    if(valid){
        
        file << encryptToHex(email) << " " << encryptToHex(password) << " " << encryptToHex(userName) << endl;

        file.close();

    }

}