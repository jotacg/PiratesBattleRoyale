#pragma once
#include "BarcoBase.h"
#include <string>

class Pirata : public BarcoBase
{
public:
	Pirata(std::string nombre, int vida, int coordX = 0, int coordY = 0);
};

