#include "authentication.h"
#include "utility.h"
#include "colors.h"
#include "registration.h"
#include "login.h"


#include <iostream>
#include <string>
#include <fstream>
using namespace std;



/********************************************************************************/
/* Function Name: isEmailExist                                                  */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : Bool                                                          */
/*                                                                              */
/* Note         : This will check wether email already exist or not             */
/********************************************************************************/

bool isEmailExist(string email){

    string savedEmail, savedPassword, savedUsername;
    
    ifstream file("Database/authentication.txt");

    while(file >> savedEmail >> savedPassword >> savedUsername){

        if(savedEmail == email){

            return true;

        }

    }

    return false;

}



/********************************************************************************/
/* Function Name: isEmailExist                                                  */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : Bool                                                          */
/*                                                                              */
/* Note         : This will check wether email already exist or not             */
/********************************************************************************/

void printAuthenticationMenu(){

    clearScreen();

    cout << BGGREEN << RED << "╔═══════════════════════AUTHENTICATION═══════════════════════╗\n\n" << RESET;

    cout << BGGREEN << BLUE << "1. Registration\n\n2. Log In\n\n3. Reset Password\n\n4. Reset Username\n\n5. Exit\n\n" << RESET;

    cout << BGGREEN << RED << "╚═══════════════════════AUTHENTICATION═══════════════════════╝\n\n" << RESET;


}



/********************************************************************************/
/* Function Name: isEmailExist                                                  */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : Bool                                                          */
/*                                                                              */
/* Note         : This will check wether email already exist or not             */
/********************************************************************************/

void authenticationMenu(){
    
    int choice;
    
    while(1){

        printAuthenticationMenu();

        cout << "Enter Your Choice: ";

        speak("Enter Your Choice");

        cin >> choice;

        if(choice == 1){

            registrationMenu();

        }

        else if(choice == 2){

            loginMenu();

        }

        else if(choice == 3){

            cout << "Under Development!\n";
            
            speak("Under Development\n");

            pressToContinue();

        }

        else if(choice == 4){

            cout << "Under Development!\n";
            
            speak("Under Development\n");

            pressToContinue();

        }

        else if(choice == 5){

            exitWindow();

        }

        else{

            cout << "Invalid Input! Choose Between (1 - 5)!\n";

            speak("Invalid Input! Choose Between (1 - 5)");

            pressToContinue();

        }

    }

}