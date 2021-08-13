#include <iostream>
using namespace std;

int main(){
    int a;  
    int b = 12;
    a = 0; // saknades ett semikolon efter tilldelning.
    
    cout << "a = " << a << endl;
    cout << a+b << '\n' << "a-b = " << a-b << endl;  
    return 0;
    }