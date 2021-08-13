#include <iostream>
using namespace std;

// Deklarationer av funktionerna
void skrivInfo(){
  cout << "Programmet kräver inmatning av två heltal följd av en bokstav (a,m eller k)" << endl;
}

int lasEttTal(){
  int tal;
  cout << "Var snäll och skriv ett värde: ";
  cin >> tal;
  return tal;
}

char lasOp(){
  char tecken;
  cout << "Var snäll och skriv bokstav (a, m eller k): ";
  cin >> tecken;
  return tecken;
}

void ordna(int &tal1,int &tal2){
  if(tal1 > tal2){
    int temp = tal1;
    tal1 = tal2;
    tal2 = temp;
    
  }
}

int berakna(int tal1, int tal2, char op){
  int svar = 0;

  if(op == 'a'){
    for(tal1; tal1 <= tal2; tal1++){
      svar += tal1;
    }
    return svar;
  } else if(op == 'm'){
      svar = 1; // för att multiplikationen ska fungera
    for(tal1; tal1 <= tal2; tal1++){
      svar *= tal1;
    }
    return svar;
  } else if(op == 'k'){
    for(tal1; tal1 <= tal2; tal1++){
      svar += tal1*tal1;
    }
    return svar;
  } else {
    cout << "Fel!";
  }

  return 0;
}

void skrivResultat(int svar){
  cout << "Resultat: " << svar << endl;
}
// Globala variabler, dvs att deklarera 
// variabler utanför funktionerna är ej tillåtet

int main()
{  
  // Här ska deklaration av variabler finnas
  int tal1, tal2, svar;
  char op;
  
  skrivInfo();

  tal1 = lasEttTal();

  tal2 = lasEttTal();

  op = lasOp();

  ordna(tal1, tal2);

  svar = berakna(tal1, tal2, op);

  skrivResultat(svar);

  return 0;
}
// Definitioner av funktionerna