// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Rectangle;
class KeyBoardCtrl;
class Bounce;
class Image;
class Rotate;
class GameMap;
class PointOnImage;
class Movimiento;
class MovementShader;
class MenuButton;
class Health;
class Ability_Architect;
class Ability_Rogue;
class Attack;
//class DeAcceleration;
//class Health;
//class ShowAtOpposieSide;
//class Follow;

#define _CMPS_LIST_  \
	Transform,\
	Rectangle,\
	KeyBoardCtrl,\
	Image, \
	Rotate, \
	Bounce , \
	GameMap, \
	Movimiento, \
	PointOnImage, \
	MovementShader, \
	MenuButton, \
	Health, \
	Ability_Architect , \
	Ability_Rogue , \
	Attack
	/*DeAcceleration,\
	Health,\
	ShowAtOpposieSide,\
	Follow*/

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



