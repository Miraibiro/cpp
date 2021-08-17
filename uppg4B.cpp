//
// Programskal till inlämningsuppgift 4 - deluppgift B
//
// Hanterar fallet med 26 bokstäver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

// Tips: Använd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// istället för värdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26; //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP innehåller bokstavsfrekvensen i %
// för fyra språk. TOLK_HJALP[0][0] är frekvensen av
// bokstaven a för engelska. TOLK_HJALP[0][25] är frekvensen av
// bokstaven z för engelska.
// Arrayen är en GLOBAL KONSTANT och skall alltså ej skickas
// som parameter till den funktion som behöver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER] =
    {{8.27, 1.48, 2.94, 4.03, 11.78, 2.22, 1.72, 6.77, //engelska
      7.39, 0.12, 0.81, 3.76, 2.85, 6.71, 7.79, 1.54,
      0.05, 5.95, 6.69, 9.07, 2.66, 1.13, 2.14, 0.19,
      1.89, 0.03},
     {7.97, 1.40, 3.55, 3.79, 16.89, 1.02, 1.00, 0.75, //franska
      7.08, 0.38, 0.04, 5.51, 2.82, 8.11, 5.19, 2.78,
      1.01, 6.69, 8.35, 7.22, 6.09, 1.35, 0.02, 0.54,
      0.30, 0.15},
     {9.50, 1.11, 1.53, 5.30, 8.94, 1.74, 3.57, 3.94, //svenska
      3.98, 0.89, 3.26, 4.93, 3.41, 8.46, 5.01, 1.77,
      0.00, 6.73, 5.56, 9.20, 1.94, 2.42, 0.00, 0.05,
      0.45, 0.00},
     {5.12, 1.95, 3.57, 5.07, 16.87, 1.35, 3.00, 5.79, //tyska
      8.63, 0.19, 1.14, 3.68, 3.12, 10.64, 1.74, 0.42,
      0.01, 6.30, 6.99, 5.19, 3.92, 0.77, 1.79, 0.01,
      0.69, 1.24}};

// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:

// Deklarationer av dina egna funktioner
// Använd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
// denna skrevs i A-uppgiften och kan klippas in här
int berakna_histogram_abs(char bokstav, char bokstaver[]);

// Funktionen abs_till_rel
double abs_till_rel(int antal, int totalt);

// Funktionen plotta_histogram_rel
void plotta_histogram_rel(double histogramRel[], char bokstaver[], int totalt, string sprak[], double kvadratsumma[], int n);

// Funktionen tolkning
double tolkning(double histogramRel[], const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER], int vilketSprak);

// Funktionen namn_pa_fil
string namn_pa_fil();

// Funktionen inlasning
string inlasning(string filNamn);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
  string mening, filNamn;
  int histogram[ANTAL_BOKSTAVER] = {0};
  double histogramRel[ANTAL_BOKSTAVER] = {0};
  char bokstaver[ANTAL_BOKSTAVER] =
      {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  string sprak[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};
  int vilkenBokstav, totalt = 0;
  double bestResult;
  int mestTroligt = 0;
  double kvadratsummaAllaSprak[ANTAL_SPRAK];

  filNamn = namn_pa_fil();

  mening = inlasning(filNamn);

  for (int i = 0; i < mening.length(); i++)
  {
    vilkenBokstav = berakna_histogram_abs(mening.at(i), bokstaver);
    if (0 <= vilkenBokstav && vilkenBokstav < 26)
    {
      histogram[vilkenBokstav]++;
      totalt++;
    }
  }

  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    histogramRel[i] = abs_till_rel(histogram[i], totalt);
  }

  bestResult = kvadratsummaAllaSprak[0] = tolkning(histogramRel, TOLK_HJALP, 0);
  for (int i = 1; i < ANTAL_SPRAK; i++)
  {
    kvadratsummaAllaSprak[i] = tolkning(histogramRel, TOLK_HJALP, i);
    if (bestResult > kvadratsummaAllaSprak[i])
    {
      mestTroligt = i;
      bestResult = kvadratsummaAllaSprak[i];
    }
  }

  plotta_histogram_rel(histogramRel, bokstaver, totalt, sprak, kvadratsummaAllaSprak, mestTroligt);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:
int berakna_histogram_abs(char bokstav, char bokstaver[])
{
  bokstav = tolower(bokstav);

  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    if (bokstav == bokstaver[i])
    {
      return i;
    }
  }

  return -1;
}
// -------------------------------------------------------

double abs_till_rel(int antal, int totalt)
{
  return double(antal) / double(totalt) * 100.0;
}
// -------------------------------------------------------

void plotta_histogram_rel(double histogramRel[], char bokstaver[], int totalt, string sprak[], double kvadratsumma[], int n)
{
  double delas_med = 0.5;

  cout << endl
       << "Resultat för bokstäverna A-Z\n"
       << endl;
  cout << "Totala antalet bokstäver: " << totalt << endl;

  for (int i = 0; i < ANTAL_SPRAK; i++)
  {
    cout << sprak[i] << " har kvadratsumman = " << setprecision(6) << kvadratsumma[i] << endl;
  }
  cout << "Det är mest troligt att språket är " << sprak[n] << endl;

  cout << endl
       << "Bokstavsfördelning:\n"
       << endl;

  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    putchar(toupper(bokstaver[i]));
    cout << " ";
    // Denna del skriver ut antal '*' för varje bokstav
    // Gör detta med hjälp av % (modulo)
    for (int j = 0; j < (int(10.0 * histogramRel[i]) / int(10.0 * delas_med)); j++)
    {
      cout << '*';
    }
    cout << endl;
  }
}
// -------------------------------------------------------

double tolkning(double histogramRel[], const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER], int vilketSprak)
{
  double kvadratsumman = 0;

  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    kvadratsumman += (histogramRel[i] - TOLK_HJALP[vilketSprak][i]) * (histogramRel[i] - TOLK_HJALP[vilketSprak][i]);
  }

  return kvadratsumman;
}
// -------------------------------------------------------

string namn_pa_fil()
{
  string filNamn;
  cout << "Ange filnamn:" << endl;
  cin >> filNamn;

  if (filNamn.length() - 4 == filNamn.rfind(".txt"))
  {
    return filNamn;
  }
  else
  {
    return filNamn.append(".txt");
  }
}
// -------------------------------------------------------

string inlasning(string filNamn)
{
  ifstream fin(filNamn.c_str());
  // Felkontroll
  if (!fin)
  {
    cout << "Det finns ingen fil med namnet " << filNamn << endl;
    exit(EXIT_FAILURE);
  }

  string filInnehall = "";
  char c;
  while (fin.get(c))
  {
    filInnehall.push_back(c);
  }

  return filInnehall;
}
// -------------------------------------------------------
// Rapport om uppgiften
// Den var klurig vill jag påstå. Det stod att man skulle göra felhanterande av icke existerande filer i HP men valde att göra det i
// metoden inlasning istället då det kändes passande att göra det där.
// För att se om ".txt" fanns i slutet av filnamnet man matade in koltrollerade jag om det fanns på indexplatsen som var fjärde längst bak eller ej
// annars la jag till det i slutet innan jag skicakde tillbaka det till HP.
// Vid plottning av histogrammet skickade jag in i princip all information som behövdes för att skriva ut allt på skärmen.
// Därför skickas det in många olika parameterar in i denna metod.
// Vid omvandligen så gör jag heltal till flyttal och sedan dividerar jag dem med varandra och får fram det relativt till resten.
