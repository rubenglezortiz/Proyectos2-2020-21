// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere

class Ability_Alchemist;
class TanqueA;
class Ability_Architect;
class Ability_Bomb;
class Ability_Creeper;
class Ability_Druid;
class Ability_Golem;
class Ability_Kirin;
class Ability_Priest;
class Ability_Rogue;
class Ability_Viking;
class Ability_Wolf;
class Ability_Tank;
class Ability;
class Attack;
class ButtonCharacterSelection;
class ButtonDescription;
class ButtonHovered;
class ButtonSelected;
class ButtonSettings;
class ButtonSurrender;
class ButtonPlay;
class ButtonTick;
class ButtonVolume;
class DeckSpawn;
class FramedImage;
class GameMap;
class Health;
class Image;
class Interfaz;
class MenuButton;
class MovementShader;
class Movimiento;
class PointOnImage;
class Transform;
class Transform2;

#define _CMPS_LIST_  \
	Ability						    ,  \
	Ability_Alchemist			    ,  \
	Ability_Architect			    ,  \
	Ability_Bomb				 	,  \
	Ability_Creeper				    ,  \
	Ability_Druid				    ,  \
	Ability_Golem					,  \
	Ability_Kirin					,  \
	Ability_Priest				    ,  \
	Ability_Rogue				    ,  \
	Ability_Viking				    ,  \
	Ability_Wolf		    	    ,  \
	Ability_Tank				    ,  \
	Attack							,  \
	ButtonCharacterSelection		,  \
	ButtonDescription               ,  \
	ButtonHovered					,  \
	ButtonSelected					,  \
	ButtonSettings					,  \
	ButtonSurrender					,  \
	ButtonPlay						,  \
	ButtonTick						,  \
	ButtonVolume					,  \
	DeckSpawn					    ,  \
	FramedImage					    ,  \
	GameMap							,  \
	Health						    ,  \
	Image							,  \
	Interfaz						,  \
	MenuButton				   	    ,  \
	MovementShader				    ,  \
	Movimiento						,  \
	PointOnImage					,  \
	Transform						,  \
	TanqueA						    ,  \
	Transform2

	// groups

struct Personajes;
struct Attack;
struct Defense;
struct Utility;
struct Mazo1;
struct Mazo2;
struct Equipo_Rojo;
struct Equipo_Azul;

#define _GRPS_LIST_ \
	Personajes	, \
	Attack , \
	Defense , \
	Utility , \
	Mazo1       , \
	Mazo2       , \
	Equipo_Rojo , \
	Equipo_Azul 


// handlers
struct Hdlr_1;
struct Mapa;
struct BoardManager;

#define _HDLRS_LIST_ Hdlr_1, Mapa, BoardManager