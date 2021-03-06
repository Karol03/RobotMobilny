#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <fstream>
#include "ObiektGraficzny.hh"
#include "Robot.hh"
#include "lacze_do_gnuplota.hh"
#include "Prostokat.hh"
#include <list>
#include <memory>


/*! \file
 * Plik z klasa sceny.
 */

/*!
 * \brief Scena to klasa ktora przedstawia uklad w ktorym dzialaja obiekty.
 */
class Scena{
  PzG::LaczeDoGNUPlota Lacze; //!< Lacze do rysowania w GNU plocie
  std::list< std::shared_ptr<ObiektGraficzny> > _obiekty; //!< Obiekty na scenie
  std::shared_ptr<ObiektGraficzny> _aktOb; //!< Wskaznik na aktywny obiekt
  std::shared_ptr<ObiektGraficzny> _aktSciezka; //!< Sciezka aktywnego robota
  

  /*! \brief Wypisuje liste obiektow na scenie
   *
   */
  void ListaObiektow();

  /*!\brief Czy drugi obiekt zawiera sie w polu pierwszego obiektu
   * \retval zwraca true jezeli zachodzi 
   */
  bool CzyNalezyDoObiektu(const shared_ptr<ObiektGraficzny>&,
			  const shared_ptr<ObiektGraficzny>&,
			  int blad = 0) const;

  /*!\brief Czy okregi nachodza na siebie
   * \retval zwraca true jezeli zachodzi 
   */
  bool CzyOkregiNachodza(const shared_ptr<ObiektGraficzny>&,
			 const shared_ptr<ObiektGraficzny>&,
			 int blad = 0 ) const; 
  
public:
  /*!
   * \brief
   * Konstruktor sceny.
   */
  Scena();
  /*!
   * \brief
   * Metoda zapisuje obiekty graficzne do pliku.
   */
  bool ZapisDoPliku(const char *sNazwaPliku = "obiekt.dat") const;
  /*!
   * \brief
   * Operator jest metoda ruchu robota o dana ilosc krokow
   * \param int ilosc krokow robota
   * \retval false jezeli nastapila kolizja  
   */
  bool operator[](int);
  /*!
   * \brief
   * Obrot robota o dana ilosc stopni
   * \param int kat o jaki obracamy robota
   */
  void ObrocRobota(int);
  /*!
   * \brief
   * Metoda zmienia szybkosc robota 
   * \param int nowa szybkosc robota
   */
  void Szybkosc(int n_sz){ _aktOb->UstawSzybkosc(n_sz); }

  /*!
   * \brief Metoda wykonuje translacje obrazu o zadany wektor
   * \param wektor translacji sceny
   */
  void ZmienPolozenie( Wektor2D );

  /*!
   * \brief Metoda przywraca ustawienia poczatkowe sceny
   */
  void UstPoczatkowe();


  void KtoryRobot() const {
    if( _aktOb != nullptr ){ 
      std::cout << "Aktualnie wybrany robot: \n";
      _aktOb->WyswietlWsp();
    }
  }

  /*! \brief Wypisuje polozenia wszystkich robotow.
   */
  void WypiszWspRobotow();

  /*!
   * \brief Zamienia aktywnego robota na innego podanego w parametrze
   * \param ktorego robota chcemy wybrac
   * \retval true jezeli udalo sie zmienic aktywnego robota
   */
  bool ZmienRobota(int );


  /*!
   * \brief Sprawdza czy nastapila kolizja z przeszkoda
   * \retval true jezeli kolizja nastapila
   */
  bool SprawdzCzyKolizja();

  /*! \brief Skaluje wybrany obiekt
   *  \retval true jezeli operacja skalowania powiodla sie
   */
  bool SkalujObiekt();

  bool CzySieNaloza(const shared_ptr<ObiektGraficzny>& );


  bool Dodaj(char typ);
  bool Usun( );
};





#endif
