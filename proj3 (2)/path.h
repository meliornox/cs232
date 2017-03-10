#ifndef PATH_H_
#define PATH_H_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <cstring>
#include <sstream>

using namespace std;

class Path {
public:
    Path();
    int find(const string& program) const;
    string getDirectory(int i) const;
    virtual ~Path();

private:
    vector<string> path;
    unsigned size;

};
#endif
