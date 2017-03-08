/* 
** Theodore Bigelow
** jgb23
** 02/17/17
**
** This is the file for the main() function in accordance with the coding 
** standards for cs 232 projects found at 
**     https://cs.calvin.edu/courses/cs/232/policies/coding.html
**
** I used several online resources for this project, most notably 
** stackOverflow.com for their explaination of .h, .c, and main.c
** files and tutorialsPoint.com for their explainations of library functions.
** 
** Compile and run by navigating to this folder and typing 
**     gcc -o prank main.c prank.c
**     ./prank
** Along with any arguments: -m "message" to set the message to message,
** -t sec to set the time between messages to sec, and -i to disable (default)
** or +i to enable interrupts(Ctrl-C).
**
** This program defaults to be unresponsive to interrupts(Ctrl-C). In order to
** end the program, type
**     Ctrl-Z
** To kill it, type
**     ps
** and find the program with the CMD value of prank, note its PID value, and
** type kill -9 PID, where PID is the value of PID. This is the surest way to
** kill a program, it circumvents the program itself which could be ignoring
** user input(as this one does) and tells the operating system to kill
** the process.
*/

//Include header file
#include "prank.h"

/*
** main() processes the command line arguments with if statements
**
** thisMany: The number of command line arguments
** arguments[]: The array of command line arguments
**
** returns a status code, 0 is normal
*/

//Define global variables
int enableInterrupts = 0;
char *message = "No, YOU'RE annoying";
int sec = 5;

//When program starts
int main(int thisMany, char *arguments[]) {
    //each command is checked:
    for (int i = 1; i < thisMany; i++) {
        //+i enables interrupts
        if (strcmp(arguments[i], "+i") == 0) {
            enableInterrupts = 1;
        }
        //-i disables interrupts
        if (strcmp(arguments[i], "-i") == 0) {
            enableInterrupts = 0;
        }
        //-m changes message
        if (strcmp(arguments[i], "-m") == 0) {
            message = arguments[i+1];
        }
        //+t sets the delay between sending the messages
        if (strcmp(arguments[i], "+t") == 0) {
            sec = atoi(arguments[i+1]);
        }
    }
    //Then we define SIGALRM signal to be handled by sending SIGALARM's signal
        //number to handler()
    signal(SIGALRM, handler);
    //If interrupts are not enabled user interaction (SIGINT) is ignored
    if (enableInterrupts == 0) {
        signal(SIGINT, SIG_IGN);
    }
    //Lastly the program loops infinitely, calling a function that will trigger
        //a SIGALRM alarm every sec seconds and pausing until the signal 
        //is issued
    while(1) {
        alarm(sec);
        pause();
    }
}