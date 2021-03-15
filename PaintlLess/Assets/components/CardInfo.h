#pragma once

#include "../ecs/Component.h"

class Texture;

enum TipoCarta {Ataque, Defensa, Utilidad};

enum TipoMov { Normal, Saltar };


struct InfoMov {
	InfoMov(unsigned int alc, TipoMov tipoMov): alcanceMov(alc), tipoMov(tipoMov), energiaMov(1){}
	unsigned int alcanceMov, energiaMov;
	TipoMov tipoMov;

};
class CardInfo : public Component {

public:

	CardInfo(TipoCarta tipoCarta, Texture* ic, unsigned int currentCD, unsigned int maxCD, unsigned int mana, unsigned int alcanceAt, unsigned int damage, unsigned int alcMov, TipoMov tipoMov):
	tipoCarta(tipoCarta),
	currentCoolDown(currentCD), maxCoolDown(maxCD), mana(mana), alcanceAt(alcanceAt), damage(damage),
	infoMov(alcMov, tipoMov)
	{

		if (tipoCarta == TipoCarta::Defensa) {
			infoMov.energiaMov = 2;
		}
		
		
	}


private:
	
	unsigned int currentCoolDown, maxCoolDown, mana, vida, alcanceAt, damage;
	Texture* icono;
	TipoCarta tipoCarta;
	InfoMov infoMov;


};