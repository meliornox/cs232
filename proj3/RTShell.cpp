/*
** Reuben Lewis - rtl5
** Theodore Bigelow - jgb23
** 03/07/17
**
** This is the .c file containing definitions implied as a requirement
** for compliance with the standards for cs 232 projects referred to in main.c
**
** Run using $g++ -o rtshell main.cpp RTShell.cpp Prompt.cpp Path.cpp
**     CommandLine.cpp
**     $./rtshell
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
**     http://www.linuxquestions.org/questions/programming-9/making-a-c-shell-775690/
**     http://users.cs.cf.ac.uk/Dave.Marshall/C/node20.html
**     https://linux.die.net/man/3/execvp
**     http://p2p.wrox.com/c-programming/92954-c-class-example-separate-header-implementation-file.html
*/

//Includes header file
#include "RTShell.h"

// Global variables

/*
** run() runs the RTShell and makes use of several helper classes.  RTShell
**     performs bash shell commands on behalf of the user using threading and
**     allowing for & to return control to the user while the shell executes
**     the command on another thread.
**
** results in console outputs
**/
void RTShell::run() {
    // Infinite loop
    while (true) {
        // Prompt refreshes current path
        Prompt pr;
        // Make it look like bash
        cout << pr.get()<< "$ " << flush;
        // Make a new CommandLine to read in the next line
        CommandLine c(cin);
        // Make variable for the command since it gets referenced so often
        char* command = c.getCommand();

        // Exit gracefully if the command is "exit"
        if (strcmp(command, "exit") == 0) {
            exit(0);
        }
        // If command is pwd list current path
        else if (strcmp(command,  "pwd") == 0) {
            cout << pr.get() << endl;
        }
        // If command is cd
        else if (strcmp(command,  "cd") == 0){
            // If cd is the only argument go to the home directory
            if (c.getArgCount() < 2) {
                char* homeDir = getenv("HOME");
                int err = chdir(homeDir);
            }
            // Otherwise go to the folder specified
            // (See the comments on movingDir)
            else {
                movingDir(c.getArgVector(1));
            }
        }
        // If command is not found in the path print error
        else if (p.find(command) == -1) {
            cout << "Command not found" << endl;
        }
        // Else execute command:
        else {
            // Make a "string" with the command and its path directory for use
            //     in execve
            int index = p.find(command);
            char cmdpath[256];
            strcpy(cmdpath, p.getDirectory(index).c_str());
            strcat(cmdpath, "/");
            strcat(cmdpath, c.getCommand());
            // Attempt to make a child
            pid_t kidpid = fork();
            // Make a variable for the status of the child
            int status;
            if (kidpid < 0) {
                perror("Can't fork");
                continue;
            } else if (kidpid == 0) {
                //You're such a child

                // Make a "string" "array" holding the arguments from
                //     CommandLine
                char** args = c.getArgVector();
                // Set the last argument to be a terminating NULL
                // (This was the most tricky part of our debug process)
                // AKA The Giant Slicer Blade
                args[c.getArgCount()] = NULL;
                // Run the command, setting a variable for error handling
                int error = execve(cmdpath, args, NULL);
                // Handle error
                if (error == -1) {
                    // Be nice about it
                    cout << "Cannot complete " << c.getCommand() << endl;
                    perror("");
                    // Soft break so the "shell" continues execution
                    continue;
                }
            }
            if (c.noAmpersand()) {
                // If there is no ampersand in the input wait for the child, the
                //     implication being that if there is an ampersand the
                //     program will not wait
                waitpid(kidpid, &status, 0);
            }
        }
    }
}
/*
** movingDir() takes in  an argument from the cd command and moves
**     to the specified path
**
** results in the directory being moved to the specified path
**/
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
                    cout << "Directory not found!" << endl;
                    return;
                }
                nextDir = p.getDirectory(indexOfDir) + "/" + argVector;
            }
            err = chdir(nextDir.c_str());
        }
    }
}
