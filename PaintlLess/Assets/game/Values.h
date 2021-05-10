#pragma once


enum Unit { Alquimista, Arquitecta, Bomba, Cazador, Druida, Esqueleto, Golem, Kirin, Lobo, Monaguillo, Picara, Tanque, Vikingo};
enum UnitAnim {Idle, Death, Attack, Ability};



struct AnimInfo {
	int finCol;
};

struct SpriteSheetInfo {
	int animInfo[4];
	int rows, cols;
};


typedef unsigned int uint;

namespace UnitInfo {
enum TipoCarta {Ataque, Defensa, Utilidad};

	const uint numUnidades = 13;

	const uint Movimiento[2] = { 4, 2 };	
	const uint mana[numUnidades] = { 3, 3, 3, 2, 3, 1, 4, 3, 3, 3, 2, 4, 2 };
	const uint cooldown[numUnidades] = { 3, 3, 3, 2, 3, 1, 3, 2, 2, 2, 3, 2, 2 };

	const SpriteSheetInfo spriteSheetInfo[numUnidades] = { {{0,0,0,0}, 0, 0},   //Alquimista
														  {{0,0,0,0}, 0, 0},   //Arquitecta
														  {{0,0,0,0}, 0, 0},   //Bomba
														  {{0,0,0,0}, 0, 0},   //Cazador
														  {{0,0,0,0}, 0, 0},   //Druida
														  {{0,0,0,0}, 0, 0},   //Esqueleto
														  {{0,0,0,0}, 0, 0},   //Golem
														  {{0,0,0,0}, 0, 0},   //Kirin
														  {{0,0,0,0}, 0, 0},   //Lobo
														  {{0,0,0,0}, 0, 0},   //Monaguillo
														  {{0,0,0,0}, 0, 0},   //Picara
														  {{0,0,0,0}, 0, 0},   //Tanque
														  {{3,4,0,5}, 3, 6}  //Vikingo
	};

	

	//const uint numUnidades = 13;
	//const uint Ataque = {1};
	//
	//const uint Cooldown = {3};
	//const uint Mana = {3};
	//const uint Vida = {2};
	//const TipoCarta tipoCarta = {TipoCarta::Ataque};

	/*  
    const uint health[numUnidades] = { 2, 2, 3, 1, 2, 1, 4, 2, 2, 1, 2, 4, 1 };
    
    const uint damage[numUnidades] = { 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 0, 1 };
    //const TipoCarta tiposCartas[numUnidades] = { Utilidad, Utilidad, Utilidad, Ataque, Utilidad, Ataque, Defensa, Ataque, Utilidad, Defensa, Ataque, Defensa, Ataque };
	}*/

	/*Ataque[Arquitecta] =1;
	Ataque[Bomba] = 0;
	Ataque[Cazador] = 1;
	Ataque[Druida] = 1;
	Ataque[Esqueleto] = 1;
	Ataque[Golem] = 1;
	Ataque[Kirin] = 1;
	Ataque[Lobo] = 0;
	Ataque[Monaguillo] = ;
	Ataque[Picara] = ;
	Ataque[Tanque] = ;
	Ataque[Vikingo] = ;*/
}