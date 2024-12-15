#include "Corsario.h"

Corsario::Corsario(std::string nombre, int vida, int coordX, int coordY) : BarcoBase(nombre, vida, coordX, coordY)
{
	setPotFuego(50);
	setDinero(200);
}
