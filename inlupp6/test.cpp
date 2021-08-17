#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
const int MAX_PERSONER = 10;

string* textTillOrd(string is){
    string ord = "";
    string* Templista = new string[MAX_PERSONER + 4];
    int upprepningar = 0;
    int i = 0;
    for(char x : is){
        if(x == ' '){
            if(upprepningar == 0){
                Templista[i] = ord;
                i++;
            }
            // cout << ord << endl;
            ord = "";
            upprepningar++;
        } else {
            ord = ord + x;
            upprepningar = 0;
        }
    }
    return Templista;

}


int main(){
    string str = "190615  transp  Eva     6000    5       Bosse   Kristin  Paul    Torsten Stina";
    string *lista;
    lista = textTillOrd(str);

    for(int i = 0; i < 14; i++){
        cout <<  lista[i] << endl;
    }
    return 0;
}