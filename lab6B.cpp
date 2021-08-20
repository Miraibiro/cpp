#include <iostream>
#include <string>
#include <fstream>
using namespace std;

 //-----------------------------------------------------
 class Transaktion
 {
 private:
   string  datum;
   string  typ;
   string  namn;
   double  belopp;
   int     antal_kompisar;
   string *kompisar;

  public:
   Transaktion();
   ~Transaktion();
   Transaktion& operator=( const Transaktion& t);
   string hamtaNamn() const;
   double hamtaBelopp() const;
   int    hamtaAntalKompisar() const;
   bool   finnsKompis(const string &namnet) const;
   bool   lasIn(istream &is);
   void   skrivUt(ostream &os) const;
   void   skrivTitel(ostream &os) const;
   //...eventuellt div. annat...
 }; 

 //-----------------------------------------------------

 class Person
 {
 private:
   string namn;
   double betalat_andras; // ligger ute med totalt
   double skyldig;        // skyldig totalt

 public:
   Person();
   Person(const string &namn, double betalat_andras, double skyldig);
   string hamtaNamn();
   double hamtaBetalat();
   double hamtaSkyldig();
   void   skrivUt(ostream &os);
   // ...eventuellt div. annat...
};

 //-----------------------------------------------------

 class PersonLista
 {
 private:
   int     antal_personer;
   Person *personer;

 public:
   PersonLista();
   ~PersonLista();
   void   laggTill(Person ny_person);
   void   skrivUtOchFixa(ostream &os);
   double summaSkyldig() const;
   double summaBetalat() const;
   bool   finnsPerson(const string &namn);
   //...eventuellt div. annat...
 }; 

 //-----------------------------------------------------

 class TransaktionsLista
 {
 private:
   int          antal_transaktioner;
   Transaktion *transaktioner;

 public:
   TransaktionsLista();
   ~TransaktionsLista();
   void   lasIn(istream & is);
   void   skrivUt(ostream & os);
   void   laggTill(Transaktion & t);
   double totalKostnad() const;
   double liggerUteMed(const string &namnet);
   double arSkyldig(const string &namnet);
   PersonLista FixaPersoner();
   // ...eventuellt div. annat...
 }; 

 //-----------------------------------------------------
 //-----------------------------------------------------
 // Huvudprogram

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
 //-----------------------------------------------------
 //-----------------------------------------------------
 //-----------------------------------------------------
 
    Transaktion :: Transaktion()
    : datum(""), typ(""), namn(""), belopp(0.0), antal_kompisar(0), kompisar(0)
    {}

    Transaktion :: ~Transaktion(){
        delete[] kompisar;
    }
    
    Transaktion& Transaktion :: operator=( const Transaktion& t){
        if (this != &t){
            delete[] kompisar;
            datum          = t.datum;
            typ            = t.typ;
            namn           = t.namn;
            belopp         = t.belopp;
            antal_kompisar = t.antal_kompisar;
            kompisar       = new string[antal_kompisar];
            for (int i=0; i < antal_kompisar; i++)
            kompisar[i] = t.kompisar[i];
        }
        return *this;
    }
    
    string Transaktion :: hamtaNamn() const{
        return namn;
    }

    double Transaktion :: hamtaBelopp() const{
        return belopp;
    }

    int Transaktion :: hamtaAntalKompisar() const{
        return antal_kompisar;
    }

    bool Transaktion :: finnsKompis(const string &namnet) const{
        for(int i=0; i<antal_kompisar; i++){
            if(kompisar[i] == namnet){
                return true;
            }
        }
        return false;
    }

    bool Transaktion :: lasIn(istream &is){
        string ord;
        if(! is.eof()){
            is >> ord;
            datum = ord;

            is >> ord;
            typ = ord;
        
            is >> ord;
            namn = ord;
            
            is >> ord;
            belopp = stold(ord);
            
            is >> ord;
            antal_kompisar = stoi(ord);
            
            kompisar = new string[antal_kompisar];
            for(int i=0; i<antal_kompisar; i++){
                is >> ord;
                kompisar[i] = ord;
            }
            return true;
        }
    return false;
    }

    void Transaktion :: skrivUt(ostream &os) const{
        os << datum << "  ";
        os << typ << "  ";
        os << namn << "  ";
        os << belopp << "  ";
        os << antal_kompisar << "  ";
        for(int i=0; i<antal_kompisar; i++){
            os << kompisar[i] << "  ";
        }
    }

    void Transaktion :: skrivTitel(ostream &os) const{
        os << "Skriv Datum, Typ, Namn på person som betalde, Beloppet, Antal som var med och Namnen på dem som var med:" << endl;
    }


 //-----------------------------------------------------

    TransaktionsLista :: TransaktionsLista()
    : antal_transaktioner(0), transaktioner(0)
    {
    }
    
    TransaktionsLista :: ~TransaktionsLista(){
        delete[] transaktioner;
    }
    
    void TransaktionsLista :: lasIn(istream & is){
        Transaktion t;
    
        while (t.lasIn(is)){
            laggTill(t);
        }
    }

    void TransaktionsLista :: skrivUt(ostream & os){
        os << "Antal trans = " << antal_transaktioner << endl;
        os << "Datum   Typ     Namn    Belopp  Antal och lista av kompisar" << endl;

        Transaktion t;
        for(int i=0; i<antal_transaktioner; i++){
            t = transaktioner[i];
            t.skrivUt(os);
            os << endl;
        }
    }

    void TransaktionsLista :: laggTill(Transaktion & t){
        Transaktion *trans = 0;
        trans = new Transaktion[antal_transaktioner+1];
        for(int i=0; i<antal_transaktioner; i++){
            trans[i] = transaktioner[i];
        }
        trans[antal_transaktioner] = t;
        antal_transaktioner++;

        delete[] transaktioner;
        transaktioner = trans;
    }

    double TransaktionsLista :: totalKostnad() const{
        Transaktion t;
        double total = 0.0;
        for(int i=0; i<antal_transaktioner; i++){
            t = transaktioner[i];
            total += t.hamtaBelopp();
        }
        return total;
    }

    double TransaktionsLista :: liggerUteMed(const string &namnet){
        Transaktion t;
        double ute = 0.0;
        for(int i=0; i<antal_transaktioner; i++){
            t = transaktioner[i];
            if(namnet == t.hamtaNamn()){
                ute += t.hamtaBelopp() * (1.0 - 1.0 / (t.hamtaAntalKompisar()+1)); 
            }
        }
        return ute;
    }

    double TransaktionsLista :: arSkyldig(const string &namnet){
        Transaktion t;
        double skuld = 0.0;
        for(int i=0; i<antal_transaktioner; i++){
            t = transaktioner[i];
            if(t.finnsKompis(namnet)){
                skuld += (t.hamtaBelopp()/double(t.hamtaAntalKompisar()+1));
            }
        }
        return skuld;
    }

    PersonLista TransaktionsLista :: FixaPersoner(){
        PersonLista pl;
        Transaktion t;

        for(int i=0; i<antal_transaktioner; i++){
            t = transaktioner[i];
            if(! pl.finnsPerson(t.hamtaNamn())){
                pl.laggTill(Person(t.hamtaNamn(), liggerUteMed(t.hamtaNamn()), arSkyldig(t.hamtaNamn())));
            }
        }
        return pl;
    }



 //-----------------------------------------------------

    Person :: Person()
    : namn(""), betalat_andras(0.0), skyldig(0.0)
    {

    }

    Person :: Person(const string &namn, double betalat_andras, double skyldig)
    : namn(namn), betalat_andras(betalat_andras), skyldig(skyldig)
    {

    }

    string Person :: hamtaNamn(){
        return namn;
    }

    double Person :: hamtaBetalat(){
        return betalat_andras;
    }

    double Person :: hamtaSkyldig(){
        return skyldig;
    }

    void Person :: skrivUt(ostream &os){
        os << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig;
        if(betalat_andras>skyldig){
            os << ". Skall ha "<< (betalat_andras-skyldig) <<" från potten!";
        }else{
            os << ". Skall lägga " << (skyldig-betalat_andras) << " till potten!";
        }
        
    }

 //-----------------------------------------------------

    PersonLista :: PersonLista()
    : antal_personer(0), personer(0)
    {}

    PersonLista :: ~PersonLista(){
        delete[] personer;
    }

    void PersonLista :: laggTill(Person ny_person){
        Person *p = 0;
        p = new Person[antal_personer+1];
        for(int i=0; i<antal_personer; i++){
            p[i] = personer[i];
        }
        p[antal_personer] = ny_person;
        antal_personer++;

        delete[] personer;
        personer = p;
    }

    void PersonLista :: skrivUtOchFixa(ostream &os){
        Person p;
        for(int i=0; i<antal_personer; i++){
            p = personer[i];
            p.skrivUt(os);
            os << endl;
        }
        if(!(int(summaBetalat()*100.0) == int(summaSkyldig()*100.0))){
            os << "Något blev fel i beräkningarna!" << endl;
        }
    }

    double PersonLista :: summaSkyldig() const{
        double summa = 0.0;
        Person p;
        for(int i=0; i<antal_personer; i++){
            p = personer[i];
            summa += p.hamtaSkyldig();
        }
        return summa;
    }

    double PersonLista :: summaBetalat() const{
        double summa = 0.0;
        Person p;
        for(int i=0; i<antal_personer; i++){
            p = personer[i];
            summa += p.hamtaBetalat();
        }
        return summa;
    }

    bool PersonLista :: finnsPerson(const string &namn){
        Person p;

        for(int i=0; i<antal_personer; i++){
            p = personer[i];
            if(p.hamtaNamn() == namn){
                return true;
            }
        }
        return false;
    }

 //-----------------------------------------------------
