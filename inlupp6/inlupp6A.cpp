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

class Transaktion{
    private:
        string datum, typ, namn, kompisar[MAX_PERSONER];
        double belopp;
        int antal_kompisar;

    public:
        Transaktion(){};
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
    string ord = "", rad;
    string Templista[MAX_PERSONER + 4], TempKompis[MAX_PERSONER];
    int upprepningar = 0;
    int i = 0;
    while(getline(is, rad)){
        tom = false;
        for(char x : rad){
        if(x == ' '){
            if(upprepningar == 0){
                Templista[i] = ord;
                i++;
            }
            ord = "";
            upprepningar++;
        } else {
            ord = ord + x;
            upprepningar = 0;
        }}}
        datum = Templista[0];
        typ = Templista[1];
        namn = Templista[2];
        belopp = stod(Templista[3]);
        antal_kompisar = stoi(Templista[4]);
        for(int j = 0; j < antal_kompisar; j++){
            kompisar[j] = Templista[j+5];
        }
    return !tom;
}
string Transaktion::hamtaKompis(int i){return kompisar[i];}

class Person{
    private:
        string namn;
        double betalat_andras, skyldig; //ligguer ute med totalt, respektive skyldig totalt

    public:
        Person(){};
        Person(const string &namn, double betalat_andras, double skyldig){};
        string hamtaNamn();
        double hamtaBetalat();
        double hamtaSkyldig();
        void andraBetalat(double betalat_, double skyldig_);
        void   skrivUt(ostream &os);
};

// Här är metoderna hamtaBetalat och hamtaSkyldig
// s k selektorer som returnerar attributvärden betalat_andras respektive skyldig.

string Person::hamtaNamn(){return namn;}
double Person::hamtaBetalat(){return betalat_andras;}
double Person::hamtaSkyldig(){return skyldig;}

// Metoden skrivUt skriver ut personens namn och hur mycket personen ligger ute med samt är skyldig och vad han/hon skall betala till, 
// eller ta ifrån potten (dvs attributen). Det kan t ex se ut så här:
//  Stina ligger ute med 2500 och är skyldig 1333.33. Skall ha 1166.67 från potten! 

void Person::skrivUt(ostream &os){
    os << hamtaNamn() << "ligger ute med " << hamtaBetalat() << " och är skyldig " << hamtaSkyldig() << ".";
    double summa = hamtaBetalat() - hamtaSkyldig();
    if(summa < 0){os << " Skall betala " << abs(summa) << " till potten!";
    }else{os << " Skall ha " << abs(summa) << " från potten!";
    }
}

void Person::andraBetalat(double betalat_, double skyldig_){
    betalat_andras += betalat_;
    skyldig += skyldig_;
}
class PersonLista{
    private:
        int antal_personer;
        Person personer[MAX_TRANSAKTIONER];
    
    public:
        PersonLista(){};
        ~PersonLista(){};
        void   laggTill(Person ny_person);
        void   skrivUtOchFixa(ostream &os);
        double summaSkyldig();
        double summaBetalat();
        int hamtaAntalPersoner();
        Person hamtaPerson(int i);
        bool   finnsPerson(const string& namn);
};

// Metoden laggTill tar ett personobjekt som inparameter,
// ny_person, och lägger till i arrayen personer, efter den sista personen.

void PersonLista::laggTill(Person ny_person){
    personer[antal_personer] = ny_person;
    antal_personer++;
}

// Metoden skrivUtOchFixa skriver ut information om varje personobjekt i arrayen pers
// samt kollar att det belopp som personer lägger till potten är lika med det belopp som andra personer tar från potten.

void PersonLista::skrivUtOchFixa(ostream &os){
    for(int i = 0; i < antal_personer; i++){
        personer[i].skrivUt(os);
    }
}

double PersonLista::summaSkyldig(){
    double summaSkyldig = 0.;
    for(int i = 0; i < antal_personer; i++){
        summaSkyldig += personer[i].hamtaSkyldig();
    } return summaSkyldig;
}

double PersonLista::summaBetalat(){
    double summaBetalat = 0.f;
    for(int i = 0; i < antal_personer; i++){
        summaBetalat += personer[i].hamtaBetalat();
    } return summaBetalat;
}

// Metoden finnsPerson() returnerar sant om namn finns bland personerna i listan, falskt annars.
// Används lämpligen i FixaPersoner i TransaktionsLista för att undvika att lagra dubletter.

bool PersonLista::finnsPerson(const string& namn){
    for(int i = 0; i < antal_personer; i++){
        if(personer[i].hamtaNamn() == namn){ return true; }
    } return false;
}

int PersonLista::hamtaAntalPersoner(){return antal_personer;}
Person PersonLista::hamtaPerson(int i){return personer[i];}
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
        double totalKostnad();
        double liggerUteMed(const string &namnet);
        double arSkyldig(const string &namnet);
        PersonLista FixaPersoner();
};

// Metoderna lasIn och skrivUt läser in värden till ett TransaktionsLista-objekt från/till fil eller tangentbord/skärm.
// Använder sig av inläsnings- och utskriftsmetoder i klassen Transaktion.

void TransaktionsLista::lasIn(istream & is){
    for(int i = 0; i < antal_transaktioner; i++){
        string s;
        while(getline(is, s)){transaktioner[i].lasIn(is);}
    }
}

void TransaktionsLista::skrivUt(ostream & os){
    for(int i=0; i < antal_transaktioner; i++){
        transaktioner[i].skrivUt(os);
    }
}

// Metoden laggTill ska lägga till ett nytt transaktionsobjekt sist i arrayen transaktioner.

void TransaktionsLista::laggTill(Transaktion & t){
    transaktioner[antal_transaktioner] = t;
    antal_transaktioner++;
}

// Metoden totalKostnad beräknar och returnerar summan av alla utgifter på resan 
// (så man kan jämföra olika år och se om det t ex blir dyrare).

double TransaktionsLista::totalKostnad(){
    double summa = 0.;
    for(int i = 0; i < antal_transaktioner; i++){
        summa += transaktioner[i].hamtaBelopp();
    } return summa;
}

// Metoden liggerUteMed räknar ut hur mycket en viss person,
// dvs med namnet namnet har betalat för andra personer och alltså ligger ute med.
// Detta belopp räknas ut genom att gå igenom alla transaktioner.
// Det är det viktigt att ta bort den del som personen har betalat för sig själv,
// vilket i sin tur beror på antal kompiser.

 double TransaktionsLista::liggerUteMed(const string &namn){
   double summa = 0.;
   for (int i = 0; i < antal_transaktioner; i++)
     if (transaktioner[i].hamtaNamn() == namn)
       summa += transaktioner[i].hamtaBelopp() *
                (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
   return summa;
 }

// Metoden arSkyldig räknar ut hur mycket en viss person, dvs med namnet namnet är skyldig andra,
// vilket igen räknas ut genom att gå igenom alla transaktioner och andelen av personen av transaktionen.

double TransaktionsLista::arSkyldig(const string &namn) {
   double summa = 0.;
   for (int i = 0; i < antal_transaktioner; i++)
     if (transaktioner[i].hamtaNamn() == namn)
       summa += transaktioner[i].hamtaBelopp() *
                (1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
   return summa;
 }

//  Metoden FixaPersoner ska skapa och returnera ett objekt av typen
//  PersonLista genom att gå igenom transaktionslistan och
//  plocka ut alla unika personer som förekommer i transaktionerna.
//  Metoden skall för varje person ta reda på hennes speciella egenskaper
//  (dvs hur mycket pengar hon ligger ute med åt andra personer totalt,
//  samt hur mycket hon själv är skyldig de andra totalt),
//  sedan skall personobjekt skapas som läggs till objektet av typen PersonLista,
//  som slutligen returneras.
//  Dvs man bygger upp med fler och fler personer till
//  den array som är attribut inne objekt av typen PersonLista.

// Detta är en viktig metod i klassen.
// I denna metod så är alltså ett delproblem att helt enkelt ta reda på alla olika
// (unika) namn som finns på personer i transaktionslistan.

PersonLista TransaktionsLista::FixaPersoner(){
    PersonLista p;

    // gå igenom en transaktion i taget, om namnet inte finns i en array,
    // lägg till den i array, hämta sedan betalat() och skyldig() från namn
    // och lägg till i Personlista.person med index av namn
    // och lägg updpatera värden på skyldig så += belopp, resp skyldig.
    // returnera sedan personlistan p.

    // lägger in namn i namn-array
    string namn[MAX_PERSONER];
    for(int i = 0; i < antal_transaktioner; i++){
        for(int j = 0; j < MAX_PERSONER; j++){
            if(namn[j] == transaktioner[i].hamtaNamn()){
            } else {namn[i] = transaktioner[i].hamtaNamn();}}}

    //lägger till namnen till PersonLista p
    for(int i = 0; i < MAX_PERSONER; i++){
        if(!namn[i].empty()){
            Person temp(namn[i], 0, 0);
            p.laggTill(temp);
        }
    }

    //fixar värden för att personer i PersonLista p
    for(int i = 0; i < antal_transaktioner; i++){
        int kompisarTot = 0;
        kompisarTot = transaktioner[i].hamtaAntalKompisar();
        for(int j = 0; j < MAX_PERSONER; j++){
            if(namn[j] == transaktioner[i].hamtaNamn()){
                for(int k = 0; k < p.hamtaAntalPersoner(); k++){
                    if(namn[j] == p.hamtaPerson(k).hamtaNamn()){
                        p.hamtaPerson(k).andraBetalat(transaktioner[i].hamtaBelopp(), 0);
                        
                        for(int l = 0; l < MAX_PERSONER; l++){
                            if(transaktioner[i].hamtaKompis(j) == p.hamtaPerson(l).hamtaNamn()){
                                p.hamtaPerson(l).andraBetalat(0, (transaktioner[i].hamtaBelopp() / 5));
                            }
                        }
                    }
                }
            }
        }
    }
    return p;
}

int main()
{
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
      cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
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
              PersonLista lista = transaktioner.FixaPersoner();
              lista.skrivUtOchFixa(cout);
              break;
            }
        }
    }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}