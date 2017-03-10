/* 
** Theodore Bigelow
** jgb23
** 03/07/17
**
** This is the .h file containing declarations implied as a requirement
** for compliance with the standards for cs 232 projects referred to in main.c
*/

//Guard - It's a header file Thing
#ifndef RTSHELL_H_
#define RTSHELL_H_

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

class Path{
public:
    Path();
    int find(const std::string&);
    string getDirectory(int) const;
};

class Prompt{
public:
    Prompt();
    string get() const;
};

class RTShell{
public:
    RTShell();
    void run();
};
//RTSHELL_H
#endif 