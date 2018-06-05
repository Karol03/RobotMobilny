#include "Robot.hh"

Robot::Robot( Wektor2D wek, int _katNachyl ){
  
  _WspLok.reserve(6);
  _GrafWsp.reserve(6);

  _WspLok.push_back( Wektor2D( 3, 0 ) );
  _WspLok.push_back( Wektor2D( 5, 0 ) );
  _WspLok.push_back( Wektor2D( 3, -4 ) );
  _WspLok.push_back( Wektor2D( -3, -4 ) );
  _WspLok.push_back( Wektor2D( -3, 4 ) );
  _WspLok.push_back( Wektor2D( 3, 4 ) );
  _WspGlob = wek;
  _Kierunek = Wektor2D( 1, 0 );
  _Szybkosc = 2;

  
  Macierz2x2 macierz;
  macierz.MacierzObrotu(_katNachyl);
  _Kierunek = macierz * _Kierunek;
  _KatLok += _katNachyl;
  LiczPromien();
  
  for(int i = 0; i < 6; i++)
    _GrafWsp.push_back( (macierz*_WspLok[i]+_WspGlob) );
  
  Rodzaj = ROBOT;

}


const Wektor2D Robot::ZmienKierunek(int Kat)
{
  Macierz2x2 macierz;
  macierz.MacierzObrotu(Kat);
  _Kierunek = macierz*_Kierunek;
  return _Kierunek;
}


void Robot::Idz( int zwolnij )
{
  for(unsigned int i=0; i < _GrafWsp.size(); i++)
    _GrafWsp[i] += _Kierunek;
  _WspGlob += _Kierunek;
}

