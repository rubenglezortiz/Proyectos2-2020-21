// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere

class Ability_Architect;
class Ability_Bomb;
class Ability_Golem;
class Ability_Rogue;
class Ability_Viking;
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
	Ability_Rogue	    ,  \
	Ability_Viking      ,  \
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

struct Group_1;
struct Lives;
struct Asteroid_grp;
struct Bullet_grp;

#define _GRPS_LIST_ \
	Group_1, \
	Lives ,\
	Asteroid_grp,\
	Bullet_grp


// handlers
struct Hdlr_1;
struct Mapa;
struct BoardManager;

#define _HDLRS_LIST_ Hdlr_1, Mapa, BoardManager



