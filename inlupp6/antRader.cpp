#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main () {
string s;
int sTotal;

ifstream in;
in.open("resa.txt");

while(!in.eof()) {
	getline(in, s);
	sTotal ++;	
    cout << s << endl;
}

cout << sTotal;

in.close();	
return 0;
}