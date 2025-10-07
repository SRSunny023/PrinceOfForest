#include "login.h"
#include "authentication.h"
#include "colors.h"
#include "utility.h"
#include "main_menu.h"


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

void loginMenu(){
    
    string email,password,savedEmail,savedPassword,savedUsername;

    string command;

    bool valid = false;

    User person;

    do{

        clearScreen();

        cout << BGGREEN << RED << "╔═══════════════════════LOGIN═══════════════════════╗\n" << RESET;

        email = getEmailInput("Enter Your Email: ");

        if(!isEmailExist(email)){

            command = "Email Address Not Found. Create A New Account Or Try Again With Different Email!";
            
            cout << RED << command << RESET << endl;

            speak(command);

            continue;

        }

        password = getPasswordInput("Enter Your Password: ");

        ifstream file("Database/authentication.txt");

        bool found = false;

        while(file >> savedEmail >> savedPassword >> savedUsername){

            if(savedEmail == email && savedPassword == password){

                command = "Login Successfull!";

                loadingScreen("Login In Progress...");

                cout << RED << command << RESET << endl;

                speak(command);

                valid = true;

                found = true;

                file.close();

                break;

            }

        }

        if(!found){

            command = "Password Didn't Matched!";

            cout << RED << command << RESET << endl;

            speak(command);

        }
        
    }   while(!valid);
    
    if(valid){

        person.email = email;
        
        person.username = savedUsername;

        mainMenu(person);

    }

}