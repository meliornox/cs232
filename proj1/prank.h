/* 
** Theodore Bigelow
** jgb23
** 02/17/17
**
** This is the .h file containing declarations implied as a requirement
** for compliance with the standards for cs 232 projects found at 
** https://cs.calvin.edu/courses/cs/232/policies/coding.html
*/

//Guard - It's a header file Thing
#ifndef PRANK_H_
#define PRANK_H_

//Includes libraries
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

//Declares global variables
int enableInterrupts, sec;
char *message;

//Declares our single function
void handler(int number);

//PRANK_H
#endif 