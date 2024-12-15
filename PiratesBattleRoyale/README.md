# Pirates Battle Royale

## Descripcion del proyecto

Se ha realizado un minijuego donde el usuario controlará un barco y deberá pelear contra otros buques para ser la 
ultima tripulación en el ancho mar.

Este proyecto se gestionará con inputs por la terminal y se jugará por turnos, es decir, el jugador realizará su accion y le seguirá los 
diferentes barcos controlados por la IA.
El juego acabará cuando el jugador sea el ultimo barco en pie o este pierda todos sus puntos de vida.

## Inicio de la partida

Una vez se comience la partida se necesitarán realizar unas configuraciones inicales para poder jugar. El juego te pedirá
se escribas una seria de inputs para personalizar la partida:
1. Dimensiones del mapa: se creará un mapa de NxN para poder posicionar los elementos de la partida.
2. Numero de islas: Se le pedirá al jugador que seleccione un numero de islas para generarlas en posiciones aleatoria en el mapa previamente delimitado.
3. Numero de jugadores: Se deberá seleccionar un numero de barcos que jugarán la partida.
Por cada jugador seleccionado se deberá proporcionar un nombre y una tripulación para el barco (cada tripulacion tendra unas caracteísticas diferentes).

## Jerarquía de clases

Se ha desarrollado una clase BarcoBase que contiene todos los atributos y métodos necesario para el control del barco durante el juego.
1. Atributos:

	* Nombre: Identificador del barco.
	* Vida maxima: Atributo no accesible para que los barcos no puedan recuperar mas vida de la maxima de su clase
	* Vida: Atributo para controlar la vida actual del barco
	* Potencia de fuego: Mide la capacidad de daño de los cañones del barco.
	* Dinero: Mide la cantidad de oro que posee el barco para comprar mejoras.
	* Posicion: Atributo que controla la posicion del barco en el mapa en coordenadas XY.

Se ha desarrollado 3 clases hijo que heredan de BarcoBase y modifican ciertos atributos de la clase padre:
1. Tipos de tripulación:

	* Piratas: Temibles, pero pobres, hombres que no conocen el miedo. Tienen una gran potencia de fuego a costa de su dañado barco (vida) y dinero.
	* Marineros: A diferencia de los piratas no tienen mucha cadencia de fuego pero lo suplen con un barco reforzado y mucho dinero.
	* Corsarios: Una tripulacion polivalente con buna potencia de fuego, un buen barco y algo de dinero.

## Desarrollo de la partida

### Inicio de ronda
Al principio de cada turno el jugador podrá ver el numero de barcos que siguen vivos, la vida actual de cada uno y los elementos que rodean su posicion:
1. "J": Caracter que representa el jugador.
1. "E": Caracter que representa a un enemigo.
1. "I": Caracter que representa a una isla.
1. "~": Caracter que representa agua.

Ademas el jugador pordrá ver las estidisticas actualies de su barco.

### Turno del jugador
En cada turno el jugador podrá elegir entre varias acciones a realizar:
1. Navegar: Te permitirá moverte por el mapa.
1. Consultar el mapa: Te permitira ver donde estan el resto de jugadores, tesoros, islas...
1. Reparar el barco: Te permitirá recuperar algo de salud de tu buque.
1. Accion: Esta opcion dependerá de los objetos que tengas en las casillas adyacentes:
	* Atacar a otro barco.
	* Ir a una isla para comprar mejoras para tu barco.
	* Buscar en el fondo marino: Encontraras dinero entre un rango de cantidades.

Una vez el jugador haya realizado su turno el resto de enemigos realizará su turno de forma secuencial.

### Algoritmo IA enemigo.

Se ha generado un pequeño algoritmo para los enemigos. Los enemigos interán realizar una serie de acciones:
* El orden será el siguiente:
	* Si esta al lado de otro barco -> Atacará a un barco adyacente.
	* Si esta por debajo de 50 de vida -> La tripulacion reparará el barco.
	* Si tiene menos de 100 de oro  y no esta cerca de una isla -> Buscará dinero en el fondo del mar.
	* Si esta al lado de una isla y tiene dinero -> Mejorará su potencia de fuego.
	* Si no tiene otra opcion -> Navegará por el mar.