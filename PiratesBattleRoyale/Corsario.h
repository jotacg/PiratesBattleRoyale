#pragma once
#include "BarcoBase.h"
#include <string>

class Corsario : public BarcoBase
{
public:
	Corsario(std::string nombre, int vida, int coordX = 0, int coordY = 0);
};

