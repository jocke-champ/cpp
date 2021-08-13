// Man räknar ut vad varje person är skyldig de andra personerna totalt (utan att bry sig om vilka som var med och i vilket sammanhang man blev skyldig).
// Man räknar ut hur mycket varje person har lagt ut åt andra personer totalt (utan att bry sig om vilka som var med vid de olika tillfällena).
// Man talar man om för alla som är skyldiga andra personer pengar att de skall lägga dem i potten.
// Man säger åt alla som ligger ute med pengar att hämta dem från potten.
// Man kollar att det gick jämnt ut :-)

// namn efter rad 16 i txt, rad 24 summa, 32 antal, 40 first, 48 andra, 57 tredje, 65 sista

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int MAX_PERSONER = 10, MAX_TRANSAKTIONER = 30;

class Person
 {
 private:
   string namn;
   double betalat_andras; // ligger ute med totalt
   double skyldig;        // skyldig totalt

 public:
   Person();
   Person(const string &namn, double betalat_andras, double skyldig);
   double hamtaBetalat();
   double hamtaSkyldig();
   void   skrivUt(ostream &os);
};

class PersonLista
 {
 private:
   int    antal_personer;
   Person personer[MAX_PERSONER];

 public:
   PersonLista();
   ~PersonLista();
   void   laggTill(Person ny_person);
   void   skrivUtOchFixa(ostream &os);
   double summaSkyldig();
   double summaBetalat();
   bool   finnsPerson(const string& namn);
    // ...eventuellt div. annat...
 }; 

class Transaktion
 {
 private:
   string datum;
   string typ;
   string namn;
   double belopp;
   int    antal_kompisar;
   string kompisar[MAX_PERSONER];

 public:
   Transaktion();
   Transaktion(string datum, strin typ, string namn, double belopp, int antal_kompisar, string* kompisar);
   ~Transaktion();
   string hamtaNamn();
   double hamtaBelopp();
   int    hamtaAntalKompisar();
   bool   finnsKompis(const string &namnet);
   bool   lasIn(istream &is);
   void   skrivUt(ostream &os);
   void   skrivTitel(ostream &os);
    // ...eventuellt div. annat...
 }; 

 class TransaktionsLista
 {
 private:
   int antal_transaktioner;
   Transaktion transaktioner[MAX_TRANSAKTIONER];

 public:
   TransaktionsLista();
   ~TransaktionsLista();
   void   lasIn(istream & is);
   void   skrivUt(ostream & os);
   void   laggTill(Transaktion & t);
   double totalKostnad();
   double liggerUteMed(const string &namnet);
   double arSkyldig(const string &namnet);
   PersonLista fixaPersoner();
    // ...eventuellt div. annat...
 }; 

Transaktion::Transaktion(string datum, string typ, string namn, double belopp, int antal_kompisar, string* kompisar){
  Transaktion::datum = datum;
  Transaktion::typ = typ;
  Transaktion::namn = namn;
  Transaktion::belopp = belopp;
  Transaktion::antal_kompisar = antal_kompisar;
}
string Transaktion::hamtaNamn(){
   return namn;
   }
int Transaktion::hamtaAntalKompisar(){
  return antal_kompisar;
  }
double Transaktion::hamtaBelopp(){
  return belopp;
  }
bool Transaktion::finnsKompis(const string &namnet){
  for(int i = 0; i < MAX_PERSONER; i++) if(kompisar[i] == namnet) return true;
  return false;
}
bool Transaktion::lasIn(istream &is){

  string s;
  is >> s;
  string hallKoll[MAX_PERSONER+3]; // MAX_PERSONER+3 för max i kvitto
  string soker = " "; 
  int mellanrumPos, nuPos = 0, j = 0,  tidigarePos = 0;

    while(!is.eof()){
      do{
    mellanrumPos = s.find(soker, nuPos);
    if(mellanrumPos >= 0){
      nuPos = mellanrumPos;
      hallKoll[j] = s.substr(tidigarePos, nuPos - tidigarePos);
      nuPos++;
      tidigarePos = nuPos;
      j++;
    }
  } while(mellanrumPos >= 0);
  hallKoll[j] = s.substr(tidigarePos, s.length());
  }
  

  // 0 = datum, 1 = typ av köp, 2 = köpare, 3 = pris, 4 = hur många som var med i köpet, 5+ = skyldiga köpare

    for(int k = 0; k < MAX_PERSONER+3; k++){
      if(!hallKoll[k].empty()){
        switch(k){
          case 0:
            transaktioner.datum = stoi(hallKoll[k]);
            break;
          case 1:
            transaktioner.typ = hallKoll[i][k];
            break;
          case 2:
            transaktioner[i].namn = hallKoll[i][k];
            break;
          case 3:
            transaktioner[i].belopp = stod(hallKoll[i][k]);
            break;
          case 4:
            transaktioner[i].antal_kompisar = stoi(hallKoll[i][k]);
            break;
          default:
            transaktioner[i].kompisar[k-5] = hallKoll[i][k];
            break;
        }
      } else{

      }
    }
   
    for(int k = 0; k < kvitto.size(); k++){
      if(kvitto[k] != " "){
        switch(k){
          case 0:
            datum = stoi(kvitto[k]);
            break;
          case 1:
            typ = kvitto[k];
            break;
          case 2:
            namn = kvitto[k];
            break;
          case 3:
            belopp = stod(kvitto[k]);
            break;
          case 4:
            antal_kompisar = stoi(kvitto[k]);
            break;
          default:
            kompisar[k-5] = kvitto[k];
            break;
        }
      }
    }

}
void Transaktion::skrivUt(ostream &os){

}
void Transaktion::skrivTitel(ostream &os){
  os << "Datum  Typ  Namn  Belopp  Antal  och lista av kompisar" << endl;
}

double Person::hamtaBetalat(){
  return betalat_andras;
  }
double Person::hamtaSkyldig(){
  return skyldig;
  }
void Person::skrivUt(ostream &os){
  //  Stina ligger ute med 2500 och är skyldig 1333.33. Skall ha 1166.67 från potten! 
}
string Person::hamtaNamn(){
  return namn;
  }
Person::Person(const string &namn, double betalat_andras, double skyldig){
  Person::namn = namn;
  Person::betalat_andras = betalat_andras;
  Person::skyldig = skyldig;
}

void PersonLista::laggTill(Person ny_person){
  bool tom = true;
  int i = 0;
  while(tom){
    if(personer[i] == nullptr){
       personer[i] = ny_person.namn;
       tom = false;
    } else i++;
  }
}
void PersonLista::skrivUtOchFixa(ostream &os){
  os << "Nu skapar vi en personarray och reder ut det hela!" << endl;
  for(int i = 0; i < antal_personer; i++){
    os << personer[i].hamtaNamn() << " ligger ute med " << personer[i].hamtaBetalat();
    << " och är skyldig " << personer[i].hamtaSkyldig();
    double summa = personer[i].hamtaSkyldig() - personer[i].hamtaBetalat();
    cout << ".";
    (summa < 0) ? (os << " Skall ha " << summa << " från potten!") 
    : (os << " Skall lägga " << summa << " till potten!");
  }
}
double PersonLista::summaSkyldig(){
  double summa = 0;
  for(int i = 0; i < MAX_PERSONER; i++){
    summa += personer[i].skyldig;
  }

  return summa;
}
double PersonLista::summaBetalat(){
  double summa = 0;
  for(int i = 0; i < MAX_PERSONER; i++){
    summa += personer[i].betalat_andras;
  }

  return summa;
}
bool PersonLista::finnsPerson(const string& namn){

  for(int i = 0; i < MAX_PERSONER; i++){
    if(personer[i] == namn){
      return true;
    }
  }
  return false;
}

void TransaktionsLista::lasIn(istream &is){

  string s;
  int rader;

  while(!is.eof()){
    getline(is, s);
    rader++;
  }

  antal_transaktioner = rader;

  string hallKoll[rader][MAX_PERSONER+3]; // MAX_PERSONER+3 för max i kvitto

  for(int i = 0; i < rader; i++){
  string soker = " "; 
  int mellanrumPos, nuPos = 0, j = 0,  tidigarePos = 0;

    while(!is.eof()){
      do{
    mellanrumPos = s.find(soker, nuPos);
    if(mellanrumPos >= 0){
      nuPos = mellanrumPos;
      hallKoll[i][j] = s.substr(tidigarePos, nuPos - tidigarePos);
      nuPos++;
      tidigarePos = nuPos;
      j++;
    }
  } while(mellanrumPos >= 0);
  hallKoll[i][j] = s.substr(tidigarePos, s.length());
  }
  }

  // 0 = datum, 1 = typ av köp, 2 = köpare, 3 = pris, 4 = hur många som var med i köpet, 5+ = skyldiga köpare

  for(int i = 0; i < antal_transaktioner; i++){
    for(int k = 0; k < MAX_PERSONER+3; k++){
      if(!hallKoll[i][k].empty()){
        switch(k){
          case 0:
            transaktioner[i].datum = stoi(hallKoll[i][k]);
            break;
          case 1:
            transaktioner[i].typ = hallKoll[i][k];
            break;
          case 2:
            transaktioner[i].namn = hallKoll[i][k];
            break;
          case 3:
            transaktioner[i].belopp = stod(hallKoll[i][k]);
            break;
          case 4:
            transaktioner[i].antal_kompisar = stoi(hallKoll[i][k]);
            break;
          default:
            transaktioner[i].kompisar[k-5] = hallKoll[i][k];
            break;
        }
      }
    }
  }
}
void TransaktionsLista::skrivUt(ostream &os){
  os << "Antal trans = " << antal_transaktioner << endl;
  skrivTitel(os);
  for(int i = 0; i < antal_transaktioner; i++){
    os << transaktioner[i].datum << "  " << transaktioner[i].typ << "  " << transaktioner[i].namn 
    << "  " << transaktioner[i].belopp << "  " << transaktioner[i].antal_kompisar;
    for(int j = 0; j < MAX_PERSONER; j++){
      if(!transaktioner[i].kompisar[j].empty()){
        os << transaktioner[i].kompisar[j] << "  ";
      }
    }
    os << endl;
  }
}
void TransaktionsLista::laggTill(Transaktion & t){
  
  for(int k = 0; k < MAX_PERSONER+3; k++){
        switch(k){
          case 0:
            transaktioner[antal_transaktioner].datum = t.datum;
            break;
          case 1:
            transaktioner[antal_transaktioner].typ = t.typ;
            break;
          case 2:
            transaktioner[antal_transaktioner].namn = t.namn;
            break;
          case 3:
            transaktioner[antal_transaktioner].belopp = t.belopp;
            break;
          case 4:
            transaktioner[antal_transaktioner].antal_kompisar = t.antal_kompisar;
            break;
          default:
            transaktioner[antal_transaktioner].kompisar[k-5] = t.kompisar[k-5];
            break;
        }
    }

  antal_transaktioner++;
}
double TransaktionsLista::totalKostnad(){
  double summa = 0.;

  for(int i=0; i < antal_transaktioner; i++) summa += transaktioner[i].belopp;

  return summa;
}
double TransaktionsLista::liggerUteMed(const string &namnet) const{
   double summa = 0.;
   for (int i = 0; i < antal_transaktioner; i++)
     if (transaktioner[i].hamtaNamn() == namnet)
       summa += transaktioner[i].hamtaBelopp() *
                (1.0 - 1.0 / (transaktioner[i].antalKompisar() + 1));
   return summa;
 }
double TransaktionsLista::arSkyldig(const string &namnet)const{
   double summa = 0.;
   for (int i = 0; i < antal_transaktioner; i++)
     if (transaktioner[i].hamtaNamn() == namnet)
       summa += transaktioner[i].hamtaBelopp() *
                (1.0 / (transaktioner[i].antalKompisar() + 1));
   return summa;
 }
PersonLista TransaktionsLista::fixaPersoner(){
  PersonLista p;

  bool finns = false;
  string unika_kompisar[hamtaAntalKompisar()];
  for(int i = 0; i < hamtaAntalKompisar(); i++){
    for(int j = 0; j < MAX_PERSONER; i++ ){
      if(finnsPerson(kompisar[j])){
        for(int k = 0; k < hamtaAntalKompisar(); k++){
          if(unika_kompisar[k] == kompisar[j]){
            finns = true;
          }
        }
        if(!finns){
          unika_kompisar[i] = kompisar[j];
          p.personer[i](unika_kompisar[i], liggerUteMed(unika_kompisar[i]), arSkyldig(unika_kompisar[i]));
        } 
      }
    }
  }
  return p;

}

 int main(){
  cout << "Startar med att läsa från en fil." << endl;

  TransaktionsLista transaktioner;
  std::ifstream     is("resa.txt");
  transaktioner.lasIn(is);

  int operation = 1;
  while (operation != 0)
    {
      cout << endl;
      cout << "Välj i menyn nedan:" << endl;
      cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
      cout << "1. Skriv ut information om alla transaktioner." << endl;
      cout << "2. Läs in en transaktion från tangentbordet." << endl;
      cout << "3. Beräkna totala kostnaden." << endl;
      cout << "4. Hur mycket är en viss person skyldig?" << endl;
      cout << "5. Hur mycket ligger en viss person ute med?" << endl;
      cout << "6. Lista alla personer mm och FIXA" << endl;

      cin >> operation;
      cout << endl;

      switch (operation)
        {
          case 1:
            {
              transaktioner.skrivUt(cout);
              break;
            }
          case 2:
            {
              Transaktion transaktion;
              cout << "Ange transaktion i följande format" << endl;
              transaktion.skrivTitel(cout);
              transaktion.lasIn(cin);
              transaktioner.laggTill(transaktion);
              break;
            }
          case 3:
            {
              cout << "Den totala kostnanden för resan var "
                   << transaktioner.totalKostnad() << endl;
              break;
            }
          case 4:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ar_skyldig = transaktioner.arSkyldig(namn);
              if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " är skyldig " << ar_skyldig << endl;
              break;
            }
          case 5:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ligger_ute_med = transaktioner.liggerUteMed(namn);
              if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
              break;
            }
          case 6:
            {
              cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
              PersonLista lista = transaktioner.fixaPersoner();
              lista.skrivUtOchFixa(cout);
              break;
            }
        }
    }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}