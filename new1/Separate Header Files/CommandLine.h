/* 
** Theodore Bigelow
** jgb23
** 03/10/17
**
** This is the .h file containing declarations of rthe CommandLine class 
**     as per the requirements for compliance with the standards
**     for cs 232 projects referred to in main.c
*/

//Guard - It's a header file Thing
#ifndef COMMANDLINE_H
#define COMMANDLINE_H

//Includes libraries
#include <sstream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cstring>

//Define namespace
using namespace std;

class CommandLine{
public:
    CommandLine(std::istream&);
    char* getCommand() const;
    int getArgCount() const;
    char** getArgVector() const;
    char* getArgVector(int) const;
    bool noAmpersand() const;
	virtual ~CommandLine();
private:
    char ** argv;
    int argc;
};

//COMMANDLINE_H
#endif 