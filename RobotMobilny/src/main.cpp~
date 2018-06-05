#include <iostream>
#include <iomanip>
#include <fstream>
#include "Wektor2D.hh"
#include "Macierz2x2.hh"
#include "Prostokat.hh"
#include "Robot.hh"
#include "lacze_do_gnuplota.hh"
#include "ObiektGraficzny.hh"
#include "Scena.hh"
#include "Fabryka.hh"

using namespace std;


/* DEKLARACJE FUNKCJI */
bool menu(Scena&);
void wyswietl();

/**********************************************************/
/*                FUNKCJA          MAIN                   */
/**********************************************************/
int main()
{
  Scena NowaScena;

  wyswietl();
  Wektor2D::Statystyka();
  while( menu(NowaScena) );
}



/*!
 *  Funkcja wyswietla spis mozliwych operacji w programie.
 */
void wyswietl()
{
  cout << "o - obrot robota o zadany kat\n"
       << "i - jazda na wprost\n"
       << "c - wybierz robota\n"
       << "z - zmien szybkosc robota\n\n"
       << "n - nowy obiekt\n"
       << "u - usun obiekt\n"
       << "s - skaluj obiekt\n"
       << "t - translacja rysunku\n"
       << "p - ustawienia poczatkowe\n\n"
       << "m - wyswietl menu\n"
       << "k - koniec dzialania programu\n";
  
}

/*!
 *  Menu glowne programu. 
 *  W tej funkcji uzytkownik podejmuje decyzje o operacji ktora chce wykonac.
 */
bool menu(Scena& NowaScena)
{
  NowaScena.KtoryRobot(); 

  char znak;
  cout << "Twoj wybor? (m - menu) > ";
  cin >> znak;

  switch(znak){
  case 'o':
    int kat;
    cout << "Podaj kat obrotu robota: \n";
    cin >> kat;
    if( cin.good() )
      NowaScena.ObrocRobota(kat);
    else
      cin.clear();
    break;
  case 'i':
    int il_Krok;
    cout << "Podaj dlugosc drogi robota: \n";
    cin >> il_Krok;
    if( cin.good() ){
      if( !NowaScena[il_Krok] )
	cerr << "!!! KOLIZJA \n !!! NIE MOZNA KONTYNUOWAC \n";
    }else
      cin.clear();
    break;
  case 'c':
    int nmr_rob;
    NowaScena.WypiszWspRobotow();
    cout << "Podaj numer robota, ktorym chcesz sterowac: \n";
    cin >> nmr_rob;
    if( !NowaScena.ZmienRobota(nmr_rob) )
      cerr << "Blad: Nie udalo sie zmienic robota\n";
    break;
  case 'z':
    int n_sz;
    cout << "Podaj nowa szybkosc robota: \n";
    cin >> n_sz;
    if( cin.good() )
      NowaScena.Szybkosc(n_sz);
    else
      cin.clear();
    break;
  case 'n':
    char typ;
    cout << "Jakiego typu obiekt chcesz dodac?\n"
	 << "r - robota, p - przeszkode\n";
    cin >> typ;
    if( typ == 'r' || typ == 'p')
      NowaScena.Dodaj(typ);
    else
      cerr << "Blad: Nie ma takiego typu obiektu\n";
    break;
  case 'u':
    NowaScena.Usun();
    break;
  case 's':
    NowaScena.SkalujObiekt();
    break;
  case 't':
    float x,y;
    cout << "Wprowadz wektor translacji sceny (wspolrzedna x oraz y): \n";
    cin >> x;
    cin >> y;
    NowaScena.ZmienPolozenie( Wektor2D(x,y) );
    break;
  case 'p':
    NowaScena.UstPoczatkowe();
    cout << "Przywrocono ustawienia poczatkowe sceny\n";
    break;
  case 'm':
    Wektor2D::Statystyka();
    wyswietl();
    break;
  case 'k':
    cout << "Koniec dzialania programu\n";
    FabrykaObjektow::UsunFabryke();
    return false;
  default:
    break;
  }
  
  return true;
}
