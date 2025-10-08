#include "authentication.h"



#include <iostream>
#include <string>
#include <fstream>
using namespace std;




/********************************************************************************/
/* Function Name: saveSession                                                   */
/*                                                                              */
/* Inputs       : String                                                        */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is the function To Save Login History                    */
/********************************************************************************/

void saveSession(const string &username){

    string userName;
    
    ofstream file("Database/session.txt", ios::trunc);

    userName = encryptToHex(username);

    file << userName;

    file.close();

}



/********************************************************************************/
/* Function Name: clearSession                                                  */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : None                                                          */
/*                                                                              */
/* Note         : This is the function To Clear Login History                   */
/********************************************************************************/

void clearSession(){

    ofstream file("Database/session.txt", ios::trunc);

    file.close();

}



/********************************************************************************/
/* Function Name: loadSession                                                   */
/*                                                                              */
/* Inputs       : None                                                          */
/*                                                                              */
/* Returns      : String                                                        */
/*                                                                              */
/* Note         : This is the function To Load Login History                    */
/********************************************************************************/

string loadSession(){
    
    ifstream file("Database/session.txt");

    if(!file || file.peek() == ifstream::traits_type::eof()){

        return "";

    }

    string encodedUsername;

    getline(file,encodedUsername);

    file.close();

    string userName = decryptFromHex(encodedUsername);

    return userName;

}