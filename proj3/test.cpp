//jgb23@hollerith:~/232/proj3$ g++ -o test CommandLine.cpp test.cpp
//CommandLine.cpp:28:20: error: expected ')' before '&' token
//CommandLine(istream& in){
//                   ^


#include "RTShell.h"
using namespace std;

int main(){
    CommandLine c(cin);
    cout<<c.getCommand();
	cout<< " ";
	cout<<c.getArgCount();
	cout<< " ";
	cout<<c.getArgVector();
	cout<< " ";
	cout<<c.getArgVector(1);
	cout<< " ";
	cout<<c.noAmpersand();
    return 0;
}