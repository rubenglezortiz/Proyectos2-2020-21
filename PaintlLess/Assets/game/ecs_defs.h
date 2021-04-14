// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere

class Ability_Architect;
class Ability_Bomb;
class Ability_Golem;
class Ability_Kirin;
class Ability_Rogue;
class Ability_Viking;
class Ability_Druid;
class Ability_Creeper;
class Attack;
class GameMap;
class Health;
class Image;
class MenuButton;
class MovementShader;
class Movimiento;
class PointOnImage;
class Transform;

#define _CMPS_LIST_  \
	Ability_Architect   ,  \
	Ability_Bomb		,  \
	Ability_Golem		,  \
	Ability_Kirin		,  \
	Ability_Rogue	    ,  \
	Ability_Viking      ,  \
	Ability_Druid       ,  \
	Ability_Creeper     ,  \
	Attack				,  \
	GameMap				,  \
	Health              ,  \
	Image				,  \
	MenuButton          ,  \
	MovementShader      ,  \
	Movimiento			,  \
	PointOnImage	    ,  \
	Transform

	// groups

struct Equipo_Rojo;
struct Equipo_Azul;

#define _GRPS_LIST_ \
	Equipo_Rojo, \
	Equipo_Azul 


// handlers
struct Hdlr_1;
struct Mapa;
struct BoardManager;

#define _HDLRS_LIST_ Hdlr_1, Mapa, BoardManager