/* 
** Theodore Bigelow
** jgb23
** 03/07/17
**
** This is the CommandLine.c file containing definitions for Project 3
**     as required by the instructions referred to in the main file.
**
** Holy segmentation faults Batman!
**
*/
/*
** Resources: 
**     http://www.cplusplus.com/reference/string/string/
**     http://stackoverflow.com/questions/3300743/i-want-to-see-if-a-character-is-present-in-a-string
**     http://stackoverflow.com/questions/17757617/returning-array-of-char-pointers-from-a-function-c
**     http://www.cplusplus.com/forum/general/17892/
**     http://stackoverflow.com/questions/6846263/maximum-length-of-command-line-argument-that-can-be-passed-to-sqlplus-from-lin
**     http://stackoverflow.com/questions/17813423/cout-with-char-argument-prints-string-not-pointer-value
**     http://www.cplusplus.com/forum/articles/10627/
**     Prof. Norman for ClassName::function()
**     http://stackoverflow.com/questions/13428164/c-compile-error-has-initializer-but-incomplete-type
**     http://stackoverflow.com/questions/16545753/initializer-but-incomplete-type
**     http://stackoverflow.com/questions/13947445/how-to-find-char-in-a-vector-of-string
**     http://www.cplusplus.com/reference/cstring/strcmp/
**     http://www.cplusplus.com/forum/unices/57754/
**     http://www.cplusplus.com/forum/beginner/174005/
**     http://stackoverflow.com/questions/2346806/what-is-a-segmentation-fault
**     http://stackoverflow.com/questions/1524356/c-deprecated-conversion-from-string-constant-to-char
**     http://www.cplusplus.com/forum/beginner/122208/
**     http://en.cppreference.com/w/cpp/language/reinterpret_cast
**     http://crasseux.com/books/ctutorial/argc-and-argv.html
**     http://stackoverflow.com/questions/2037736/finding-size-of-int-array/
**     http://stackoverflow.com/questions/7352099/stdstring-to-char
**     http://www.cplusplus.com/forum/beginner/12305/
**     http://stackoverflow.com/questions/677653/does-delete-call-the-destructor
*/

//Includes header file
#include "RTShell.h"

/*
** CommandLine() constructs a CommandLine by reading a command-line from in,
**     parsing it, and building instance variables for argc and argv.
**
** istream& in: A reference to an istream which allows us to read in commands.
**/
    
CommandLine::CommandLine(istream& in){
    // Make a temporary string to get the line from the console and make an
    //     istringstream, which allows the use of while() to cycle through 
    //     the words in the console input.
    string lineIn;
    getline(in, lineIn);
    istringstream iss(lineIn);

    // Make a vector of strings, which is kind of like an array but not 
    //     a fixed size to hold all the words, make another temporary string
    //     to hold each word, and initialize argc to count the words.
    vector<string> args;
    string word;
    argc = 0;

    // Cycle through each word in the console input stream and push them 
    //     at the back into the temporary vector of strings, iterating argc
    //     to count each word.
    while (iss >> word) {
        args.push_back(word);
        argc++;
    }

    // Initialize the "array" of "strings" (C++ does things 
    //     a little differently than a lot of other languages with respect
    //     to strings)
    argv = new char*[args.size()];

    // Fill in the values for argv
    for (int i = 0; i < argc; i++) {
        argv[i] = new char[args[i].size() + 1];
        strcpy(argv[i], args[i].c_str());
    }
}

/*
** getCommand() returns a pointer to the command portion of the command-line.
**
** returns char*, the first "string" of the console input.
**/
char* CommandLine::getCommand() const{
    return argv[0];
}

/*
** getArgCount() returns the number of command-line arguments on 
**     the command-line.
**
** returns int, the number of arguments sumbitted.
**/
int CommandLine::getArgCount() const{
    return argc;
}

/*
** getArgVector() returns a pointer to a char* array,
**     each entry of which points to one 'word' of the command-line.
**
** returns char**, the "array" of "strings" that make up the user input on the command line.
**/
char** CommandLine::getArgVector() const{
    return argv;
}

/*
** getArgVector() returns a pointer to the ith command-line 'word'.
**
** int i: the position of the command-line word accessed. 
** returns char*, the ith C++ "string" in the console input.
**/
char* CommandLine::getArgVector(int i) const{
    return argv[i];
}

/*
** noAmpersand() returns true if and only if no ampersand was given on the
**     command-line.
**
** returns bool, whether there is at least one string in the arguments that
**     contains '&'.
**/
bool CommandLine::noAmpersand() const{
    // Make a char* for &
    const char* ampersand = "&";
    
    // Cycle through each "string" in the console input and check if it's '&'
    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i],ampersand) == 0) {
            // If so there is not no ampersand
            return false;
        }
    }
    // If not there is an ampersand.
    return true;
}

/*
** ~CommandLine() is an override for the destructor for CommandLine.  It is
**     in place because pointers require delete[] to remove them from the heap.
**     Since we're using an array of pointers, for every element of the array
**     we have to call delete[], then again for the array itself.
**/
CommandLine::~CommandLine() {
    // Cycle through the elements of argv
    for (int i = 0; i < argc; i++) {
        //Delete each one
        delete[] argv[i];
    }
    // Delete argv itself.
    delete[] argv;
}