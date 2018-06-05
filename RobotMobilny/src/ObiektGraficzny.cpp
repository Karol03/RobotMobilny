#include "ObiektGraficzny.hh"

Wektor2D ObiektGraficzny::_WekTrans;
int ObiektGraficzny::_IlObStworz;
int ObiektGraficzny::_IlObUsun;

ObiektGraficzny ObiektGraficzny::Obrot(int katObrotu)
{
  _KatLok += katObrotu;
  _KatLok %= 360;
  Macierz2x2 Macierz;
  
  Macierz.MacierzObrotu(_KatLok);
  for(unsigned int i=0; i<_GrafWsp.size(); i++){
    _GrafWsp[i] = Macierz * _WspLok[i];
    _GrafWsp[i] = _GrafWsp[i] + _WspGlob;
  }
  return (*this);    
}


void ObiektGraficzny::ZapisDoStrumienia( ostream& StrmWy ) const
{
  Wektor2D WspRys;
  for(unsigned int i = 0; i < _GrafWsp.size(); i++){
    WspRys =_GrafWsp[i] + _WekTrans;
    StrmWy << setw(16) << fixed << setprecision(10) << WspRys[0]
           << setw(16) << fixed << setprecision(10) << WspRys[1] << endl;
  }
  if( Rodzaj == ROBOT ) {
    WspRys = _GrafWsp[1] + _WekTrans;
    StrmWy << setw(16) << fixed << setprecision(10) << WspRys[0]
	   << setw(16) << fixed << setprecision(10) << WspRys[1] << endl
	   << endl;
  }
  if( Rodzaj == PRZESZKODA ) {
    WspRys = _GrafWsp[0] + _WekTrans;
    StrmWy << setw(16) << fixed << setprecision(10) << WspRys[0]
	   << setw(16) << fixed << setprecision(10) << WspRys[1] << endl
	   << endl;
  }
  StrmWy << endl;
}


float ObiektGraficzny::ZmienSkale(float nowa_skala)
{
  Macierz2x2 Macierz;

  Macierz.MacierzObrotu(_KatLok);
  _Skala = nowa_skala;
  
  for( Wektor2D &wsp : _WspLok)
    wsp = wsp * _Skala;

  for(unsigned int i=0; i<_GrafWsp.size(); i++){
    _GrafWsp[i] = Macierz * _WspLok[i];
    _GrafWsp[i] = _GrafWsp[i] + _WspGlob;
  }

  return _Skala;
}
