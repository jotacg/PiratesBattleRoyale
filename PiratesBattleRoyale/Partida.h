#pragma once
#include <iostream>
#include <string>
#include <random>
#include "BarcoBase.h"

class Partida
{
private:
	int filas;
	int columnas;
	std::string** mapa;

	int capacidadJugadores;
	BarcoBase** jugadores;
	void redimensionar();

public:
	static int numJugadores;
	Partida(int tamanioInicial, int jugadoresIniciales = 2);
	void rellenarAgua(char agua);
	void agregarJugador(BarcoBase *jugador);
	void posicionarElementos(BarcoBase** jugadores, int numIslas);
	void mostarMapa();
	int getFilas();
	std::string** getMapa();
	BarcoBase** getJugadores();
	BarcoBase* getBarco(int* posBarco);
	void mostrarVidaJugadores();
	void elegirTurno(BarcoBase* jugador);
	void elegirAccion(BarcoBase* jugador);
	void eliminarBarco();
	void turnoIA(BarcoBase* jugador);
	bool jugadorVivo(std::string);

};

