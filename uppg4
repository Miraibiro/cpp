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
int berakna_histogram_abs(char bokstav, char bokstaver[]);

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
  int vilkenBokstav, totalt = 0;

  // Läs in en rad med text från tangentbordet
  cout << "Ge en rad med text:" << endl;
  getline(cin, mening);

  // Anropa funktionen berakna_histogram_abs som beräknar histogrammet
  // och antalet bokstäver.  
  for(int i=0; i<mening.length(); i++){
    vilkenBokstav = berakna_histogram_abs(mening.at(i), bokstaver);
    if (0 <= vilkenBokstav && vilkenBokstav < 26){
      histogram[vilkenBokstav]++;
      totalt++;
    }
  }

  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
  skriv_histogram_abs(histogram, bokstaver, totalt);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:
int berakna_histogram_abs(char bokstav, char bokstaver[]){
  bokstav = tolower(bokstav);

  for(int i=0; i<ANTAL_BOKSTAVER; i++){
    if(bokstav == bokstaver[i]){
      return i;
    }
  }
  
  return -1;
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
