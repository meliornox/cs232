/* 
** Theodore Bigelow
** jgb23
** 03/07/17
**
** This is the CommandLine.c file containing definitions for Project 3
**     as required by the instructions referred to in the main file.
**
** Resources: http://www.cplusplus.com/reference/string/string/
**     http://stackoverflow.com/questions/3300743/i-want-to-see-if-a-character-is-present-in-a-string
**     http://stackoverflow.com/questions/17757617/returning-array-of-char-pointers-from-a-function-c
**     http://www.cplusplus.com/forum/general/17892/
**     http://stackoverflow.com/questions/6846263/maximum-length-of-command-line-argument-that-can-be-passed-to-sqlplus-from-lin
**     http://stackoverflow.com/questions/17813423/cout-with-char-argument-prints-string-not-pointer-value
**     http://www.cplusplus.com/forum/articles/10627/
*/

//Includes header file
#include "RTShell.h"

/*
** CommandLine() constructs a CommandLine by reading a command-line from in,
**     parsing it, and building instance variables for argc and argv.
**
** in: An istream reference for reading in commands 
**/
	
CommandLine(istream& in){
// Max length of a command could be 2090314 according to xargs --show-limits,
//     but more than 256 in a char[] will throw errors.

    vector<string> words;

    char commands[256];
    in.getline(commands, 256);
    istringstream ss(commands);

    string word;
    while (ss >> word){
        words.push_back(word);
    }
    char** argv = getArgVector();
    int argc = getArgCount();
}

/*
** getCommand() returns a pointer to the command portion of the command-line.
**
** in: An istream reference for reading in commands 
**/
char* getCommand() const{
	char** args = this.getArgVector();
    return args[0];
}

/*
** getArgCount() returns the number of command-line arguments on 
**     the command-line.
**
** in: An istream reference for reading in commands 
**/
int getArgCount() const{
	return words.size();
}

/*
** getArgVector() returns a pointer to a char* array,
**     each entry of which points to one 'word' of the command-line
**
** in: An istream reference for reading in commands 
**/
char** getArgVector() const{

    // create an array of char*
	int number = this.getArgCount();
    char** ptrArray = new char*[number];
	
	for(int i = 0; i < number; i++){
		ptrArray[i] = this.getArgVector(i);
	}

    return ptrArray;	
}

/*
** getArgVector() returns a pointer to the ith command-line 'word'
**
** in: An istream reference for reading in commands 
**/
char* getArgVector(int i) const{
	char** args = this.getArgVector();
    return args[i];
}

/*
** noAmpersand() returns true if and only if no ampersand was given on the
**     command-line
**
** in: An istream reference for reading in commands 
**/
bool noAmpersand() const{
	int pos = -1;
	if(words.find("&") == -1){
        return true;
	} else {
		return false;
	}
}