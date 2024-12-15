#include "Marinero.h"

Marinero::Marinero(std::string nombre, int vida, int coordX, int coordY) : BarcoBase(nombre, vida, coordX, coordY)
{
	setPotFuego(35);
	setDinero(300);
}
