#include "authentication.h"
#include "utility.h"
#include "colors.h"
#include "main_menu.h"


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;





/********************************************************************************/
/* Function Name: encrypt                                                       */
/*                                                                              */
/* Inputs       : String,String                                                 */
/*                                                                              */
/* Returns      : String                                                        */
/*                                                                              */
/* Note         : This will check wether email already exist or not             */
/*                plain text → XOR → encrypted bytes → hex → save               */
/********************************************************************************/

string encrypt(const string &data, const string key){

    string encryptedCode = data;

    for(size_t i = 0; i < encryptedCode.size(); ++i){

        encryptedCode[i] ^= key[i%key.size()];

    }

    return encryptedCode;

}



/********************************************************************************/
/* Function Name: toHex                                                         */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : String                                                        */
/*                                                                              */
/* Note         : This will convert to Hex                                      */
/********************************************************************************/

string toHex(const string &data){
    
    stringstream ss;
    
    for(unsigned char c : data){
        
        ss << hex << setw(2) << setfill('0') << (int)c;
    
    }
    
    return ss.str();

}



/********************************************************************************/
/* Function Name: fromHex                                                       */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : String                                                        */
/*                                                                              */
/* Note         : This will reconvert from Hex                                  */
/********************************************************************************/

string fromHex(const string &hex){
    
    string data;
    
    for(size_t i = 0; i < hex.size(); i += 2){
        
        unsigned int byte;
        
        sscanf(hex.substr(i, 2).c_str(), "%02X", &byte);
        
        data += static_cast<char>(byte);
    
    }
    
    return data;

}



/********************************************************************************/
/* Function Name: encryptToHex                                                  */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : String                                                        */
/*                                                                              */
/* Note         : This will encrypt and convert to hex                          */
/********************************************************************************/

string encryptToHex(const string &data) {
    
    return toHex(encrypt(data));

}



/********************************************************************************/
/* Function Name: decryptFromHex                                                */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : String                                                        */
/*                                                                              */
/* Note         : This will decrypt and convert from hex                        */
/*                read hex → bytes → XOR → original text                        */
/********************************************************************************/

string decryptFromHex(const string &hexData) {
    
    return encrypt(fromHex(hexData));

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

bool isEmailExist(string email){

    string savedEmailEnc, savedPassword, savedUsername;
    
    ifstream file("Database/authentication.txt");

    while(file >> savedEmailEnc >> savedPassword >> savedUsername){

        string savedEmail = decryptFromHex(savedEmailEnc);
        
        if(savedEmail == email){

            file.close();
            
            return true;

        }

    }

    file.close();

    return false;

}



/********************************************************************************/
/* Function Name: printAuthenticationMenu                                       */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This will print the menu of Authentication                    */
/********************************************************************************/

void printAuthenticationMenu(){

    clearScreen();

    cout << BGGREEN() << RED() << "╔═══════════════════════AUTHENTICATION═══════════════════════╗\n\n" << RESET();

    cout << BGGREEN() << BLUE() << "1. Registration\n\n2. Log In\n\n3. Reset Password\n\n4. Reset Username\n\n5. Exit\n\n" << RESET();

    cout << YELLOW() << "IN THIS GAME PRESS: * TO DIRECTLY EXIT THE GAME\n\n" << RESET();

    cout << YELLOW() << "IN THIS GAME PRESS: - TO GO BACK\n\n" << RESET();

    cout << BGGREEN() << RED() << "╚═══════════════════════AUTHENTICATION═══════════════════════╝\n\n" << RESET();


}



/********************************************************************************/
/* Function Name: authenticationMenu                                            */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : Bool                                                          */
/*                                                                              */
/* Note         : This is the menu of authentication                            */
/********************************************************************************/

void authenticationMenu(){
    
    int choice;

    string userName = loadSession();

    if(userName != ""){

        string savedEmail, savedPassword, savedUsername;
        
        User person;

        ifstream file("Database/authentication.txt");

        while(file >> savedEmail >> savedPassword >> savedUsername){

            string decryptedEmail = decryptFromHex(savedEmail);
            string decryptedPassword = decryptFromHex(savedPassword);
            string decryptedUsername = decryptFromHex(savedUsername);

            if(decryptedUsername == userName){

                person.email = decryptedEmail;

                person.username = decryptedUsername;

                mainMenu(person);

            }

        }

    }

    else{

        while(1){
        
            printAuthenticationMenu();

            choice = getIntInput("Enter Your Choice: ");

            if(choice == 1){

                registrationMenu();

            }

            else if(choice == 2){

                loginMenu();

            }

            else if(choice == 3){

                updatePasswordMenu();

            }

            else if(choice == 4){

                updateUsernameMenu();

            }

            else if(choice == 5){

                exitWindow();

            }

            else if(choice == -1){

                cout << RED() << "Back Is Not Allowed Here!" << RESET() << endl;

                speak("Back Is Not Allowed Here!");

                pressToContinue(0);

            }

            else{

                cout << RED() << "Invalid Input! Choose Between (1 - 5)!" << RESET() << endl;;

                speak("Invalid Input! Choose Between (1 - 5)");

                pressToContinue(0);

            }

        }

    }

}