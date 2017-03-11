//Class Prompt, written by Reuben Lewis, for CS232 Proj3

#include "RTShell.h"

//Constructor that creates a string variable that contains the users current path
Prompt::Prompt() {
    buffSize = 200; //200 should hopefully be enough, even for super long paths
    char* cPrompt;
    char buffer[buffSize];
    //Grabs current path and does some string conversions to get it
    //into a private variable
    cPrompt = getcwd(buffer, buffSize);
    string sPrompt(cPrompt);
    dirPrompt = sPrompt;
}

//Returns the string containing the user's working directory
string Prompt::get() const {
    return dirPrompt;
}

Prompt::~Prompt(){
}
