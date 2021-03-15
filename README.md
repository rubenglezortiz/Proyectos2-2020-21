# Proyectos2-2020-21
# **P A I N T L E S S**


![LOGO](./webAssets/images/logo.png)

Documento de diseño de juego

---------------------------------

**Grupo 3 - NoName’s Studios**

*Manuel Adeliño Consuegra | Jonathan Sebastián Andrade Gordillo | Rubén González Ortiz | Alberto Gómez Castaño | Simeon Konstantinov Petrov | Javier Meitín Moreno | Mario Miguel Cuartero | Adrían Migueles D’Ambrosio | Alejandro Ortega Ruiz | Nicolás Rosa Caballero*

| **Géneros:** Turn-Based-Strategy | **Modos:** Multijugador online y local |
| --- | --- |
| **Público objetivo:** Dirigido a personas de entre 13 a 40 años | **Plataformas:** Windows x64 |

**Descripción:**
PaintLess es un juego multijugador de estrategia por turnos en el cual los jugadores disponen de un amplio abanico de personajes con distintas habilidades de los cuales deben seleccionar seis. El juego se desarrolla en un tablero 9x10 donde los jugadores deben mover a sus diferentes personajes para cubrir la mayor área de juego posible. Esto es debido a que según los personajes se mueven, colorean las casillas por las que se han desplazado. El ganador será aquel que pasados 10 turnos, tenga cubierta la mayor de las partes coloreadas. En dicho momento, se terminará la partida.

## **Páginas de interés**
### [Página web](https://rubenglezortiz.github.io/Proyectos2-2020-21/)
### [Pivotal Tracker](https://www.pivotaltracker.com/n/projects/2489055)
### [Repositorio](https://github.com/rubenglezortiz/Proyectos2-2020-21)

# Menú
foto del menú

El esquema del menú principal es simple, con una disposición vertical y centrada de diferentes botones, cada uno con su respectiva función:
- Botón para  entrar al modo multijugador: Permite o bien crear un lobby para invitar a otras personas a través de un código o bien unirse a otro jugador introduciendo uno.
- Local: Permite elegir al jugador el número de jugadores, y jugar con otros jugadores usando el mismo equipo.
- Opciones: Permite modificar el volumen.
- Salir: Cierra el juego.
 
 foto interfaz
 
 Antes de comenzar la partida, cada jugador debe elegir 6 personajes distintos de entre todos los distintos personajes para conformar su mazo.
 
 foto interfaz
 
 Durante la partida, el jugador puede entrar en un Menú de Pausa con una disposición de botones similar a la del menú principal, con diferentes opciones:
- Reanudar: Permite volver a la pantalla de juego, pudiendo proseguir con la partida.
- Rendirse: Permite al jugador abandonar la partida en caso de que no quiera seguir jugando, dándole la victoria al otro jugador/ dejando que el resto de jugadores prosigan con la partida.
- Opciones: Permite modificar el volumen.
- Salir. Permite abandonar el juego.

# Interfaz

Durante la partida, la interfaz muestra diferentes datos, con una disposición similar a la siguiente imagen:

foto interfaz

 En la parte superior de la pantalla, se indican los turnos restantes hasta que termine la partida.
 A ambos extremos del tablero se refleja qué porcentaje del mapa tiene coloreado cada jugador. Esto es indicado mediante una barrita vertical que ayuda a ver visualmente la diferencia.
 En la zona inferior, cada jugador puede ver los personajes que conforman su baraja, así como sus características, véase vida, cooldown, coste etc. También se puede ver el maná total del que dispone en el turno actual.

# Jugabilidad

## Mecánicas
 Durante cada turno de la partida el jugador puede crear tropas en el tablero usando maná y moverse/atacar utilizando 4 puntos de acción, los cuales se regenerarán en cada turno.
Cada personaje dispone de una habilidad específica con la cual puede eliminar a los personajes enemigos y ganar terreno en el mapa. Algunas de estas habilidades tienen un cooldown que limita el uso de las mismas en turnos.
## Movimiento
El jugador puede mover cada personaje dentro del tablero gastando puntos de acción (1 movimiento = 1 punto). Todos los personajes se mueven de una casilla en una casilla (a no ser que tengan una habilidad que les permita desplazarse varias casillas en una sola acción), incluso intercalando movimiento con ataque. Los personajes se pueden mover en 4 direcciones (vertical y horizontal), pero no en diagonal (excepto los personajes con habilidades especiales que se lo permitan). Los personajes no pueden atravesarse los unos a los otros ni a muros u obstáculos.
## Ataque
Cada unidad individual tiene un ataque diferente (definido en la tabla en la página siguiente). Para atacar, el jugador debe gastar puntos de acción (1 ataque = 1 punto). Dependiendo del personaje, el ataque causará más o menos daño y tendrá un rango distinto. Cada personaje solo podrá atacar una vez por turno.
## Maná
El jugador dispone puntos de maná que le permite sacar personajes desde el mazo al terreno de juego. El coste de cada personaje viene indicado arriba a la derecha de su ficha. 
El máximo de maná es 10 y cada turno se regenera 3 puntos. 
foto
## Personajes
Para el transcurso de la batalla, el jugador saca personajes arrastrándolos al terreno de juego gastando maná. El jugador podrá sacarlos (o en su zona de spawn + 2 filas pintadas / o en su zona pintada (dentro de su 50% de campo))
cada personaje ataca en 4 direcciones.

| SPRITE | MANÁ | CD | VIDA | DAÑO | PASIVA |
| --- | --- | --- | --- | --- | --- |
| PÍCARA | 2 | 3 | 2 | 2 | 25% para hacer x2 daño |
| ESQUELETO | 1 | 1 | 1 | 1 |  |
| VIKINGO | 2 | 2 | 1 | 1 | Disparo a larga distancia |
| KIRIN | 3 | 2 | 2 | 1 | Salta por encima de un obstáculo |
| DRUIDA | 3 | 3 | 2 | 1 | Saca enredaderas que dura 3 turnos|
| CAZADOR | 2 | 2 | 1 | 1 | Alcance aumentado |
| TANQUE | 4 | 2 | 3 | 0 | Regenera 1 de vida cada turno |
| GOLEM | 4 | 3 | 4 | 1 | No se puede mover |
| MONAGUILLO | 3 | 2 | 1 | 1 | +1 HP a los aliados de 3x3 |
| ARQUITECTA| 3 | 3 | 2 | 1 | Puede crear muros de 1 HP |
| BOMBA | 3 | 3 | 3 | 0 | Hace 1 de daño en 3x3 al morir o llegar a casillas enemigas |
| ALQUIMISTA | 3 | 3 | 2 | 0 | Su ataque stunea a los enemigos un turno y se mueve 2 casillas |
| LOBO | 3 | 2 | 2 | 0 | Echa hacia atrás a los enemigos 1 casilla. Si el empujado choca con un personaje, inflige 1 de daño |

## Tablero
foto interfaz
El tablero del juego será de tamaño y forma variable, y tendrá espacio para mantener un juego entre, como mínimo, dos jugadores.

En los extremos del tablero estarán los spawns(ocupando una fila completa) de cada jugador, casillas marcadas con un color neutral. En dichas casillas de spawn, los personajes no podrán ser heridos ni tampoco podrán atacar y defenderse, sólo moverse.

El resto de casillas del tablero comenzarán sin color, y a medida que los personajes de cada jugador avancen las convertirán del color propio del jugador.
 
En el tablero también aparecerán obstáculos, los cuales no podrán ser atravesados por los personajes del tablero (a no ser que tengan una habilidad que lo permita, i.e.: un personaje con la habilidad de saltar por encima de un obstáculo). 
 
Como el objetivo del juego es tener el mayor número de casillas de tu color, en pantalla aparecerá el porcentaje de terreno que cada jugador tiene.

# Dinámicas
## Objetivo del juego
El jugador deberá de tener la mayor parte del tablero de su color al finalizar todos los turnos.

# Estética

## Ambientación y gráficos
El arte del juego será Pixel 16-bit, tanto los jugadores como los mapas y los menús. Tendrá influencias fantásticas y medievales, pues el juego está ubicado en un espacio-tiempo similar al de la Edad Media, con ápices de fantasía. Los colores predominantes serán tonalidades vibrantes de verde, rojo, morado y amarillo. 

La resolución será de pantalla completa.

## Experiencia de juego

El jugador tomará el papel de un candidato a Adamantín, y combatirá con otros candidatos para ascender a Adamantín. La batalla transcurrirá por turnos y cada jugador podrá invocar a los diferentes guerreros del mundo, conocer sus historias y controlarlos por el tablero.

Ya que los candidatos combatirán para convertirse en Adamantines, las decisiones que tome el jugador en torno a las acciones del personaje serán decisivas y tendrá que pensar de manera estratégica para hacerse con la victoria.

# Contenido
## Historia 
En un mundo de dioses el destino del mundo está escrito sobre el Pergamino Celeste, y son los Adamantines los que se encargan de escribir en este pergamino el transcurso de la historia.

Recientemente, uno de los Adamantines fue expulsado del Consejo Diamante por infringir las normas establecidas 14000 años atrás y alterar el ritmo de la historia, y es por esto que los Adamantines han empezado una Guerra para poder declarar al nuevo Adamantín.

Los candidatos a Adamantín poseen la capacidad de invocar guerreros que un día lucharon por su propia causa, y hoy luchan a favor de cada candidato. Estos guerreros son nativos del mundo que los Adamantines se encargan de regir, pero cada uno vino de una diferente época y de un diferente lugar.

Los candidatos deberán demostrar sus cualidades como Adamantín mediante el buen control de estos personajes a los que invocan y su capacidad de pintar su historia y sus acciones.

## Personajes
### Druida 
Ermitaño que entra en la guerra para preservar la naturaleza y ponerle fin a la destrucción que sucede. Es capaz de comunicarse con las plantas, y mediante un elixir que fabrica (cooldown) es capaz de mutarlas, haciendo que crezcan y atrapen a sus enemigos.
### Tanque 
Ex-militar que formaba parte de la División Alpha y era la mejor en su quinta. Pasó la mayor parte de su vida en el campo de batalla, y entabló muchas amistades con sus compañeros, a los que consideraba familia. Tras tener que presenciar la muerte de todos ellos, surge un cambio dentro de ella que la hace dejar la ofensiva para siempre y defender a todo el que pudiera en el campo de batalla.
### Rogue
Dentro de la ciudad, en los barrios más pobres se crió una mujer como arma cuyo objetivo es matar al objetivo que el cliente desea, ganándose la vida y escalando poco a poco al nivel más alto de la sociedad.
### Monaguillo
Niño huérfano que fue acogido por la Iglesia y le echaron de ésta por su conducta rebelde. Nunca atendía a las lecciones de misa o hacía las tareas, ni mostraba asertividad con nadie. Estaba en un entorno en el que no podía ser él mismo. Cuando le echaron, se aseguraron de que no pudiera cometer ningún acto rebelde y le revocaron las artes mágicas que poseía, dejándole solo con artes curativas. Al salir, tuvo que buscarse la vida y se topó con un grupo del ejército, y encontró el objetivo de su vida. Aunque no pudiera dedicarse a atacar, lucharía en la guerra utilizando sus artes curativas.
### Gólem
Un mago experimentando con una roca se dio cuenta que sus poderes no servían para invocar elementos de la naturaleza como sus compañeros, sino para dar vida a objetos inanimados. Así es como dio a luz a su grandioso colosal, pero una vez acaba la vida mágica de ésta vuelve a su estado original.
### Vikingo
Dentro de una aldea creció un niño cuyo objetivo era ser el luchador más fuerte y poderoso de la tribu. Cada día de su vida se lo pasó practicando su lanzamiento de hacha y con esfuerzo y dedicación se convirtió en el luchador más imprescindible de la tribu. En un abrir y cerrar de ojos, es capaz de matar una tropa enemiga a larga distancia.
### Arquitecta
Después de tener un pasado difícil donde sus padres le obligaron a ser arquitecta, ella detestaba el trabajo de sus padres. Una vez sus lazos acabó utilizando su técnica de arquitectura en la guerra para ver cómo sus creaciones eran destruidas y así autocomplacerse.
### Lobo
Durante años, muchos magos se han dedicado a dominar hechizos de invocación de distintos elementos de la naturaleza. Otros magos se dedican a experimentar con plantas. Una vez, un mago consiguió fabricar una planta cuyo fruto alberga poderes de los elementos de la naturaleza y pensando que esta era inutil se desechó de ella. Donde más tarde un lobo se comió la fruta del viento adquiriendo el poder de esta.
### Bomba humana
Criminal altamente peligroso al que le han dictado una pena de muerte. Le ofrecen la posibilidad de salir de la cárcel en el caso de que luche en la guerra a favor de la penitenciaria, pero le engañan y le colocan una runa en la espalda que se detona cuando llega al territorio enemigo.
### Kirin
Espectro de años atrás que vive paseándose por los campos de batalla. Lo único que alienta sus garbeos es la sed de sangre que nunca desapareció al morir. Extrañamente, el monaguillo es la viva imagen de su hijo, y por esto mismo Kirin pasa el tiempo que no está vagando por el campo de batalla con el monaguillo. No tiene capacidad de comprensión ni entendimiento pero en el monaguillo siente la calidez que sentía cuando murió mientras pensaba en su hijo.
### Cazador
En la cultura del bosque no se puede considerar a una persona cazador si no completó una prueba a los 10 años. Deben adentrarse solos en el bosque y no volver a la aldea hasta que traigan consigo a un animal fuerte para que sea su compañero, muchos niños no lo consiguen y mueren de hambre o incluso devorados por los animales que buscan. Nuestro cazador se encontraba solo y sin fuerzas, a punto de alcanzar la muerte, cuando un lobo solitario, que había perdido la manada se acurrucó junto a ella. Fue el inicio de su historia, en la actualidad viven juntos las batallas para que los humanos no amenacen la supervivencia del bosque.
### Alquimista 
Prodigio de la ingeniería y la alquimia que nunca ha sabido diferenciar entre el bien y el mal. Su ansia y curiosidad por la ciencia la llevó a realizar prácticas inmorales de las cuales se acabaron enterando las fuerzas armadas. En el día de su juicio, fue bien preparada y bombardeó el palacio de su ciudad, escapando por lo más alto. 
Ahora es una fugitiva que se ha refugiado en la guerra para que no sean capaces de encontrarla, y nadie sabe de su pasado excepto ella misma.
### Esqueleto
Tras tantas batallas los soldados caídos en combate han perdido todo aquello que una vez les hacía distintos y especiales. Ahora solo sirven como carne de cañón después de revivir como puro odio hacia el oponente.


# Modo de juego
## Multijugador local
El jugador podrá elegir el número de adversarios contra los que quiere jugar. Todos ellos jugarán desde el mismo dispositivo.
## Multijugador online
El jugador podrá elegir entre crear sala o unirse a una, dependiendo de la elección.	
