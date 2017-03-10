//Path tester, by Reuben Lewis for CS 232 project 3

#include <iostream>
#include "path.h"

using namespace std;

int main() {
    cout << "Starting testing of path\n";

    cout << "Testing constructor\n";
    Path testPath;
    cout << "Path created\n";

    cout << "testing find\n";
    int index = testPath.find("noFile");
    cout << "Index for noFile is " << index << "\n";
    index = testPath.find("testPath");
    cout << "testFind found at " << index << "\n";


    cout << "testing getDirectory \n";
    string dir;
    dir = testPath.getDirectory(index);
    cout << "At index " << index << " is " << dir << "\n";

    return 0;
}
