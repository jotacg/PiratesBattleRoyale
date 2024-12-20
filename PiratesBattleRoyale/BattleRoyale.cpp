#include <iostream>
#include "BarcoBase.h"
#include "Partida.h"
#include "Pirata.h"
#include "Marinero.h"
#include "Corsario.h"


int main() 
{
	int tamanio = 5; // Tamaño del mapa por defecto 5x5
	std::cout <<"Elegir el tamaño del mapa (Se recomienda un tamaño entre 5 y 10):" << std::endl;
	std::cin >> tamanio;
	Partida partida = Partida(tamanio);

	partida.rellenarAgua('~');

	int numIslas = 5; // Numero de islas, por defecto 5
	std::cout << "Elegir el numero de islas (Las islas sirven para mejorar el equipo):" << std::endl;
	std::cin >> numIslas;
	
	int numPlayer = 1;	// Numero de jugadores que van a jugar
	std::cout << "Elege el numero de jugadores:" << std::endl;
	std::cin >> numPlayer;

	for (int i = 0; i < numPlayer; i++)	// Se realiza un blucle para ir agregando los jugadores a la partida
	{
		std::string nombre = "";
		std::cout << "Elegir el nombre del barco "<< i+1 <<":" << std::endl;
		std::cin >> nombre;
		int tripulacion = 1;
		std::cout << "Elege tu tripulacion: 1.Pirata / 2.Marinero / 3.Corsario" << std::endl;
		std::cin >> tripulacion;
		switch (tripulacion)
		{
		case 1:
			partida.agregarJugador(new Pirata(nombre, 80));
			break;
		case 2:
			partida.agregarJugador(new Marinero(nombre, 150));
			break;
		case 3:
			partida.agregarJugador(new Corsario(nombre, 120));
			break;
		default:
			partida.agregarJugador(new BarcoBase(nombre, 100));
			break;
		}
	}
	
	partida.posicionarElementos(partida.getJugadores(), numIslas);	// Se posicionan aleatoriamente los jugadores y las islas en el mapa
	
	BarcoBase** listaJugadores = partida.getJugadores();
	BarcoBase* usuario = listaJugadores[0];
	std::string nombreJugador = listaJugadores[0]->getNombre();
	std::cout << "######### INICIO DE LA PARTIDA ######### " << std::endl;
	int numRonda = 0;
	std::string continuar = "s";
	while (continuar == "s")
	{
		std::cout << "######### RONDA "<< numRonda<<" ######### " << std::endl;
		partida.mostrarNumJugadores();
		partida.mostrarVidaJugadores();

		std::cout << "######### CASILLAS ADYACENTES ######### " << std::endl;
		usuario->mostrarCasillasAdyacentes(partida.getMapa(), partida.getFilas());
		std::cout << "####################################### " << std::endl;
		partida.elegirTurno(usuario);

		for (int i = 1; i < partida.numJugadores; i++)
		{
			partida.turnoIA(listaJugadores[i]);
		}
		numRonda++;

		if (!partida.jugadorVivo(nombreJugador))
		{
			std::cout << "Has perdido!" << std::endl;
			break;
		}

		if (partida.numJugadores <= 1)
		{
			std::cout << "Has ganado!" << std::endl;
			break;
		}
		std::cout << "Continuar ? [s / n]" << std::endl;
		std::cin >> continuar;
	}
	
}

