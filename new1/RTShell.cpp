/*
** Theodore Bigelow
** jgb23
** 03/07/17
**
** This is the .c file containing definitions implied as a requirement
** for compliance with the standards for cs 232 projects referred to in main.c
**
** Run using $g++ -o rtshell main.cpp RTShell.cpp Prompt.cpp Path.cpp CommandLine.cpp
**
** References: http://www.cplusplus.com/forum/general/46540/
**     http://www.linuxquestions.org/questions/programming-9/making-a-c-shell-775690/
**     http://stackoverflow.com/questions/15006269/get-substring-before-a-certain-char-in-c
**     http://stackoverflow.com/questions/1195675/convert-a-char-to-stdstring
**     http://www.cplusplus.com/reference/string/string/find/
**     http://stackoverflow.com/questions/2564052/how-to-copy-char-into-a-string-and-vice-versa
**     http://www.cplusplus.com/reference/string/string/substr/
**     https://sourceforge.net/p/glx/mailman/message/18347524/
**     http://stackoverflow.com/questions/22608160/atom-change-indentation-mode
*/
            ////////////////////////////////
            //http://www.linuxquestions.org/questions/programming-9/making-a-c-shell-775690/
            //http://users.cs.cf.ac.uk/Dave.Marshall/C/node20.html
            //https://linux.die.net/man/3/execvp
            //http://p2p.wrox.com/c-programming/92954-c-class-example-separate-header-implementation-file.html
            //https://listenonrepeat.com/?v=YqeW9_5kURI#Major_Lazer_%26_DJ_Snake_-_Lean_On_(feat__M%C3%98)_(Official_Music_Video)
            //https://cs.calvin.edu/courses/cs/232/assignments/3/index.html
            //http://www.cprogramming.com/tutorial/lesson14.html

//Includes header file
#include "RTShell.h"

// Global variables

/*
** RTShell() ~*#Description#*~
**
** ~*#Input#*~
**/
RTShell::RTShell(){
}

/*
** run() ~*#Description#*~
**
** ~*#Input#*~
**/
void RTShell::run() {
    while (true) {
        Prompt pr;
        string directory = pr.get();

        cout << directory << "$ " ;

        CommandLine c(cin);
        Path p;

        char* command = c.getCommand();
        char** arguments = c.getArgVector();

        if (strcmp(command, "exit") == 0) {
            exit(0);
        } else if (strcmp(command,  "pwd") == 0) {
                cout << directory << "\n";
        } else if (strcmp(command,  "cd") == 0){
            if (c.getArgCount() < 2) {
                char* homeDir = getenv("HOME");
                int err = chdir(homeDir);
            } else {
                movingDir(c.getArgVector(1));
            }
        } else {
            pid_t kidpid = fork();

            if (kidpid < 0){
                perror("Can't fork");
                exit(-1);
            } else if (kidpid == 0) {
                //I am the child

                if(!c.noAmpersand()){
                    cout << "\n";
                }
                int index = p.find(command);
                if(index == -1){
                    cout << "Command not found\n";
                } else {
                //cout << "1 ";
                    string sCommand(command);
                    //cout << "2 ";
                    string fullCMD = p.getDirectory(index) + "/" + sCommand;
                    //cout << "3 ";
                    //cout << c.getArgCount() << "\n";
                    //cout << "4 ";
                    int i = 0;
                    //cout << "5 ";
                    while(arguments[i] != NULL){
                        //cout << arguments[i] << " ";
                        i++;
                    }
                    //cout << "6 ";
                    //cout << "\n";
                    cout << c.getArgCount() << " ";
                    for(int j = c.getArgCount(); j < i; j++){
                        cout << "removing element " << j << ": " << arguments[j] << "\n";
                        arguments[j] = NULL;
                        //cout << j << "j ";
                    }
                    cout << "\n";
                    //cout << "7\n";
                    // i = 0;
                    // while(arguments[i] != NULL){
                    //     cout << arguments[i] << " ";
                    //     i++;
                    // }
                    //cout << "\n";
                  // Somehow fixes "ignoring non-option arguments" after pwd
                //    cout << c.getArgVector();
                    execve(fullCMD.c_str(), arguments, NULL);
                }

            } else if(c.noAmpersand()){

            //I am parent process
                //int *zero = static_cast<int*>(0);
                int status;
                waitpid(kidpid, &status, 0 );
                cout << status << "\n";
                cout << kidpid << "\n";
                if (WIFEXITED(status)) {
                    kill(kidpid, 0);
                    printf("%d\n", WEXITSTATUS(status));
                }
                /*
    if ( (waitpid( kidpid, &status, 0 )) == -1 ) {
                    perror("Can't wait for child");
                    exit(-1);
                }    */



            }
        }
    }
        //delete[] command;
}

//Takes in  an argument from the cd command and moves to the specified path
void RTShell::movingDir(const char* argVector) {
    string nextDir;
    int err;
    int indexOfDir;
    Prompt pr;
    Path p;
    //If the argVector is empty, we want to go back to the home dir
    if (argVector == NULL){
        char *userID;
        cuserid(userID);
        string sUserID(userID);
        nextDir = "/home/" + sUserID;
        err = chdir (nextDir.c_str());
    } else {
        //Try to move directly to the dir. If that fails, we know the dir is
        //either above or below the current folder.
        err = chdir(argVector);
        if (err == -1) {
            //If "..", we want to go to the folder above
            if (argVector == "..") {
                string currentDir = pr.get();
                nextDir = dirname((char *)currentDir.c_str());
            } else {
                //Otherwise, search the folder to see if argVector is inside
                indexOfDir = p.find(argVector);
                if (indexOfDir == -1) {
                    cout << "Directory not found!\n";
                    return;
                }
                nextDir = p.getDirectory(indexOfDir) + "/" + argVector;
            }
            err = chdir(nextDir.c_str());
        }
    }
}
