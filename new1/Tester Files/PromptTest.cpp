//Prompt tester, by Reuben Lewis for CS232 project 3

#include <iostream>
#include "RTShell.h"

using namespace std;

int main() {
    cout << "Starting to test the prompt\n";

    cout << "testing basic constructor\n";
    Prompt testPrompt;
    cout << "Test prompt created.\n";

    cout << "testing basic prompt return\n";
    string directory = testPrompt.get();
    cout << "Your current directory is " << directory << "\n";

    return 0;
}
