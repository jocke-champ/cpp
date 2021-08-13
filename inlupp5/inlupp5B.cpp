
// Hanterar fallet med 26 bokst�ver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:
const int ANTAL_BOKSTAVER = 26;  // A-Z
const int ANTAL_SPRAK = 4;

const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, // engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, // franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  // svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, // tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

// Globala variabler �r ej till�tna

//--------------------------------------------------------
// H�r kommer klassdeklarationen

class Text{
  private:
    string text;
    int histo[ANTAL_BOKSTAVER] = { 0 };
    int histoLangd = 0;
    double histoRel[ANTAL_BOKSTAVER] = { 0 };
  
  public:

    void setText(const string &nyText){
      text = nyText;
    }
  
    bool beraknaHistogramAbs(){ //int* &histo, int &histoLangd,
      if(!text.empty()){

        for(int i = 0; i <= text.length(); i++){
          text[i] = toupper(text[i]);
          if(text[i] >= 'A' && text[i] <= 'Z'){
            histo[int(text[i]-'A')]++;
            histoLangd++;
          }
        }
        
        return true;
      } else {
        return false;
      }
      //om inte tom returnera True
    }
  
    void skrivHistogramAbs(){ // int* histo, int histoLangd
      cout << "Resultat för bokstäverna A-Z" << endl << endl;
      cout << "Totala antalet bokstäver: " << histoLangd << endl;
      cout << "Bokstavsfördelning:" << endl << endl;

      for(char bokstav = 'A'; bokstav <= ('A' + ANTAL_BOKSTAVER - 1);bokstav++){
        cout << bokstav << ": " << histo[int(bokstav-'A')] << endl;
      }
    }

    
    void absTillRel(){
        for(int i = 0; i <= ANTAL_BOKSTAVER;i++){
            histoRel[i] = histo[i]*100/(double)histoLangd;
        }
    }

    void plottaHistogramRel(){
        string sprak;

        cout << "Totala antalet bokstäver: " << histoLangd << endl;
        sprak = tolka();
        cout << "Det är mest troligt att språket är " << sprak << "." << endl;
        cout << "Bokstavsfördelning:" << endl << endl;

        for(char bokstav = 'A'; bokstav <= ('A' + ANTAL_BOKSTAVER - 1);bokstav++){
        cout << bokstav << ": ";
            for(int i = 0; i <= floor(histoRel[int(bokstav-'A')])*2-1; i++){
                cout << "*";
            } cout << endl;
      }
    }

    void beraknaHistogram(){
        if(beraknaHistogramAbs()){
            absTillRel();
        } else exit(1);
    }

    string tolka(){
        string sprak[ANTAL_SPRAK] = {"engelska", "franska", "svenska", "tyska"};
        int sprak_mest_likt;
        double kvadratsumma, sprak_lagst = 0;

        for(int i = 0; i < ANTAL_SPRAK; i++){
            kvadratsumma = 0;
            for(int j = 0; j < ANTAL_BOKSTAVER; j++){
            kvadratsumma += abs((histoRel[j] - TOLK_HJALP[i][j])*(histoRel[j] - TOLK_HJALP[i][j])); //kvadratsumman
            }
            if((kvadratsumma < sprak_lagst) || (sprak_lagst == 0)){
            sprak_mest_likt = i;
            sprak_lagst = kvadratsumma;
            }

            cout << sprak[i] << " har kvadratsumma = " << kvadratsumma << endl;
        }
        return sprak[sprak_mest_likt];
    }
  
  
};

// -------------------------------------------------------

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

// Huvudprogram:

int main()
{
 // Deklarera variabler
  string filnamn = namn_pa_fil();
  string text = inlasning(filnamn);
  Text minText;  // Ett objekt av typen Text skapas

  // Skicka str�ngen text till objektet minText
  minText.setText( text );

  // Ber�kna och skriv ut histogrammet
  minText.beraknaHistogram();
  minText.plottaHistogramRel();

  return 0;
}