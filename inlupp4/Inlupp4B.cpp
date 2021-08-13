#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP inneh�ller bokstavsfrekvensen i %
// f�r fyra spr�k. TOLK_HJALP[0][0] �r frekvensen av
// bokstaven a f�r engelska. TOLK_HJALP[0][25] �r frekvensen av
// bokstaven z f�r engelska.
// Arrayen �r en GLOBAL KONSTANT och skall allts� ej skickas
// som parameter till den funktion som beh�ver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};



void berakna_histogram_abs(char* antal, double* ant_bok, int ascii_A, int antal_langd){
  for(int i = 0; i <= antal_langd; i++){
    int bokstav = int(antal[i])-ascii_A;
    if(bokstav >= 0 && bokstav <= 25){
        ant_bok[bokstav] += 1;
        }
  }
}

void abs_till_rel(double* ant_bok){
  int storlek = 0;
  for(int i = 0; i < ANTAL_BOKSTAVER; i++){
    storlek += ant_bok[i]; // får antalet bokstäver i texten
  }
  for(int i = 0; i < ANTAL_BOKSTAVER; i++){
    ant_bok[i] = ant_bok[i]*100/storlek;
  }
  cout << "Totala antalet bokstäver: " << storlek << endl;
}

void plotta_histogram_rel(double* ant_bok, int ascii_A){
  cout << "Bokstavsfördelning:" << endl << endl;

  for(int i = 0; i <= ANTAL_BOKSTAVER-1; i++){
    char bokstav = (char)(ascii_A+i);
    cout << bokstav << ": ";
    for(int j = 0; j < ceil(ant_bok[i]); j++){ // representerar ungefär hur stor andel av bokstaven förekommer i texten i procent
      cout << "*";
    } cout << endl;
  }
}

void tolkning(double* ant_bok){
  string mest_trolig, sprak[ANTAL_SPRAK] = {"engelska", "franska", "svenska", "tyska"};
  int sprak_mest_likt;
  double kvadratsumma, sprak_lagst = 0;

  for(int i = 0; i < ANTAL_SPRAK; i++){
    kvadratsumma = 0;
    for(int j = 0; j < ANTAL_BOKSTAVER; j++){
      kvadratsumma += abs((ant_bok[j] - TOLK_HJALP[i][j])*(ant_bok[j] - TOLK_HJALP[i][j])); //kvadratsumman
    }
    if((kvadratsumma < sprak_lagst) || (sprak_lagst == 0)){
      sprak_mest_likt = i;
      sprak_lagst = kvadratsumma;
    }

    cout << sprak[i] << " har kvadratsumma = " << kvadratsumma << endl;
  }
  cout << "Det är mest troligt att språket är " << sprak[sprak_mest_likt];
}

string namn_pa_fil(){
  string filnamn;
  cout << "Ange filnamn:" << endl;
  cin >> filnamn;
  if(filnamn.substr(filnamn.length() - 4) == ".txt"){ // lägger till ".txt" till inmatningen och strängen inte innehåller ".txt" på slutet
  } else {
    filnamn = filnamn + ".txt";
  }
  cout << endl;
  return filnamn;
}

string inlasning(string filnamn){
  ifstream fil(filnamn);
  string str, text;
  while(getline(fil, str)){ 
    text += str; // lägger till varje rad i texten till en annan sträng
  }

  if(text.empty()){
    cout << "Det finns ingen fil med namnet " << filnamn;
    exit(1);
  }
  return text;
}

int main()
{
  double ant_bok[ANTAL_BOKSTAVER] = { 0 };

  int ascii_A = int('A');
  string filnamn = namn_pa_fil();
  string text = inlasning(filnamn);
  char antal[text.length()];

  for(int i = 0; i < sizeof(antal); i++){
    antal[i] = toupper(text[i]); // ser till så arrayen består av stora bokstäver
  }
  int antal_langd = text.length();

  berakna_histogram_abs(antal, ant_bok, ascii_A, antal_langd);

  abs_till_rel(ant_bok);

  tolkning(ant_bok);

  cout << endl << endl;

  plotta_histogram_rel(ant_bok, ascii_A);

  return 0;
}