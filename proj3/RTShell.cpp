/* 
** Theodore Bigelow
** jgb23
** 03/07/17
**
** This is the .c file containing definitions implied as a requirement
** for compliance with the standards for cs 232 projects referred to in main.c
**
** References: http://www.cplusplus.com/forum/general/46540/
**     http://www.linuxquestions.org/questions/programming-9/making-a-c-shell-775690/
**     http://stackoverflow.com/questions/15006269/get-substring-before-a-certain-char-in-c
**     http://stackoverflow.com/questions/1195675/convert-a-char-to-stdstring
**     http://www.cplusplus.com/reference/string/string/find/
**     http://stackoverflow.com/questions/2564052/how-to-copy-char-into-a-string-and-vice-versa
**     http://www.cplusplus.com/reference/string/string/substr/
*/

//Includes header file
#include "RTShell.h"
using namespace std;

// Global variables

/*
** RTShell() ~*#Description#*~
**
** ~*#Input#*~ 
**/
RTShell(){
}

/*
** run() ~*#Description#*~
**
** ~*#Input#*~ 
**/
void run() {
    while(true){

        cout << get_current_dir_name () << "$ " ;

        CommandLine c(cin);
        Path p();
        Prompt pr();


        char* wholeArray = c.getCommand();
        //Maybe s instead of str
        string wholeString str(wholeArray);
        string::size_type pos = wholeString.strchr(' ');
        string command = wholeString.substr(0, pos);

        if(strcmp(command, "exit") == 0){
            exit(0);
        } else {

            ////////////////////////////////
            //http://www.linuxquestions.org/questions/programming-9/making-a-c-shell-775690/
            //http://users.cs.cf.ac.uk/Dave.Marshall/C/node20.html
            //https://linux.die.net/man/3/execvp
            //http://p2p.wrox.com/c-programming/92954-c-class-example-separate-header-implementation-file.html
            //https://listenonrepeat.com/?v=YqeW9_5kURI#Major_Lazer_%26_DJ_Snake_-_Lean_On_(feat__M%C3%98)_(Official_Music_Video)
            //https://cs.calvin.edu/courses/cs/232/assignments/3/index.html
            //http://www.cprogramming.com/tutorial/lesson14.html

	        if (!strcmp (prog, "cd"){
                if (argv[1] == NULL){
                    chdir ("/");
                } else {
                    chdir (argv[1]);
                }
                perror (command);
            } else if ((pid = fork()) == -1){
                perror("Can't fork");
                exit(-1);
            }
            // ---- by when you get here there will be two processes
            if (pid == 0) {
                // child process
                string path = p.getDirectory();
                char *charPath = path.c_str();
                execvp(charPath,c.getCommand());
            } else {
                //parent process
                if(waitpid(pid, 0, 0) <0){
                    perror("Can't wait for child");
                    exit(-1);
                }
            }
        }
        //delete[] command;
    }
}
