# Pirates Battle Royale

## Descripcion del proyecto

Se ha realizado un minijuego donde el usuario controlara un barco y debera pelear contra otros buques para ser la 
ultima tripulacion en el ancho mar.

Este proyecto se gestionara con inputs por la terminal y se jugara por turnos, es decir, el jugador realizara su accion y le seguira los 
diferentes barcos controlados por la IA.
El juego acabara cuando el jugador sea el ultimo barco en pie o este pierda todos sus puntos de vida.

## Inicio de la partida

Una vez se comience la partida se necesitaran realizar unas configuraciones inicales para poder jugar. El juego te pedira
se escribas una seria de inputs para personalizar la partida:
1. Dimensiones del mapa: se creara un mapa de NxN para poder posicionar los elementos de la partida.
2. Numero de islas: Se le pedira al jugador que seleccione un numero de islas para generarlas en posiciones aleatoria en el mapa previamente delimitado.
3. Numero de jugadores: Se debera seleccionar un numero de barcos que jugaran la partida.
Por cada jugador seleccionado se debera proporcionar un nombre y una tripulacion para el barco (cada tripulacion tendra unas caracteisticas diferentes).

## Jerarquia de clases

Se ha desarrollado una clase BarcoBase que contiene todos los atributos y metodos necesario para el control del barco durante el juego.
1. Atributos:

	* Nombre: Identificador del barco.
	* Vida maxima: Atributo no accesible para que los barcos no puedan recuperar mas vida de la maxima de su clase
	* Vida: Atributo para controlar la vida actual del barco
	* Potencia de fuego: Mide la capacidad de daño de los cañones del barco.
	* Dinero: Mide la cantidad de oro que posee el barco para comprar mejoras.
	* Posicion: Atributo que controla la posicion del barco en el mapa en coordenadas XY.

Se ha desarrollado 3 clases hijo que heredan de BarcoBase y modifican ciertos atributos de la clase padre:
1. Tipos de tripulacion:

	* Piratas: Temibles, pero pobres, hombres que no conocen el miedo. Tienen una gran potencia de fuego a costa de su dañado barco (vida) y dinero.
	* Marineros: A diferencia de los piratas no tienen mucha cadencia de fuego pero lo suplen con un barco reforzado y mucho dinero.
	* Corsarios: Una tripulacion polivalente con buna potencia de fuego, un buen barco y algo de dinero.

## Desarrollo de la partida

### Inicio de ronda
Al principio de cada turno el jugador podra ver el numero de barcos que siguen vivos, la vida actual de cada uno y los elementos que rodean su posicion:
1. "J": Caracter que representa el jugador.
1. "E": Caracter que representa a un enemigo.
1. "I": Caracter que representa a una isla.
1. "~": Caracter que representa agua.

Ademas el jugador pordra ver las estidisticas actualies de su barco.

### Turno del jugador
En cada turno el jugador podra elegir entre varias acciones a realizar:
1. Navegar: Te permitira moverte por el mapa.
1. Consultar el mapa: Te permitira ver donde estan el resto de jugadores, tesoros, islas...
1. Reparar el barco: Te permitira recuperar algo de salud de tu buque.
1. Accion: Esta opcion dependera de los objetos que tengas en las casillas adyacentes:
	* Atacar a otro barco.
	* Ir a una isla para comprar mejoras para tu barco.
	* Buscar en el fondo marino: Encontraras dinero entre un rango de cantidades.

Una vez el jugador haya realizado su turno el resto de enemigos realizara su turno de forma secuencial.

### Algoritmo IA enemigo.

Se ha generado un pequeño algoritmo para los enemigos. Los enemigos interan realizar una serie de acciones:
* El orden sera el siguiente:
	* Si esta al lado de otro barco -> Atacara a un barco adyacente.
	* Si esta por debajo de 50 de vida -> La tripulacion reparara el barco.
	* Si tiene menos de 100 de oro  y no esta cerca de una isla -> Buscara dinero en el fondo del mar.
	* Si esta al lado de una isla y tiene dinero -> Mejorara su potencia de fuego.
	* Si no tiene otra opcion -> Navegara por el mar.