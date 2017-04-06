/*
** Reuben Lewis - rtl5
** Theodore Bigelow - jgb23
** 03/07/17
**
** This is the file for the main() function for project 3 in CS 232
**     at Calvin College.  The assignment description can be found at
**     https://cs.calvin.edu/courses/cs/232/assignments/3/index.html
**
** This file is in accordance with the coding standards
**     for CS 232 projects found at
**     https://cs.calvin.edu/courses/cs/232/policies/coding.html
*/

//Include header file
#include "RTShell.h"

/*
** main() is a driver for the shell, all it does is create and start it
**     and the shell class takes care of the rest.
**
** returns a status code, 0 is normal
*/
   int main()
   {
      RTShell myShell;
      myShell.run();
   }
