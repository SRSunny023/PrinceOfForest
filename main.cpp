#include "authentication.h"
#include "utility.h"



#include <iostream>
using namespace std;





int main(){
    
    loadConfig();

    loadingScreen("Game Loading Please Wait");
    
    authenticationMenu();

    return 0;

}