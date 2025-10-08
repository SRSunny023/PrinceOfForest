#include "authentication.h"
#include "utility.h"
#include "colors.h"




#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
using namespace std;





/********************************************************************************/
/* Function Name: updateUsername                                                */
/*                                                                              */
/* Inputs       : String,String                                                 */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is the function To Update Username                       */
/********************************************************************************/

void updateUsername(const string &emailToUpdate, const string &newUsername){

    ifstream file("Database/authentication.txt");

    vector<User> users;

    string line;

    while(getline(file,line)){

        istringstream iss(line);

        string encEmail, encPass, encUsername;

        User u;

        iss >> encEmail >> encPass >> encUsername;

        u.email = decryptFromHex(encEmail);

        u.password = decryptFromHex(encPass);

        u.username = decryptFromHex(encUsername);

        users.push_back(u);

    }

    file.close();

    for(User &u : users){

        if(u.email == emailToUpdate){

            u.username = newUsername;

            break;

        }

    }

    ofstream out("Database/authentication.txt", ios::trunc);

    for(User &u : users){
        
        out << encryptToHex(u.email) << " " << encryptToHex(u.password) << " " << encryptToHex(u.username) << "\n";
    
    }
    
    out.close();

}



/********************************************************************************/
/* Function Name: printUpdateUserNameMenu                                       */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This will print the menu of Update Username                   */
/********************************************************************************/

void printUpdateUserNameMenu(){

    clearScreen();

    cout << BGGREEN() << RED() << "╔═══════════════════════UPDATE USERNAME═══════════════════════╗\n\n" << RESET();

}



/********************************************************************************/
/* Function Name: updateUsernameMenu                                            */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is the menu of Update Username                           */
/********************************************************************************/

void updateUsernameMenu(){

    string username;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    do{

        printUpdateUserNameMenu();

        string email = getEmailInput("Enter Your Email Address: ");

        if(email == "-"){

            return;

        }

        if(!isEmailExist(email)){

            cout << RED() << "Email Not Found!" << RESET();

            cout << flush;

            speak("Email Not Found");

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

        cout << "Enter Your New Username: ";

        speak("Enter Your New Username");

        cin >> username;

        if(username == "*") exitWindow();

        if(username == "-") return;

        updateUsername(email,username);

        loadingScreen("Username Updating In Progress...");

        cout << "Username Successfully Updated" << endl;

        speak("Username Successfully Updated");

        if(!VOICE_ENABLED){

            #ifdef _WIN32
                sleepMS(2000);
                while (_kbhit()) _getch();
            #else
                sleepIgnoreInput(2000);
            #endif

        }

        return;

    }   while(true);

}



/********************************************************************************/
/* Function Name: updatePassword                                                */
/*                                                                              */
/* Inputs       : String,String                                                 */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This will update the password                                 */
/********************************************************************************/

void updatePassword(const string &emailToUpdate, const string &newPassword){

    ifstream file("Database/authentication.txt");

    vector<User> users;

    string line;

    while(getline(file,line)){

        istringstream iss(line);

        string encEmail, encPass, encUsername;

        User u;

        iss >> encEmail >> encPass >> encUsername;

        u.email = decryptFromHex(encEmail);

        u.password = decryptFromHex(encPass);

        u.username = decryptFromHex(encUsername);

        users.push_back(u);

    }

    file.close();

    for(User &u : users){

        if(u.email == emailToUpdate){

            u.password = newPassword;

            break;

        }

    }

    ofstream out("Database/authentication.txt", ios::trunc);

    for(User &u : users){
        
        out << encryptToHex(u.email) << " " << encryptToHex(u.password) << " " << encryptToHex(u.username) << "\n";
    
    }
    
    out.close();

}



/********************************************************************************/
/* Function Name: printUpdatePasswordMenu                                       */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This will print the update password menu                      */
/********************************************************************************/

void printUpdatePasswordMenu(){

    clearScreen();

    cout << BGGREEN() << RED() << "╔═══════════════════════UPDATE PASSWORD═══════════════════════╗\n\n" << RESET();

}



/********************************************************************************/
/* Function Name: updatePasswordMenu                                            */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is the update password menu                              */
/********************************************************************************/

void updatePasswordMenu(){

    string password;

    string email;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    do{

        printUpdatePasswordMenu();

        string email = getEmailInput("Enter Your Email Address: ");

        if(email == "-"){

            return;

        }

        if(!isEmailExist(email)){

            cout << "Email Not Found!";

            cout << flush;

            speak("Email Not Found");

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

        password = getPasswordInput("Enter Your New Password: ");

        if(password == "-") return;

        updatePassword(email,password);

        loadingScreen("Password Updating In Progress...");

        cout << "Password Successfully Updated" << endl;

        speak("Password Successfully Updated");

        if(!VOICE_ENABLED){

            #ifdef _WIN32
                sleepMS(2000);
                while (_kbhit()) _getch();
            #else
                sleepIgnoreInput(2000);
            #endif

        }

        return;

    }   while(true);

}