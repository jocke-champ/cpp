#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26;  //A-Z

int berakna_histogram_abs(char* antal, int* ant_bok, int ascii_A, int antal_langd){
    int langd = 0;
  for(int i = 0; i <= antal_langd; i++){
    int bokstav = int(antal[i])-ascii_A; // får ett tal mellan 0 - 25
    if(bokstav >= 0 && bokstav <= 25){
        langd++;
        ant_bok[bokstav] += 1; // går igenom texten och lägger till hur ofta en bokstav förekommer i texten enligt 0 - 25 <=> A - Z
        }
  }
  return langd;
}

void skriv_histogram_abs(int* ant_bok, int ascii_A){
  for(int i = 0; i <= ANTAL_BOKSTAVER-1; i++){
    char bokstav = (char)(ascii_A+i); // omvandlar ascii till bokstav
    cout << bokstav << ": " << ant_bok[i] << endl;
  }
}

int main()
{
  int ant_bok[ANTAL_BOKSTAVER] = { 0 };
  int ascii_A = int('A');
  string inmatning;

  cout << "Ge en rad med text: " << endl;
  getline(cin, inmatning);

  char antal[inmatning.length()];

  for(int i = 0; i < sizeof(antal); i++){
    antal[i] = toupper(inmatning[i]); // omvandlar alla bokstäver i texten till stora bokstäver
  }

  int antal_langd = inmatning.length();

  int langd = berakna_histogram_abs(antal, ant_bok, ascii_A, antal_langd);

  cout << endl;
  cout << "Resultat för bokstäverna A-Z" << endl;
  cout << endl;
  cout << "Totala antalet bokstäver: " << langd << endl;
  cout << "Bokstavsfördelning:" << endl;

  skriv_histogram_abs(ant_bok, ascii_A);
  
  return 0;
}