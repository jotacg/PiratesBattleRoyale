#include "Partida.h"

int Partida::numJugadores = 0;

// Constructor de la partida donde se agregaran los jugaodres, el mapa y las islas
Partida::Partida(int tamanioInicial, int jugadoresIniciales)
{
    this->filas = tamanioInicial;
    this->columnas = tamanioInicial;
	this->mapa = new std::string* [tamanioInicial];

    for (int i = 0; i < tamanioInicial; i++)    // Se crea el mapa con el tamanio pasado por parametro
    {
        mapa[i] = new std::string[tamanioInicial];
    }

    this->capacidadJugadores = jugadoresIniciales;
    this->jugadores = new BarcoBase * [jugadoresIniciales];
}

// Metodo para rellenar con un caracter pasado por parametro el grid del mapa
void Partida::rellenarAgua(char agua)
{
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            mapa[i][j] = agua;
        }
    }
}

// Metodo para agregar un jugador a la lista de jugadores, en el caso de que no haya espacio se debe redimensionar la lista
void Partida::agregarJugador(BarcoBase* jugador)
{
    if (numJugadores == capacidadJugadores)
    {
        redimensionar();
    }

    jugadores[numJugadores] = jugador;

    numJugadores++;     // Se suma 1 al numero de jugadores
}

void Partida::posicionarElementos(BarcoBase **jugadores, int numIslas)
{
    // Se sacan todas las posiciones del grid
    std::vector<std::pair<int, int>> posiciones;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            posiciones.emplace_back(i, j); // Guardar posición (fila, columna)
        }
    }
    
    // Se barajan las posiciones para agregar los barcos y las islas de forma aleatoria
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(posiciones.begin(), posiciones.end(), gen);

    int k = 0;
    // Posicionar a los jugadores
    for (k; k < numJugadores; k++) {
        int fila = posiciones[k].first;
        int columna = posiciones[k].second;
        jugadores[k]->setPosicion(fila, columna); // La fila sera la coord Y y la columna la X
        if (k == 0) // Se marca al primero con una 'J' de jugador y el resto 'E' de enemigo
        {
            mapa[fila][columna] = 'J';
        }
        else
        {
            mapa[fila][columna] = 'E'; 
        }
    }

    // Posicionar islas
    int islas = k + numIslas;   // se mantiene el valor de k para no pisar a los barcos ya posicionados
    for (k; k < islas; k++)
    {
        int fila = posiciones[k].first;
        int columna = posiciones[k].second;
        mapa[fila][columna] = 'I';
    }
}

// Metodo para redimensionar la capacidad de la lista en caso de que no entre el jugador a agregar
void Partida::redimensionar()
{
    capacidadJugadores = capacidadJugadores * 2;	// Se duplica la capacidad de la lista

    BarcoBase** nuevosJugadores = new BarcoBase * [capacidadJugadores];	// Se crea la nueva lista con la capacidad duplicada

    for (int i = 0; i < numJugadores; i++)
    {
        nuevosJugadores[i] = jugadores[i];	// Se cargan en la nueva lista los elementos de la antigua
    }

    delete[] jugadores;

    jugadores = nuevosJugadores;
}

// Metodo para mostrar el todo el mapa generado
void Partida::mostarMapa()
{
    for (int i = 0; i < filas; i++) 
    {
        for (int j = 0; j < columnas; j++) 
        {
            std::cout << " " << mapa[i][j];
        }
        std::cout << std::endl;
    }
}

int Partida::getFilas()
{
    return filas;
}

std::string** Partida::getMapa()
{
    return mapa;
}

BarcoBase** Partida::getJugadores()
{
    return jugadores;
}

// Metodo para devolver el objeto Barco dada una posicion
BarcoBase* Partida::getBarco(int * posBarco)
{
    BarcoBase** jugadores = getJugadores();
    
    for (int i = 0; i < numJugadores; i++)
    {
        if (jugadores[i]->getPosicion()[0] == posBarco[0] &&
            jugadores[i]->getPosicion()[1] == posBarco[1])
        {
            return jugadores[i];
        }
    }
    return nullptr;
}

// Metodo para mostrar la vida de los jugadores en cada ronda (iterando por la lista de jugadores)
void Partida::mostrarVidaJugadores()
{
    BarcoBase** jugadores = getJugadores();

    for (int i = 0; i < numJugadores; i++)
    {
        std::cout << jugadores[i]->getNombre() << " vida restante: " << jugadores[i]->getVida() << std::endl;
    }
}

// Metodo que muestra las caracteristicas actuales del tu barco y que permite realizar una accion en el turno
void Partida::elegirTurno(BarcoBase * jugador)
{
    std::cout << "##### DATOS DEL BARCO #####" << std::endl;
    std::cout << "- Vida: " << jugador->getVida() << std::endl;
    std::cout << "- Pot. Ataque: " << jugador->getPotFuego() << std::endl;
    std::cout << "- Dinero: " << jugador->getDinero() << std::endl;
    std::cout << "- Posicion:: x:" << jugador->getPosicion()[0] << ", y:" << jugador->getPosicion()[1] << std::endl;
    std::cout << "###########################" << std::endl;

    std::cout << "Que deseas hacer?" << std::endl;
    std::cout << "1. Navegar" << std::endl;
    std::cout << "2. Consultar el mapa" << std::endl;
    std::cout << "3. Reparar el barco" << std::endl;
    std::cout << "4. Accion" << std::endl;
    int accion;
    std::cin  >> accion;
    switch (accion)
    {
    case 1:
        jugador->navegar(mapa, filas, true);
        break;
    case 2:
        mostarMapa();
        break;
    case 3:
        jugador->repararBarco();
        break;
    case 4:
        elegirAccion(jugador);
    default:
        break;
    }
}

// Metodo para buscar dinero, mejorar el barco (en caso de tener dinero y estar cerca de una isla) y atacar
void Partida::elegirAccion(BarcoBase* jugador)
{
    std::cout << "Que deseas hacer?" << std::endl;
    std::cout << "1. Buscar dinero" << std::endl;
    std::cout << "2. Mejorar barco" << std::endl;
    std::cout << "3. Atacar" << std::endl;
    int accion;
    int* posEnemigo;
    std::cin >> accion;
    BarcoBase* disparado = nullptr; // Se guarda una variable *BarcoBase para comprobar si ha dado a un barco o no
    switch (accion)
    {
    case 1:
        jugador->buscarDinero();
        break;
    case 2:
        jugador->comprarMejora(mapa, filas);
        break;
    case 3:         // En caso de que se fuese a disparar
        posEnemigo = jugador->mostrarBarcosADisparar(getMapa(), getFilas()); // Se muestran las posiciones de los barcos adyacentes y se devuelve una pos a disparar
        disparado = getBarco(posEnemigo);   // En caso de que haya un barco en esa pos, se le restara la vida
        delete[] posEnemigo;
        break;
    default:
        break;
    }
    if (disparado != nullptr)
    {
        disparado->perderVida(jugador->getPotFuego());
        eliminarBarco();    // Se comprueba si se tienen que eliminar barcos
    }
    
}

// Metodo para comprobar si hay barcos a eliminar
void Partida::eliminarBarco()
{
    int indice = -1;		// Varable para saber el indice del Barco encontrado
    if (numJugadores > 0)
    {
        for (int i = 0; i < numJugadores; i++)
        {
            if (jugadores[i]->getVida() <= 0)
            {
                mapa[jugadores[i]->getPosicion()[1]][jugadores[i]->getPosicion()[0]] = "~";
                delete jugadores[i];
                indice = i;
            }
        }
        if (indice >= 0)	// En caso de que se haya encontrado se debe desplazar los elemntos siguientes
        {
            for (int j = indice; j < numJugadores - 1; j++)
            {
                jugadores[j] = jugadores[j + 1];
            }
            numJugadores--;
        }
    }
}

// Metodo para controlar el turno de los enemigos
/*
    El orden de acciones para la ia será el siguiente:
    1.Si esta al lado de otro barco -> atacar a un barco adyacente
    2.Si esta por debajo de 50 de vida -> curarse
    3.Si tiene menos de 100 de oro  y no esta cerca de una isla -> buscar en el fondo del mar
    4.Si esta al lado de una isla y tiene dinero comprar una mejora para el barco
    5.Si no tiene otra opcion -> navegar por el mar
*/
void Partida::turnoIA(BarcoBase* jugador)
{
    int* posibleEnemigo = jugador->disparoIA(mapa, filas);
    if (posibleEnemigo[0] != -1 && posibleEnemigo[1] != -1)
    {
        getBarco(posibleEnemigo)->perderVida(jugador->getPotFuego());
        eliminarBarco();    // Se comprueba si se tienen que eliminar barcos
    }
    else if (jugador->getVida() < 50)
    {
        std::cout << jugador->getNombre() << " ha reparado el barco" << std::endl;
        jugador->repararBarco();
    }
    else if (jugador->getDinero() < 500 and !jugador->islaCerca(mapa, filas))
    {
        std::cout << jugador->getNombre() << " ha buscado dinero" << std::endl;
        jugador->buscarDinero();
    }
    else if (jugador->islaCerca(mapa, filas) && jugador->getDinero() >= 500)
    {
        jugador->comprarMejora(mapa, filas);
    }
    else
    {
        jugador->navegar(mapa, filas, false);
    }
    delete[] posibleEnemigo;
}

// Metodo para comprobar si el player sigue vivo, en caso de que no se acabará la partida
bool Partida::jugadorVivo(std::string nombreJugador)
{
    BarcoBase** jugadores = getJugadores();

    for (int i = 0; i < numJugadores; i++)
    {
        if (jugadores[i]->getNombre() == nombreJugador)
        {
            return true;
        }
    }
    return false;
}

