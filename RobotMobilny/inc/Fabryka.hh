#include <iostream>
#include <memory>
#include "Scena.hh"
#include "ObiektGraficzny.hh"
#include "Prostokat.hh"
#include "Robot.hh"


/*! \file Plik z realizacja fabryki do tworzenia objektow 
 */

/*! \brief Klasa przedstawia singleton ktory jest fabryka tworzaca nowe obiekty
 * na scene.
 */
class FabrykaObjektow{
  
  static FabrykaObjektow* _Fabryka; //!< Wskaznik statyczny do naszej fabryki

  FabrykaObjektow(){}
  
  public:

  /*! \brief Funkcja statyczna do odwolywania sie do naszej fabryki
   * \retval Zwraca referencje do jedynej kopii fabryki
   */
  static FabrykaObjektow& Fabryka(){ return *_Fabryka; }

  /*! \brief Metoda statyczna do usuniecia fabryki przed zakonczeniem 
   * dzialania programu 
   */
  static void UsunFabryke(){ delete _Fabryka; } 
  
  /*! \brief Dodaje obiekt na scene 
   * \retval true jezeli udalo sie dodac obiekt
   */
  std::shared_ptr<ObiektGraficzny> DodajObiekt(RodzajObiektu, Wektor2D);

  
  /*! \brief Usuwa wskazany obiekt ze sceny
   * \retval false jezeli usuwanie nie powiodlo sie 
   */
  bool UsunObiekt();
  
};
