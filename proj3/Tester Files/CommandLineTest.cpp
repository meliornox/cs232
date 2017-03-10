/* 
** Theodore Bigelow
** jgb23
** 03/09/17
**
** This is the test file for CommandLine.cpp with printouts to console
**     to demonstrate the program's progress.
** Compile with $g++ -o test CommandLine.cpp CommandLineTest.cpp
**              $./test
*/

#include "RTShell.h"
using namespace std;

int main(){
    cout<<"Started\n$";
    CommandLine c(cin);
    cout<<"built CommandLine\n";    
    cout<<c.getCommand();
	cout<< "\n";
    cout<<"getCommand works\n";
	cout<<c.getArgCount();
	cout<< "\n";
    cout<<"getArgCount works\n";
	cout<<c.getArgVector();
	cout<< "\n";
    cout<<"getArgVector() works\n";
	cout<<c.getArgVector(1);
	cout<< "\n";
    cout<<"getArgVector(int) work\n";
	cout<<c.noAmpersand();
	cout<< "\n";
    cout<<"noAmpersand works\n";
    return 0;
}