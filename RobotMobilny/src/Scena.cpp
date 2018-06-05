#include "Scena.hh"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Fabryka.hh"

using namespace std;

#define IL_ROB 3  //Ile robotow chcemy na scenie
#define IL_PRZ 3  //Ile przeszkod chcemy na scenie

Scena::Scena()
{
  srand( time(NULL) );
  int x, y, up_or_down;
  const int ZAKRES_X = IL_ROB*50 + 50;
  const int ZAKRES_Y = IL_ROB*50 + 50;  
  
  for(int i = 0; i < IL_ROB; i++){
    x = abs(rand() % 51) + 10 + 60*i;
    
    do{ y = abs(rand() % 101) + 100 - x; }while(y < 10);
    
    cout << "Wspolrzedne Robota: ";
    cout << "x = " << x << " y = " << y << "\n";
    _obiekty.push_back( make_shared<Robot>(Wektor2D(x ,y ), (rand()%360)) );
    _obiekty.push_back( make_shared<Sciezka>(Wektor2D(x ,y ) ) ); 
  }
  
  for(int i = 0; i < IL_PRZ; i++){
    x = abs( rand() % ((ZAKRES_X-20)/IL_PRZ) ) + 10 +i*(ZAKRES_X/IL_PRZ);
    if( x < 20)
      y = abs(rand() % (abs(80-x))) + 10;
    else if( x > 80 )
      y = abs(rand()% (abs(20-x))  ) + 210 - x;
    else{
      up_or_down = abs( rand() % 2);
      if( up_or_down )
	y = abs(rand()% (abs(80-x))) +10;
      else
	y = abs(rand()% (abs(20-x))  ) + 210 - x;
    }
    _obiekty.push_back( make_shared<Prostokat>( Wektor2D(x,y) ) );

  }
  
  list< shared_ptr<ObiektGraficzny> >::iterator it;
  it = _obiekty.begin();
  
  _aktOb = nullptr;
  _aktSciezka = nullptr;
  _aktOb = _obiekty.front();
  ++it;
  _aktSciezka = (*it);
  
  Lacze.DodajNazwePliku("obiekt.dat", PzG::RR_Ciagly,2);
  Lacze.ZmienTrybRys(PzG::TR_2D);
  Lacze.UstawZakresX(0, ZAKRES_X);
  Lacze.UstawZakresY(0, ZAKRES_Y);

  
  if( !ZapisDoPliku("obiekt.dat"))
    cerr << "Blad zapisu do pliku!\n";
  Lacze.Rysuj();
  
}



bool Scena::ZapisDoPliku( const char *sNazwaPliku ) const
{
  ofstream StrmPlikowy;
  
  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open()) {
    cerr << ":( Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"\n"
	 << ":( nie powiodla sie.\n";
    return false;
  }

  for( const shared_ptr<ObiektGraficzny>& wskOb : _obiekty ) 
      wskOb->ZapisDoStrumienia(StrmPlikowy);
  
  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}

bool Scena::operator[]( int ile_Krokow )
{
  if( SprawdzCzyKolizja() )
    return false;
  else
    for(int i=0; i<ile_Krokow; i++){
      _aktOb->Idz();
      if( SprawdzCzyKolizja() ){
	_aktSciezka->NastepnyKrok(_aktOb->centrum());
	ZapisDoPliku("obiekt.dat");
	Lacze.Rysuj();
	return false;
      }
      if( !((i+1)%(_aktOb->Szybkosc())) ){
	_aktSciezka->NastepnyKrok(_aktOb->centrum());
	ZapisDoPliku("obiekt.dat");
	Lacze.Rysuj();
      }
    }
  _aktSciezka->NastepnyKrok(_aktOb->centrum());   
  ZapisDoPliku("obiekt.dat");
  Lacze.Rysuj();
  return true;
}


void Scena::ObrocRobota( int kat )
{
  int malyKat;
  if( kat > 0 )
    malyKat = 2;
  else
    malyKat = -2;
  int stp = (abs(kat)%360)/2;
  
  for(int i=0; i < stp; i++){
    _aktOb->Obrot(malyKat);
    ZapisDoPliku("obiekt.dat");
    Lacze.Rysuj();
  }
  if( stp%2 ){
    _aktOb->Obrot(1);
    ZapisDoPliku("obiekt.dat");
    Lacze.Rysuj();
  }
  _aktOb->ZmienKierunek(kat);
  _aktSciezka->Dodaj(_aktOb->centrum());
}


void Scena::ZmienPolozenie( Wektor2D wek_trans )
{
  cout << "Wektor translacji PRZED przesunieciem: "
	    << ObiektGraficzny::PodajTranslacje() << "\n";
  ObiektGraficzny::ZmienTranslacje(wek_trans); 
  ZapisDoPliku("obiekt.dat");
  Lacze.Rysuj();
  cout << "Wektor translacji PO przesunieciu: "
       << ObiektGraficzny::PodajTranslacje() << "\n";
}

void Scena::UstPoczatkowe()
{
  ZmienPolozenie( -ObiektGraficzny::PodajTranslacje() );
}


void Scena::WypiszWspRobotow()
{
  int i = 1;
  for(const shared_ptr<ObiektGraficzny> &wsk : _obiekty)
    if( wsk->PodajTyp() == ROBOT ){
      cout << "Robot " << i++ << ". ";
      wsk->WyswietlWsp();
    }
}


bool Scena::ZmienRobota( int _nowyRobot )
{
  int i = 0;

  for(const shared_ptr<ObiektGraficzny> &wsk : _obiekty){
    if( wsk->PodajTyp() == ROBOT ){
      ++i;
      if( i == _nowyRobot )
	_aktOb = wsk;
    }
    else if( (wsk->PodajTyp() == SCIEZKA) && (i == _nowyRobot) ){
      _aktSciezka = wsk;
      return true;
    }
  }

  return false;
}


bool Scena::SprawdzCzyKolizja()
{
  for(const shared_ptr< ObiektGraficzny > &wsk : _obiekty )
    if( wsk != _aktOb ){
      if( wsk->PodajTyp() == ROBOT ){
	if( CzyOkregiNachodza(wsk, _aktOb) )
	  return true;
      }else if( wsk->PodajTyp() == PRZESZKODA )
	if (CzyNalezyDoObiektu(wsk, _aktOb) )
	  return true;
    }
  return false;
}
  

bool Scena::CzySieNaloza(const shared_ptr<ObiektGraficzny>& wsk)
{
  if( wsk->PodajTyp() == ROBOT ){
    for( const shared_ptr<ObiektGraficzny> &ptr : _obiekty )
      if( ptr->PodajTyp() == ROBOT ){
	if( CzyOkregiNachodza(ptr, wsk, 5) ){
	  cerr << "Nie mozna ustawic tak blisko innego robota\n";
	  return true; 
	}
      }else if( ptr->PodajTyp() == PRZESZKODA ){
	if( CzyNalezyDoObiektu(ptr, wsk, 5) ){
	  cerr << "Nie mozna ustawic tak blisko przeszkody\n";
	}
      }
  }else if( wsk->PodajTyp() == PRZESZKODA )
    for( const shared_ptr<ObiektGraficzny> &ptr : _obiekty )
      if( ptr->PodajTyp() == ROBOT )
	if( CzyNalezyDoObiektu(wsk, ptr, 5) ){
	  cerr << "Nie mozna ustawic tak blisko robota\n";
	  return true; 
	}   
  return false;
}



bool Scena::Dodaj(char typ)
{ 
  if( typ == 'r' ){
    int x, y;
    cout << "Podaj wspolrzedne robota ( 0 < x,y < 200): \n";
    cin >> x;
    cin >> y;
    
    if( !cin ){
      cin.clear();
      return false;
    }
    if( x < 0 || y < 0 || x > 200 || y > 200){
      cerr << "Blad: Warunki nie spelnione\n";
      return false;
    }
    _obiekty.push_front(FabrykaObjektow::Fabryka().DodajObiekt(SCIEZKA, Wektor2D(x,y)));
      
    _obiekty.push_front(FabrykaObjektow::Fabryka().DodajObiekt(ROBOT, Wektor2D(x,y)));
    cout << "Robot dodany pomyslnie!\n";
    ZapisDoPliku("obiekt.dat");
    Lacze.Rysuj();
    return true;
  }
  if( typ == 'p' ){
    int x = 5, y = 5, a,b;
    cout << "Podaj wspolrzedne przeszkody( 0 < a,b < 200 ) i jej \n"
	      << "wymiary (4 < x, y < 31)\n";
    cin >> a;
    cin >> b;

    if( !cin ){
      cin.clear();
      return false;
    }
    
    if( a<200 && b<200 && x<31 && y<31 && a>0 && b>0 && x>4 && y>4 ){
      _obiekty.push_back(FabrykaObjektow::Fabryka().DodajObiekt(PRZESZKODA, Wektor2D(a,b)));
      cout << "Przeszkoda dodana pomyslnie!\n";
      ZapisDoPliku("obiekt.dat");
      Lacze.Rysuj();
      return true;
    }
    cerr << "Blad: Warunki nie spelnione - nie mozna dodac obiektu\n";
    return false;
  }
  return false;
}



bool Scena::Usun()
{
  char typ;
  int nmr;
  
  ListaObiektow();
  cout << "Ktory obiekt chcesz usunac? \n"
       << "Wpisz r - jesli robota, p - jesli przeszkode, o - zeby wyjsc\n"
       << "a nastepnie podaj numer obiektu\n";
  cin >> typ;
  cin >> nmr;
  if( !cin ){
    cin.clear();
    return false;
  }
  
  int numer_iteracji = 1;
  list< shared_ptr<ObiektGraficzny> >::iterator it;
  
  switch(typ)
    {
    case 'r':
      for( it =_obiekty.begin(); it != _obiekty.end(); ++it )
	if( (*it)->PodajTyp() == ROBOT ){
	  if( numer_iteracji == nmr ){
	    if( _aktOb == (*it) ){
	      cerr << "Blad: Nie mozna usunac aktywnego robota\n";
	      return false;
	    }
	    _obiekty.erase(it);
	    ZapisDoPliku("obiekt.dat");
	    Lacze.Rysuj();
	    return true;
	  }
	  ++numer_iteracji;
	}
      cerr << "Blad: Nie znaleziono podanego obiektu\n";
      return false;
      break;
    case 'p':
      for( it =_obiekty.begin(); it != _obiekty.end(); ++it )
	if( (*it)->PodajTyp() == PRZESZKODA){
	  if( numer_iteracji == nmr ){
	    _obiekty.erase(it);
	    ZapisDoPliku("obiekt.dat");
	    Lacze.Rysuj();
	    return true;
	  }
	  ++numer_iteracji;
	}
      std::cerr << "Blad: Nie znaleziono podanego obiektu\n";
      return false;
      
      break;
      
    case 'o':
      cin.clear();
      return false;
      
    default:
      cerr << "Blad: Nie ma takiego obiektu\n";
      return false;
    }

  return true;
}


void Scena::ListaObiektow()
{
  int nr_rob = 1, nr_prz = 1;
  for(const shared_ptr<ObiektGraficzny> &wsk : _obiekty)
    if( wsk->PodajTyp() == ROBOT ){
      cout << "Robot " << nr_rob++ << ". ";
      wsk->WyswietlWsp();
    }
    else if( wsk->PodajTyp() == PRZESZKODA ){
      cout << "Przeszkoda " << nr_prz++ << ". ";
      wsk->WyswietlWsp();
    }
      

}


bool Scena::SkalujObiekt()
{
  char typ;
  int nmr;
  float skala;
  ListaObiektow();
  cout << "Ktory obiekt chcesz przeskalowac? \n"
	    << "Wpisz r - jesli robota, p - jesli przeszkode, o - zeby wyjsc\n"
	    << "a nastepnie podaj numer obiektu"
	    << "i wartosc mnoznika skali (max. 6)\n";
  cin >> typ;
  cin >> nmr;
  cin >> skala;
  if(!cin){
    cin.clear();
    return false;
  }
  if( skala < 0 || skala > 6 ){
    cerr << "Blad: zla wartosc mnoznika skali\n";
    return false;
  }
   
  int numer_iteracji = 1;

  if( typ == 'r' )
    for( shared_ptr<ObiektGraficzny> &wsk : _obiekty )
      if( wsk->PodajTyp() == ROBOT ){
	if( numer_iteracji == nmr ){
	  wsk->ZmienSkale(skala);
	  cout << "Skalowanie przebieglo pomyslnie!\n";
	  ZapisDoPliku("obiekt.dat");
	  Lacze.Rysuj();
	  return true;
	}
	++numer_iteracji;
      }

  if( typ == 'p' )
    for( shared_ptr<ObiektGraficzny> &wsk : _obiekty )
      if( wsk->PodajTyp() == PRZESZKODA ){
	if( numer_iteracji == nmr ){
	  wsk->ZmienSkale(skala);
	  cout << "Skalowanie przebieglo pomyslnie!\n";
	  ZapisDoPliku("obiekt.dat");
	  Lacze.Rysuj();
	  return true;
	}
	++numer_iteracji;
      }
  cin.clear();
  cerr << "Blad: Wybrany obiekt nie istnieje\n";
  return false;
}


bool Scena::CzyNalezyDoObiektu(const shared_ptr<ObiektGraficzny>& _wsk,
			       const shared_ptr<ObiektGraficzny>& _potwsk,
			       int blad) const
{
  float x_min = (_wsk->Wsp_Xmin())-(_potwsk->Promien())-blad;
  float y_min = (_wsk->Wsp_Ymin())-(_potwsk->Promien())-blad;
  float x_max = (_wsk->Wsp_Xmax())+(_potwsk->Promien())+blad;
  float y_max = (_wsk->Wsp_Ymax())+(_potwsk->Promien())+blad;
  float x_rob = _potwsk->Wsp_X();
  float y_rob = _potwsk->Wsp_Y();

  if( (x_rob >= x_min) && (x_rob <= x_max) )
    if( (y_rob >= y_min) && (y_rob <= y_max) )
      return true;
  return false;
}


bool Scena::CzyOkregiNachodza(const shared_ptr<ObiektGraficzny>& _rob1,
			      const shared_ptr<ObiektGraficzny>& _rob2,
			      int blad) const
{
  Wektor2D OdlSrodkow;
  float SumaPromieni, dlWektora;
  
  SumaPromieni = _rob1->Promien() + _rob2->Promien() + blad; 
  OdlSrodkow = _rob1->centrum() - _rob2->centrum();
  dlWektora = &OdlSrodkow;
  
  return ( (dlWektora <= SumaPromieni) ? true : false );
}
 
 
