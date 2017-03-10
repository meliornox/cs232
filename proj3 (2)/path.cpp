/* Defines the path class for the rtshell.
 * Reuben Lewis
 */

 #include "path.h"

 // Initial constructor, grabbing each directory in PATH and adding it to
 //vector path.
 Path::Path() {
     size = 0;
     char* charPath =  getenv("PATH"); //Grab the PATH enviromental variable
     string sPath(charPath);
     //PATH comes as a colon sepreated line of chars, this splits them into
     //the different directories and assigns them to the vector
     stringstream ss(sPath);
     while( getline(ss, sPath, ':')) {
         path.push_back( sPath );
         size = size + 1;
     }
 }

//Looks through the different PATH directories and retunrns the index in the
//path vector that program is located in. Otherwise, returns -1.
int Path::find(const string& program) const {
    //Assume the file doesn't exsist, and create a couple of directory stucts
    int fileIsFound = -1;
    struct dirent *FileInPathDir;
    DIR *pathDir;
    string sPath;

    //Iterate through the different directories in vector path
    for (int i = 0; i < size; i ++ )
    {
        sPath = path[i];

        //Open said directories, and go through them comparing the names of the
        //files inside to program's name. If found, breaks.
        pathDir = opendir(sPath.c_str());
        while ((FileInPathDir = readdir(pathDir)) != NULL)
        {
            if ( FileInPathDir->d_name == program)
            {
                fileIsFound = i;
                break;
            }
        }
    }

    //Close the "dir" behind us ("dir" -> "door", get it? :D)
    closedir(pathDir);

    return fileIsFound;
}

//Returns a string containing the directory at index i
string Path::getDirectory(int i) const {
    string pathReturned( path[i]);
    return pathReturned;
}

//Don't forget to clean up!
Path::~Path() {
}
