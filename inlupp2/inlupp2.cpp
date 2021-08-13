#include <iostream>

using namespace std;

int main() {
  int startnummer = 1, tavlande = 0, tavlandeforst, timmeStart, timmeMal, minutStart, minutMal, sekundStart, sekundMal, Tim = 0, Min = 0, Sek = 0, rekordTim = 100, rekordMin = 100, rekordSek = 100;

  while (startnummer >= 1) {
    cout << "Startnummer? ";
    cin >> startnummer;
    if (startnummer <= 0) {
      break;
    }
    cout << "Starttid? ";
    cin >> timmeStart >> minutStart >> sekundStart;
    cout << "Måltid? ";
    cin >> timmeMal >> minutMal >> sekundMal;
    tavlande++;
    
    
    if (timmeStart >= timmeMal) {
      Tim = 24 - timmeStart + timmeMal;
      
    } else {
      Tim = timmeMal - timmeStart;
    }
    if (minutStart >= minutMal) {
      Min = 60 - minutStart + minutMal;
      Tim = Tim-1;
    } else {
      Min = minutMal - minutStart;
      
    }
    if (sekundStart >= sekundMal) {
      Sek = 60 - sekundStart + sekundMal;
      Min = Min-1;
      
    } else {
      Sek = sekundMal - sekundStart;
    }
    // kontrollerar att sekunder och minuter inte överskrider 60
    if(Sek >= 60){
        Min++;
        Sek = Sek - 60;
    }
    if(Min >= 60){
        Tim++;
        Min = Min - 60;
    }
    if(Tim == 24){
        Tim = Tim - 24;
    }
      // lägger till den tävlande om den är snabbast
    if (((Tim) < rekordTim) || (((Tim) <= rekordTim) && ((Min) < rekordMin)) || ((((Tim) <= rekordTim) && ((Min) <= rekordMin) && ((Sek) < rekordSek)))) {
      tavlandeforst = startnummer;
      rekordTim = Tim;
      rekordMin = Min;
      rekordSek = Sek;
    }

  }
  if (tavlande != 0) {
    cout << "Vinnare är startnr: " << tavlandeforst << endl;
    cout << "Tim: " << rekordTim << " Min: " << rekordMin << " Sek: " << rekordSek << endl;
    cout << "Antal tävlande: " << tavlande << endl;
  } else {
    cout << "Inga tävlade" << endl;
  }

  cout << "Programmet avslutas" << endl;

  return 0;
}