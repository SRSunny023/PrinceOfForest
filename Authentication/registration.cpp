#include "registration.h"
#include "authentication.h"
#include "colors.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <fstream>
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

    do{

        clearScreen();

        cout << BGGREEN << RED << "╔═══════════════════════REGISTRATION═══════════════════════╗\n" << RESET;

        email = getEmailInput("Enter Your Email: ");

        if(isEmailExist(email)){

            command = "This Email Address Is Already Exist. Wether Login Or Enter Another Email!";
            
            cout << RED << command << RESET << endl;

            speak(command);

            continue;

        }

        password = getPasswordInput("Enter Your Password: ");

        confirmPassword = getPasswordInput("Confirm Your Password: ");

        if(password != confirmPassword){

            command = "Sorry! Password Didn't Matched! Try Again!";

            cout << RED << command << RESET << endl;

            speak(command);

            continue;

        }

        cout << "Enter Your Username: " << flush;

        speak("Enter Your Username");

        cin >> userName;

        if(userName == "*"){

            exitWindow();

        }

        loadingScreen("Registration In Progress...");

        command = "Registration Successfull!";
        
        cout << RED << command << RESET << endl;

        speak(command);

        valid = true;

    }   while(!valid);
    
    if(valid){

        file << email << " " << password << " " << userName << endl;

        file.close();

    }

}