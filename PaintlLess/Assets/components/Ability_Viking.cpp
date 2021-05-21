#include "Ability_Viking.h"

void Ability_Viking::AbilityExecute(int x, int y) {	
	//map->getCharacter(Vector2D(x,y))->getComponent<Health>()->hit(1);
	////sdlutils().soundEffects().at("vikingoSound").setChunkVolume(30);
	//sdlutils().soundEffects().at("vikingoSound").play(); //-----------------------------------------------------------	
	//entity_->getComponent<FramedImage>()->setAnim(A_A_A);
}

bool Ability_Viking::abilityCheck(const Vector2D& pos) {
	/*bool check = false;
	int cont = 0;
	while (!check && cont < abilityCells.size()) {
		if (pos == abilityCells[cont] && this->map->getCharacter(abilityCells[cont]) != nullptr)check = true;
		cont++;
	}
	return check;*/
}
