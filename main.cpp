/* The Expanse is a game project I (Dale) used to learn //
// more about c/c++. The code is free and available to anyone  //
// to use in part or whole. It would be really cool to see     //
// someone swap out the current ascii graphics with something a//
// little or a lot better. Play the game, use the editor, use  //
// the code and just generally have fun.                       */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "Gra_Pkg.h"

using namespace std;
bool sd = false;


int saveGame();

int main()
{
    g_Time.start();
    calls++;
    if(!g_start(1))
        std::cout << "Error: Failed to start graphics." << std::endl;
    refresh();
    //populateWorld();
    mainMnu();
    g_start(0);
    std::cout << "Thank you for playing. Total Time: " << g_Time.elapsedTime() << " Calls: " << calls << std::endl << "Average Time: " << (long double) g_Time.elapsedTime()/calls << std::endl << "Mouse X: " << mouEV.x << std::endl;
    return 0;
}

int geSave()
{

    return 0;
}
