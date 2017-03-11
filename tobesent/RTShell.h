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
#include <stdlib.h>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <dirent.h>
#include <iterator>
#include <cstring>
#include <libgen.h>

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

class Path {
public:
    Path();
    int find(const string& program) const;
    string getDirectory(int i) const;
    virtual ~Path();

private:
    vector<string> path;
    unsigned size;

};

class Prompt {
public:
    Prompt();
    string get() const;
    ~Prompt();

private:
    string dirPrompt;
    int buffSize;
};

class RTShell{
public:
    RTShell();
    void run();

private:
    void movingDir( const char* argVector);
};
//RTSHELL_H
#endif
