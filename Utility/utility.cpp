#include "utility.h"
#include "authentication.h"
#include "colors.h"



#include <iostream>
#include <cstdlib>
#include <limits>
#include <fstream>



// Cross-Platform Library Header

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
#endif



using namespace std;


bool VOICE_ENABLED = true;

bool COLOR_ENABLED = true;




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

void pressToContinue(int a){

    cout << "Enter Any Key To Continue... ";

    speak("Enter Any Key To Continue");

    if(a == 0){

        cin.ignore();

    }

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

string getEmailInput(string prompt) {
    
    string email;
    
    string command;
    
    bool valid = false;

    do{
        
        cout << prompt;
        
        speak(prompt);
        
        getline(cin, email);

        if (email == "*") exitWindow();
        
        if (email == "-") return email;

        email.erase(0, email.find_first_not_of(' '));
        
        email.erase(email.find_last_not_of(' ') + 1);

        if(email.find(' ') != string::npos){
            
            command = "Invalid Email! No spaces allowed in email!";
            
            cout << RED() << command << RESET() << endl;
            
            speak(command);
            
            continue;
        
        }

        size_t atPos = email.find('@');
        
        size_t atLastPos = email.rfind('@');
        
        if(atPos == string::npos || atPos != atLastPos){
            
            command = "Invalid Email! Only one @ allowed!";
            
            cout << RED() << command << RESET() << endl;
            
            speak(command);
            
            continue;
        
        }

        if(atPos == 0 || atPos == email.length() - 1){
            
            command = "Invalid Email! Must have something before and after @!";
            
            cout << RED() << command << RESET() << endl;
            
            speak(command);
            
            continue;
        
        }

        string domain = email.substr(atPos + 1);

        size_t dotPos = domain.find('.');
        
        if(dotPos == string::npos){
            
            command = "Invalid Email! Must have at least one dot after @!";
            
            cout << RED() << command << RESET() << endl;
            
            speak(command);
            
            continue;
        
        }

        if(domain.front() == '.' || domain.back() == '.'){
            
            command = "Invalid Email! Dot cannot be the first or last character after @!";
            
            cout << RED() << command << RESET() << endl;
            
            speak(command);
            
            continue;
        
        }

        if(domain.find("..") != string::npos){
            
            command = "Invalid Email! Domain cannot contain consecutive dots!";
            
            cout << RED() << command << RESET() << endl;
            
            speak(command);
            
            continue;
        
        }

        size_t lastDot = domain.rfind('.');
        
        string tld = domain.substr(lastDot + 1);
        
        if(tld.length() < 2){
            
            command = "Invalid Email! Domain extension must be at least 2 characters (e.g., .com, .org)";
            
            cout << RED() << command << RESET() << endl;
            
            speak(command);
            
            continue;
        
        }

        valid = true;

    } while (!valid);

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

string getPasswordInput(const string &prompt){
    
    string password;
    
    char ch;

    cout << prompt;

    speak(prompt);
    
    cout.flush();

#ifdef _WIN32
    
    while (true) {
        
        ch = _getch();

        if(ch == '\r' || ch == '\n'){
            
            cout << endl;
            
            break;
        
        }
        
        else if (ch == 8){
            
            if(!password.empty()){
                
                cout << "\b \b";
                
                password.pop_back();
            
            }
        }
        
        else{
            
            password.push_back(ch);
            
            cout << '*';
        
        }
    
    }

#else

    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;

    newt.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while(true){
        
        ch = getchar();

        if(ch == '\n' || ch == '\r'){
            
            cout << endl;
            
            break;
        
        }
        
        else if(ch == 127 || ch == 8){
            
            if(!password.empty()){
                
                cout << "\b \b";
                
                password.pop_back();
            
            }
        
        }
        
        else{
            
            password.push_back(ch);
            
            cout << '*';
            
            cout.flush();
        
        }
    
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

#endif

    if(password == "*"){
        
        exitWindow();
    
    }

    if(password == "-"){

        return password;

    }

    if(password.length() < 8){
        
        cout << RED() << "Invalid Password! Must be at least 8 characters!" << RESET() << endl;

        speak("Invalid Password! Must be at least 8 characters!");
        
        return getPasswordInput(prompt);
    
    }

    return password;

}



/********************************************************************************/
/* Function Name: getIntInput                                                   */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : Int                                                           */
/*                                                                              */
/* Note         : This is Password Input Function                               */
/********************************************************************************/

int getIntInput(string prompt) {
    
    string value;
    
    while(true){
        
        cout << prompt;

        speak(prompt);
        
        cin >> value;

        if(value == "*")    exitWindow();

        else if(value == "-"){

            return -1;

        }

        else{

            bool isNumber = true;

            for(char c : value){

                if(!isdigit(c)){

                    isNumber = false;
                    
                    break;

                }

            }

            if(isNumber){

                return stoi(value);

            }

            else{

                cout << "Invalid Input! Please Enter A Number, * to Exit, or - to go back!\n";

                speak("Invalid Input! Please Enter A Number, * to Exit, or - to go back!");

            }

        }
    
    }

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

        cout << prompt << endl << endl << endl;

        for(int i=0; i<=x; i++){

            cout << YELLOW() << "█" << RESET();

        }

        cout << flush;

        sleepMS(50);
        
        x++;

    }   while(x!=50);

    cout << endl << endl << endl;

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

    if(!VOICE_ENABLED) return;
    
    #ifdef _WIN32

        string command = "PowerShell -Command \"Add-Type -AssemblyName System.Speech; "
                         "(New-Object System.Speech.Synthesis.SpeechSynthesizer).Speak('" + text + "');\"";
        
        system(command.c_str());

    #else

        string command = "espeak \"" + text + "\"";
        
        system(command.c_str());
    
    #endif

}



/********************************************************************************/
/* Function Name: voiceSetting                                                  */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is Turn On And Turn Off Voice                            */
/********************************************************************************/

void loadConfig(){

    ifstream file("Database/config.txt");

    if (!file.is_open()) return;

    string line;

    if(getline(file, line)){
        
        string decrypted = decryptFromHex(line);
        
        VOICE_ENABLED = (decrypted == "1");
    
    }

    if(getline(file, line)){
        
        string decrypted = decryptFromHex(line);
        
        COLOR_ENABLED = (decrypted == "1");
    
    }

    file.close();

}








/********************************************************************************/
/* Function Name: saveVoiceConfig                                               */
/*                                                                              */
/* Inputs       : Bool                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This will save the voice configuration in a text file         */
/********************************************************************************/

void saveConfig(bool voiceCheck, bool colorCheck){

    ofstream file("Database/config.txt", ios::trunc);
    
    if (!file.is_open()) return;


    file << encryptToHex(voiceCheck ? "1" : "0") << endl;


    file << encryptToHex(colorCheck ? "1" : "0") << endl;

    file.close();

}



/********************************************************************************/
/* Function Name: sleepIgnoreInput                                              */
/*                                                                              */
/* Inputs       : int                                                           */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This will block input during sleep in ubuntu                  */
/********************************************************************************/

void sleepIgnoreInput(int ms) {
    
    struct termios oldt, newt;
    
    tcgetattr(STDIN_FILENO, &oldt);
    
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    usleep(ms * 1000);

    tcflush(STDIN_FILENO, TCIFLUSH);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}