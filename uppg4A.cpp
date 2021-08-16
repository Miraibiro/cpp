//
// Programskal till inlämningsuppgift 4 - deluppgift A
//
// Hanterar fallet med 26 bokstäver A-Z

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;


// Använd gärna denna globala konstant i programmet
// i stället för värdet 26
const int ANTAL_BOKSTAVER = 26;  //A-Z
// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:
// Använd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
int berakna_histogram_abs(string mening, char bokstaver[], int histogram[]);

// Funktionen skriv_histogram_abs
void skriv_histogram_abs(int histogram[], char bokstaver[], int totalt);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
  string mening;
  int histogram[ANTAL_BOKSTAVER] = {0};
  char bokstaver[ANTAL_BOKSTAVER] = 
  {'a','b','c','d','e','f','g','h','i','j','k','l','m',
  'n','o','p','q','r','s','t','u','v','w','x','y','z'};

  // Läs in en rad med text från tangentbordet
  cout << "Ge en rad med text:" << endl;
  getline(cin, mening);

  // Anropa funktionen berakna_histogram_abs som beräknar histogrammet
  // och antalet bokstäver.  
  int totalt = berakna_histogram_abs(mening, bokstaver, histogram);

  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
  skriv_histogram_abs(histogram, bokstaver, totalt);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:
int berakna_histogram_abs(string mening, char bokstaver[], int histogram[]){  
  int aktuell_bokstav;
  int totalen = 0;

  // yttre loopen går igenom meningen
  for(int i=0; i<mening.length(); i++){
    // inre loopen kollar om bokstaven i meningen finns
    // i bokstaver och itererar isåfall histogram och totalen
    aktuell_bokstav = tolower(mening.at(i));
    for(int j=0; j<ANTAL_BOKSTAVER; j++){
      if(aktuell_bokstav == bokstaver[j]){
        histogram[j]++;
        totalen++;
      }
    }
  }
  return totalen;
}

void skriv_histogram_abs(int histogram[], char bokstaver[], int totalt){
  cout << endl << "Resultat för bokstäverna A-Z\n" << endl;
  cout << "Totala antalet bokstäver: " << totalt << endl;
  cout << "Bokstavsfördelning:\n" << endl;

  for(int i=0; i<ANTAL_BOKSTAVER; i++){
    putchar(toupper(bokstaver[i]));
    cout << ": " << histogram[i] << endl;
  }
}


// Redovisning av uppgiften i ord. 

// Variabeln histogram har jag gjort så att alla värden är lika med 0 i början och sedan går det upp ett för varje gång 
// berakna_histogram_abs hittar en bokstav mellan A-Z så kommer den att returera index platsen för den i histogrammet. 
// Sedan vid utskrivning skrivs bokstaven ut och även antalet gånger bokstaven förekom (histogrammets värde för den bokstaven).
// 
