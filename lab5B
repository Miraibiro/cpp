#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

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

//--------------------------------------------------------
// Här kommer klassdeklarationen
class Text
{ 
private: 
    const char bokstaver[ANTAL_BOKSTAVER] = 
    {'a','b','c','d','e','f','g','h','i','j','k','l','m',
    'n','o','p','q','r','s','t','u','v','w','x','y','z'};
    const string sprak[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};

    string mening;
    int totalen;
    int histogram[ANTAL_BOKSTAVER] = {0};
    
    double histogramRel[ANTAL_BOKSTAVER] = {0};
    double kvadratsummaAllaSprak[ANTAL_SPRAK];
    int mestTroligt;
    double kvadratsumma[ANTAL_SPRAK];


public: 
    Text();
    void setText(const string &nyText);
    bool beraknaHistogramAbs();
    void skrivHistogramAbs();
    void absTillRel();
    void plottaHistogramRel();
    void beraknaHistogram();
    string tolka();

};

//--------------------------------------------------------
// Funktionsdeklarationer:
string namn_pa_fil();
string inlasning(string filNamn);

// -------------------------------------------------------
// Huvudprogram:

int main(){
    // Deklarera variabler
    string text, filNamn;
    Text minText;  // Ett objekt av typen Text skapas

    filNamn = namn_pa_fil();
    text = inlasning(filNamn);

    minText.setText(text);

    minText.beraknaHistogram();
    
    minText.plottaHistogramRel();
    
}

// -------------------------------------------------------
// Här skriver du klassimplementationen

Text :: Text(){
  mening = "";
}
// --------------------------------------------------------

void Text :: setText(const string &nyText){
  mening = nyText;
}
// --------------------------------------------------------

bool Text :: beraknaHistogramAbs(){
  int aktuell_bokstav;
  totalen = 0;

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
  if(totalen > 0){
    return true;
  }else{
    return false;
  }
}
// --------------------------------------------------------

void Text :: absTillRel(){
    for(int i=0; i<ANTAL_BOKSTAVER; i++){
        histogramRel[i] = double (histogram[i]) / double (totalen) * 100.0;
    }
}
// --------------------------------------------------------

void Text :: plottaHistogramRel(){
    double delas_med = 0.5;

    cout << endl << "Resultat för bokstäverna A-Z\n" << endl;
    cout << "Totala antalet bokstäver: " << totalen << endl;

    string troligstSprak = tolka();
    for(int i=0; i<ANTAL_SPRAK; i++){
        cout << sprak[i] << " har kvadratsumman = " << setprecision(6) << kvadratsumma[i] << endl;
    }
    cout << "Det är mest troligt att språket är " << troligstSprak << endl;

    cout << endl << "Bokstavsfördelning:\n" << endl;

    for(int i=0; i<ANTAL_BOKSTAVER; i++){
        putchar(toupper(bokstaver[i]));
        cout << " " ;
        // Denna del skriver ut antal '*' för varje bokstav
        // Gör detta med hjälp av % (modulo)
        for(int j=0; j<(int(10.0 * histogramRel[i]) / int(10.0 * delas_med)); j++){
        cout << '*';
        }
        cout << endl;
    }
}
// --------------------------------------------------------

void Text :: beraknaHistogram(){
    if (beraknaHistogramAbs()){
        absTillRel();
    }
}
// --------------------------------------------------------

string Text :: tolka(){
    for(int i=0; i<ANTAL_SPRAK; i++){
        for(int j=0; j<ANTAL_BOKSTAVER; j++){
            kvadratsumma[i] += (histogramRel[j]-TOLK_HJALP[i][j])*(histogramRel[j]-TOLK_HJALP[i][j]);
        }
        if(i == 0){
            mestTroligt = i;
        }else{
            if(mestTroligt > kvadratsumma[i]){
                mestTroligt = i;
            }
        }
    }
    return sprak[mestTroligt];
}


// --------------------------------------------------------
// Funktionsdefinitioner:

string namn_pa_fil(){
    string filNamn;
    cout << "Ange filnamn:" << endl;
    getline(cin, filNamn);

    if(filNamn.length() - 4 ==filNamn.rfind(".txt")){
        return filNamn;
    }else{
        return filNamn.append(".txt");
    }
}

string inlasning(string filNamn){  
    ifstream fin(filNamn.c_str());
    // Felkontroll
    if (!fin) {
        cout << "Det finns ingen fil med namnet " << filNamn << endl;
        exit(EXIT_FAILURE);
    }
  
    string filInnehall = "";
    char c;
    while (fin.get(c)){
        filInnehall.push_back(c);
    }

    return filInnehall;
}

