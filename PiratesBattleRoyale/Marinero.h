#pragma once
#include "BarcoBase.h"
#include <string>

class Marinero : public BarcoBase
{
public:
	Marinero(std::string nombre, int vida, int coordX = 0, int coordY = 0);
};

