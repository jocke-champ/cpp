#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int MAX_PERSONER = 10, MAX_TRANSAKTIONER = 30;

class Transaktion{
    private:
        string datum, typ, namn, kompisar[MAX_PERSONER];
        double belopp;
        int antal_kompisar;

    public:
        Transaktion();
        ~Transaktion(){};
        string hamtaNamn();
        double hamtaBelopp();
        string hamtaKompis(int i);
        int    hamtaAntalKompisar();
        bool   finnsKompis(const string &namnet);
        bool   lasIn(istream &is);
        void   skrivUt(ostream &os);
        void   skrivTitel(ostream &os);
   
};

Transaktion::Transaktion() : belopp(0.0), antal_kompisar(0){}

// Metoderna hamtaNamn, hamtaAntalKompisar och hamtaBelopp är s k selektorer, 
// som returnerar motsvarande attributvärden.
string Transaktion::hamtaNamn(){return namn;}
double Transaktion::hamtaBelopp(){return belopp;}
int Transaktion::hamtaAntalKompisar(){return antal_kompisar;}

// Metoden finnsKompis letar igenom arrayen kompisar och returnerar true om namnet finns, annars false.
bool Transaktion::finnsKompis(const string &namnet){
    for(auto s : kompisar){if(s == namnet){return true;}}return false;}

// Metoden skrivUt skriver ut information om ett objekt (dvs "aktuella objektet" tillhörande denna klass), 
// dvs attributens värden, antingen till en fil eller till skärmen. 
// Se körexempel nedan. Metoden skrivTitel skriver ut titeln som beskriver vad som står i kolonner för metoden skrivUt.

void Transaktion::skrivUt(ostream &os){
    os << datum << " " << typ << " " << namn << " " << belopp << " " << antal_kompisar;
    for(int i = 0; i < antal_kompisar; i++){os << " " << kompisar[i];}
    os << endl;
}
void Transaktion::skrivTitel(ostream &os){
  os << "Datum  Typ  Namn  Belopp  Antal  och lista av kompisar" << endl;
}

// Metoden lasIn läser data om en transaktion (kvitto) från tangentbord eller en fil. Denna är av typen bool,
// eftersom den kan komma att anropas från klassen TransaktionsLista:s metod lasIn med en loop av typen

bool Transaktion::lasIn(istream &is){
    bool tom = true;
    string rad, ord = "";
    string Templista[MAX_PERSONER+4];
    int upprepningar = 0;
    int i = 0;
    getline(is, rad);
    rad = rad + " ";
        for(char x : rad){
            tom = false;
            if(x == ' '){
                if(upprepningar == 0){
                    Templista[i] = ord;
                    i++;
                }
                upprepningar ++;
                ord = "";
            } else {
                upprepningar = 0;
                ord.append(1, x);
            }
        }
    datum = Templista[0];
    typ = Templista[1];
    namn = Templista[2];
    belopp = stoi("600")*1.0;
    antal_kompisar = stoi("5");
    for(int j = 0; j < antal_kompisar; j++){
        kompisar[j] = Templista[j+5];
    }
    return !tom;
}
string Transaktion::hamtaKompis(int i){return kompisar[i];}

class TransaktionsLista{
    private:
        int antal_transaktioner;
        Transaktion transaktioner[MAX_TRANSAKTIONER];
    
    public:
        TransaktionsLista(){};
        ~TransaktionsLista(){};
        void   lasIn(istream & is);
        void   skrivUt(ostream & os);
        void   laggTill(Transaktion & t);
};

// Metoderna lasIn och skrivUt läser in värden till ett TransaktionsLista-objekt från/till fil eller tangentbord/skärm.
// Använder sig av inläsnings- och utskriftsmetoder i klassen Transaktion.

void TransaktionsLista::lasIn(istream & is){
    Transaktion t;
    
    while(t.lasIn(is)){
        laggTill(t);
        
    }
}

// Metoden laggTill ska lägga till ett nytt transaktionsobjekt sist i arrayen transaktioner.

void TransaktionsLista::laggTill(Transaktion & t){
    transaktioner[antal_transaktioner] = t;
    antal_transaktioner++;
}

void TransaktionsLista::skrivUt(ostream & os){
    for(int i=0; i <= antal_transaktioner; i++){
        transaktioner[i].skrivUt(os);
    }}

int main(){
    TransaktionsLista transaktioner;
    std::ifstream is("resa.txt");
    transaktioner.lasIn(is); //kan inte lasa in korrekt, 18/8 23:58

    int operation = 1;
  while (operation != 0)
    {
      cout << endl;
      cout << "Välj i menyn nedan:" << endl;
      cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
      cout << "1. Skriv ut information om alla transaktioner." << endl;

      cin >> operation;
      cout << endl;

      switch (operation)
        {
          case 1:
            {
              transaktioner.skrivUt(cout);
              break;
            }
        }
    }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}