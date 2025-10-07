#include "utility.h"
#include "colors.h"



#include <iostream>
#include <cstdlib>



// Cross-Platform Library Header

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
#endif



using namespace std;





/********************************************************************************/
/* Function Name: getch                                                         */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : Char                                                          */
/*                                                                              */
/* Note         : This is getch function for ubuntu                             */
/********************************************************************************/

#ifndef _WIN32

char getch(){

    char buf = 0;

    struct termios old = {0};

    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");

    old.c_lflag &= ~ICANON;

    old.c_lflag &= ~ECHO;

    old.c_cc[VMIN] = 1;

    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");

    if (read(0, &buf, 1) < 0) perror("read()");

    old.c_lflag |= ICANON;

    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");

    return buf;

}
#endif



/********************************************************************************/
/* Function Name: sleepMS                                                       */
/*                                                                              */
/* Inputs       : Int                                                           */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is sleep function which is Cross-Platform                */
/********************************************************************************/

void sleepMS(int miliseconds){

    #ifdef _WIN32
        Sleep(miliseconds);
    #else
        usleep(miliseconds * 1000);
    #endif

}



/********************************************************************************/
/* Function Name: clearScreen                                                   */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : Int                                                           */
/*                                                                              */
/* Note         : This will clear the console or terminal screen completely     */
/********************************************************************************/

int clearScreen(){

    #ifdef _WIN32
        system("cls");
    #else
        cout << "\033[H\033[J";
    #endif
        return 0;

}



/********************************************************************************/
/* Function Name: pressToContinue                                               */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This will tell user to press to continue the game             */
/********************************************************************************/

void pressToContinue(){

    cout << "Enter Any Key To Continue... ";

    speak("Enter Any Key To Continue");

    cin.ignore();

    cin.get();

}



/********************************************************************************/
/* Function Name: getEmailInput                                                 */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : String                                                        */
/*                                                                              */
/* Note         : This is Email Input Function                                  */
/********************************************************************************/

string getEmailInput(string prompt){

    string email;

    string command;

    bool valid = false;

    do{

        cout << prompt;

        speak(prompt);

        cin >> email;

        if(email == "*"){

            exitWindow();

        }

        size_t atPos = email.find('@');

        size_t atLastPos = email.rfind('@');

        if(atPos == string::npos || atPos != atLastPos){

            command = "Invalid Email! Only One @ Allowed In Email!";
            
            cout << RED << command << RESET << endl;

            speak(command);

            continue;

        }

        string domain = email.substr(atPos+1);
        
        size_t dotPos = domain.find('.');

        if(dotPos == string::npos){

            command = "Invalid Email! Must Have At Least One Dot After @";
            
            cout << RED << command << RESET << endl; 

            speak(command);

            continue;

        }

        if(domain.back() == '.'){
            
            command = "Invalid Email! Dot Cannot Be The Last Character. Try Again!";
            
            cout << RED << command << RESET << endl;

            speak(command);

            continue;

        }

        valid = true;

    }   while(!valid);
    
    return email;

}



/********************************************************************************/
/* Function Name: getPasswordInput                                              */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : String                                                        */
/*                                                                              */
/* Note         : This is Password Input Function                               */
/********************************************************************************/

string getPasswordInput(string prompt){
    
    string password;

    string command;
    
    char ch;

    cout << prompt;
    
    speak(prompt);

    while (true){
        
        ch = getch();

        if(ch == '\n' || ch == '\r'){
            
            cout << endl;
            
            break;
        
        }
        
        else if(ch == 127 || ch == 8){
            
            if (!password.empty()) {
                
                cout << "\b \b";
                
                password.pop_back();
            
            }
        
        }
        
        else{
            
            password.push_back(ch);
            
            cout << '*';
        
        }
    
    }

    if(password == "*"){
        
        exitWindow();
    
    }

    if(password.length() < 8){
        
        command = "Invalid Password! Must be at least 8 characters!";
        
        cout << endl << RED << command << RESET << endl;
        
        speak(command);
        
        return getPasswordInput(prompt);
    
    }

    return password;

}



/********************************************************************************/
/* Function Name: loadingScreen                                                 */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is Loading Function Which Will Show The Loading Animation*/
/********************************************************************************/

void loadingScreen(string prompt){

    int x = 0;

    speak(prompt);

    do{

        clearScreen();

        cout << prompt << endl;

        for(int i=0; i<=x; i++){

            cout << "█";

        }

        cout << flush;

        sleepMS(10);
        
        x++;

    }   while(x!=50);

    cout << endl;

}



/********************************************************************************/
/* Function Name: exitWindow                                                    */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is the exit function. This Will Terminate The Program    */
/********************************************************************************/

void exitWindow(){

    clearScreen();

    loadingScreen("Game Exitting In Progress...");

    cout << "Game Successfully Exitted!" << endl;

    speak("Game Successfully Exitted!");

    exit(0);

}



/********************************************************************************/
/* Function Name: speak                                                         */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is convert Text To Speech Which is Cross Platform        */
/********************************************************************************/

void speak(string text){

    #ifdef _WIN32

        string command = "PowerShell -Command \"Add-Type -AssemblyName System.Speech; "
                         "(New-Object System.Speech.Synthesis.SpeechSynthesizer).Speak('" + text + "');\"";
        
        system(command.c_str());

    #else

        string command = "espeak \"" + text + "\"";
        
        system(command.c_str());
    
    #endif

}