#pragma once
#include <iostream>
#include <vector>
#include <random>

class BarcoBase
{
private:
	std::string nombre;
	int vidaMaxima;
	int vida;
	int potenciaFuego;
	int dinero;
	int posicion[2];

public:
	static int contador;
	BarcoBase(std::string nombre, int vida, int coordX = 0, int coordY = 0);
	~BarcoBase();
	std::string getNombre();
	int getVida();
	void setVida(int nuevaVida);
	int getPotFuego();
	void setPotFuego(int potFuegoMejorada);
	int getDinero();
	void setDinero(int dinero);
	int* getPosicion();
	void setPosicion(int x, int y);

	void mostrarCasillasAdyacentes(std::string ** mapa, int tamanio);
	void navegar(std::string** mapa, int tamanio, bool jugador);
	void repararBarco();
	void buscarDinero();
	void comprarMejora(std::string** mapa, int tamanio);
	void perderVida(int damage);

	int* mostrarBarcosADisparar(std::string** mapa, int tamanio);
	int* disparoIA(std::string** mapa, int tamanio);
	bool islaCerca(std::string** mapa, int tamanio);
};

