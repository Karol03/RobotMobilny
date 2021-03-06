#include "Fabryka.hh"



FabrykaObjektow* FabrykaObjektow::_Fabryka = new FabrykaObjektow();

std::shared_ptr<ObiektGraficzny> FabrykaObjektow::DodajObiekt(							      RodzajObiektu JakiObj,
				     Wektor2D Srodek										      )
{
  switch(JakiObj){
  case ROBOT:
    return std::make_shared<Robot>(Srodek, (std::rand()%360) );
  case PRZESZKODA:
    return std::make_shared<Prostokat>(Srodek, 8, 8);
  case SCIEZKA:
    return std::make_shared<Sciezka>(Srodek);
  }
  return std::make_shared<ObiektGraficzny>();
}

