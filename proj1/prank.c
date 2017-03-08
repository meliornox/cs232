/* 
** Theodore Bigelow
** jgb23
** 02/17/17
**
** This is the .c file containing definitions implied as a requirement
** for compliance with the standards for cs 232 projects found at 
** https://cs.calvin.edu/courses/cs/232/policies/coding.html
*/

//Includes header file
#include "prank.h"

//Global variables are defined in main.c, in compilation they should be linked
    //and message and sec are accessable here

/*
** annoy() prints the message and is triggered by SIGALRM
**
** number: The number of the signal that was received 
**/
void handler(int number) {
    //Prints the message
    printf("%s\n", message);
}