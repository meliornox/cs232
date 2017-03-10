//Class Prompt, written by Reuben Lewis, for CS232 Proj3

#ifndef PROMPT_H_
#define PROMPT_H_

#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace std;

class Prompt {
public:
    Prompt();
    string get() const;
    ~Prompt();

private:
    string dirPrompt;
    int buffSize;
};

#endif
