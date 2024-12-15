#include "BarcoBase.h"

// Variable para llevar el conteo de los barcos
int BarcoBase::contador = 0;

BarcoBase::BarcoBase(std::string nombre, int vida, int coordX, int coordY)
{
	this->nombre = nombre;
	this->vidaMaxima = vida;
	this->vida = vida;
	this->potenciaFuego = 50;
	this->dinero = 250;
	this->posicion[0] = coordX;
	this->posicion[1] = coordY;
	contador++;
}

BarcoBase::~BarcoBase()
{
	contador--;
}
std::string BarcoBase::getNombre()
{
	return this->nombre;
}

int BarcoBase::getVida()
{
	return vida;
}

void BarcoBase::setVida(int nuevaVida)
{
	vida = nuevaVida;
}

int BarcoBase::getPotFuego()
{
	return potenciaFuego;
}

void BarcoBase::setPotFuego(int potFuegoMejorada)
{
	potenciaFuego = potFuegoMejorada;
}

int BarcoBase::getDinero()
{
	return dinero;
}

void BarcoBase::setDinero(int nuevaCantidad)
{
	dinero = nuevaCantidad;
}

int* BarcoBase::getPosicion()
{
	return posicion;
}

void BarcoBase::setPosicion(int y, int x)
{
	posicion[0] = x;
	posicion[1] = y;
}

void BarcoBase::mostrarCasillasAdyacentes(std::string** mapa, int tamanio) 
{
	const int x = posicion[0];
	const int y = posicion[1];
	for (int i = -1; i < 2; i++)	// Se recorren las 8 posiciones alrededor del barco + la del barco (de arriba a abajo, izq der)
	{
		if (y + i >= 0 && y + i < tamanio)
		{
			std::string linea = "";
			if (x - 1 >= 0)
			{
				linea += " " + mapa[y + i][x - 1];	// En el mapa las coordenadas van [Y][X]
			}
			linea += " " + mapa[y + i][x];	// En el mapa las coordenadas van [Y][X]
			if (x + 1 < tamanio)
			{
				linea += " " + mapa[y + i][x + 1];	// En el mapa las coordenadas van [Y][X]
			}
			std::cout << linea<<std::endl;
		}
	}
}

// Metodo para navegar por el mapa (se ha añadido un parametro bool para comprobar si se mueve el jugador (por lo que se le pedirá
// una direccion), o un enemigo (que se moverá aleatoriamente)
void BarcoBase::navegar(std::string** mapa, int tamanio, bool jugador)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int x = 0;
	int y = 0;
	int dir;
	if (jugador)
	{
		std::cout << "Hacia donde quieres navegar\n";
		std::cout << "Norte: 1\n";
		std::cout << "Sur: 2\n";
		std::cout << "Este: 3\n";
		std::cout << "Oeste: 4" << std::endl;
		
		std::cin >> dir;
	}
	else
	{
		std::uniform_int_distribution<> distrib(1, 4);
		dir = distrib(gen);
	}
	// Los jugadores no se pueden mover en diagonal
	switch (dir)
	{
	case 1:
		y--; break;
	case 2:
		y++; break;
	case 3:
		x++; break;
	case 4:
		x--; break;
	default:
		break;
	}
	
	
	int nuevaX = posicion[0] + x;
	int nuevaY = posicion[1] + y;
	// Se comprueba si se puede mover a esa casilla (hay agua)
	if (nuevaX >= 0 && nuevaX < tamanio && nuevaY >= 0 && nuevaY < tamanio
		&& mapa[nuevaY][nuevaX] == "~")
	{
		// Se actualiza la nueva casilla con el caracter del barco (J ó E)
		// y se actualiza la antigua con la de agua
		std::string antiguaPos = mapa[posicion[1]][posicion[0]];
		mapa[nuevaY][nuevaX] = antiguaPos;
		mapa[posicion[1]][posicion[0]] = '~';
		setPosicion(nuevaY, nuevaX);
		std::cout << nombre << " se ha movido" << std::endl;
	}

}
// Metodo para reparar el barco (en caso de que supere la vida maxima se pondrá la maxima)
void BarcoBase::repararBarco()
{
	if (vida + 20 > vidaMaxima)
	{
		setVida(vidaMaxima);
	}
	else
	{
		setVida(vida + 20);
	}
}

// Metodo para buscar dinero en el fondo del mar
void BarcoBase::buscarDinero()
{
	std::random_device rd; 
	std::mt19937 gen(rd()); // Generador de números aleatorios

	// Definir los límites
	int min_val = 50;
	int max_val = 200;

	// Se crea una distribución uniforme en el rango [min_val, max_val]
	std::uniform_int_distribution<> distrib(min_val, max_val);

	int dineroEncontrado = distrib(gen);
	std::cout << nombre << " ha encontrado " << dineroEncontrado << "!" << std::endl;
	// Generar un número aleatorio
	dinero += dineroEncontrado;
}

// Metodo para comprar una mejora al barco (requisitos: tener 500 de oro y estar al lado de una isla)
void BarcoBase::comprarMejora(std::string** mapa, int tamanio)
{
	const int x = posicion[0];
	const int y = posicion[1];

	if (islaCerca(mapa, tamanio))
	{
		if(dinero >= 500)	// En caso de que se tenga dinero se podra mejorar la potencia de fuego
		{
			dinero -= 500;
			potenciaFuego += 10;
			std::cout << nombre << " ha mejorado su potencia de fuego" << std::endl;
		}
		else
		{
			std::cout << "No tienes suficiente dinero" << std::endl;
		}
	}
	else
	{
		std::cout << "No hay una isla cerca" << std::endl;
	}
}

// Metodo para actualizar la vida del barco disparado
void BarcoBase::perderVida(int damage)
{
	this->setVida(vida - damage);
	std::cout << this->nombre << " ha perdido " << damage << " puntos de vida: vida restante " << this->vida << std::endl;
}

// Metodo que mustra por pantalla las posiciones de klos barcos adyacentes (incluido el jugador) y que devuelve un vector 
// con la posicion a la que se quiere disparar
int * BarcoBase::mostrarBarcosADisparar(std::string** mapa, int tamanio)
{
	const int x = posicion[0];
	const int y = posicion[1];
	// Se recorre las casillas adyacentes y se muestra por pantalla las posicion de los barcos adyacentes
	for (int i = -1; i < 2; i++)
	{
		if (y + i >= 0 && y + i < tamanio)
		{
			if (x - 1 >= 0 && (mapa[y + i][x - 1] == "E" || mapa[y + i][x - 1] == "J"))
			{
				std::cout << "Barco en la pos: " << x-1 << ", " << y + i << std::endl;
			}
			if (mapa[y + i][x] == "E" || mapa[y + i][x] == "J")
			{
				std::cout << "Barco en la pos: " << x << ", " << y + i << std::endl;
			}
			if (x + 1 < tamanio && (mapa[y + i][x + 1] == "E" || mapa[y + i][x + 1] == "J"))
			{
				std::cout << "Barco en la pos: " << x + 1 << ", " << y + i  << std::endl;
			}
		}
	}
	int coordX = -1;
	int coordY = -1;
	// Se pide una posicion a la que disparar
	std::cout << "A que posicion quieres disparar? (Puedes probar suerte y disparar al mar pero no te dispares a ti mismo)" << std::endl;
	std::cout << "Posicion X:" << std::endl;
	std::cin >> coordX;
	std::cout << "Posicion Y:" << std::endl;
	std::cin >> coordY;

	int* posADisparar = new int[2];
	posADisparar[0] = coordX;
	posADisparar[1] = coordY;
	return posADisparar;
}

// Metodo que que los barcos enemigos disparen (devuelven un vector con la posicion que han disparado)
// Buscará en sus casillas adyacentes un barco (J ó E) y disparará al ultimo encontrado (No se podrá disparar a si mismo)
int* BarcoBase::disparoIA(std::string** mapa, int tamanio)
{
	const int x = posicion[0];
	const int y = posicion[1];
	int enemigoX = -1;
	int enemigoY = -1;
	for (int i = -1; i < 2; i++)
	{
		if (y + i >= 0 && y + i < tamanio)
		{
			if (x - 1 >= 0 && (mapa[y + i][x - 1] == "E" || mapa[y + i][x - 1] == "J"))
			{
				enemigoX = x - 1;
				enemigoY = y + i;
			}
			if ((mapa[y + i][x] == "E" || mapa[y + i][x] == "J") && i != 0 )
			{
				enemigoX = x;
				enemigoY = y + i;
			}
			if (x + 1 < tamanio && (mapa[y + i][x + 1] == "E" || mapa[y + i][x + 1] == "J"))
			{
				enemigoX = x + 1;
				enemigoY = y + i;
			}
		}
	}
	int* posADisparar = new int[2];
	posADisparar[0] = enemigoX;
	posADisparar[1] = enemigoY;
	return posADisparar;
}

// Metodo para comprobar si hay una isla cerca del jugador (en las casillas adyacentes)
bool BarcoBase::islaCerca(std::string** mapa, int tamanio)
{
	const int x = posicion[0];
	const int y = posicion[1];
	for (int i = -1; i < 2; i++)
	{
		if (y + i >= 0 && y + i < tamanio)
		{
			if (x - 1 >= 0 && mapa[y + i][x - 1] == "I")
			{
				return true;
			}
			if (mapa[y + i][x] == "I")
			{
				return true;
			}
			if (x + 1 < tamanio && mapa[y + i][x + 1] == "I")
			{
				return true;
			}
		}
	}
	return false;
}
