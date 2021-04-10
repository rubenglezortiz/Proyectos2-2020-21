#pragma once
enum Unit { Alquimista, Arquitecta, Bomba, Cazador, Druida, Esqueleto, Golem, Kirin, Lobo, Monaguillo, Picara, Tanque, Vikingo };

//enum TipoCarta { Ataque, Defensa, Utilidad };

typedef unsigned int uint;

namespace UnitInfo {
    const uint Movimiento[2] = { 3, 2 };
    const uint numUnidades = 13;
    const uint health[numUnidades] = { 2, 2, 3, 1, 2, 1, 4, 2, 2, 1, 2, 4, 1 };
    const uint cooldown[numUnidades] = { 3, 3, 3, 2, 3, 1, 3, 2, 2, 2, 3, 2, 2 };
    const uint mana[numUnidades] = { 3, 3, 3, 2, 3, 1, 4, 3, 3, 3, 2, 4, 2 };
    const uint damage[numUnidades] = { 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 0, 1 };
    //const uint Movimiento[numUnidades] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; //OLE MIS HUEVOS. RUBEN RULES
    //const TipoCarta tiposCartas[numUnidades] = { Utilidad, Utilidad, Utilidad, Ataque, Utilidad, Ataque, Defensa, Ataque, Utilidad, Defensa, Ataque, Defensa, Ataque };
}