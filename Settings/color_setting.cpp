#include "settings.h"
#include "utility.h"
#include "colors.h"



#include <iostream>
#include <string>
using namespace std;



void colorSettings(){

    do{

        clearScreen();

        if(COLOR_ENABLED){

            cout << GREEN() << "Color Is Currently Enabled!" << RESET() << endl;

            speak("Color Is Currently Enabled!");

            int choiceSetting = getIntInput("If You Want To Disable The Color Please Click 1 If You Want To Go Back Click - : ");

            if(choiceSetting == 1){

                loadingScreen("Setting Application In Progress... ");

                cout << "Color Successfully Disabled!" << endl;

                speak("Color Successfully Disabled!");

                COLOR_ENABLED = false;

                saveConfig(VOICE_ENABLED, COLOR_ENABLED);

                cout << RED() << "Color Is Currently DISABLED!" << RESET() << endl;

            }

            else if(choiceSetting == -1){

                break;

            }

            else{

                cout << "Wrong Input! Choose Only 1" << endl;

                speak("Wrong Input! Choose Only 1");

                continue;

            }

        }

        else{

            cout << RED() << "Color Is Currently DISABLED!" << RESET() << endl;

            int choiceSetting = getIntInput("If You Want To Enable The Color Please Click 1 If You Want To Go Back Click - : ");

            if(choiceSetting == 1){

                loadingScreen("Setting Application In Progress... ");

                cout << "Color Successfully Enabled!" << endl;

                speak("Color Successfully Enabled!");

                COLOR_ENABLED = true;

                saveConfig(VOICE_ENABLED, COLOR_ENABLED);

                cout << GREEN() << "Color Is Currently ENABLED!" << RESET() << endl;

            }

            else if(choiceSetting == -1){

                break;

            }

            else{

                cout << "Wrong Input! Choose Only 1" << endl;

                speak("Wrong Input! Choose Only 1");

                continue;

            }

        }

    }   while(true);

}