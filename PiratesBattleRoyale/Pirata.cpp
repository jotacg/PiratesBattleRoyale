#include "Pirata.h"

Pirata::Pirata(std::string nombre, int vida, int coordX, int coordY) : BarcoBase(nombre, vida, coordX, coordY)
{
	setPotFuego(70);
	setDinero(100);
}