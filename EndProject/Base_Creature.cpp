#include "Base_Creature.h"
Base_Creature::Base_Creature() {
	this->Hp = 0;
	this->Name = "";
	this->Cards.clear();
}
Base_Creature::Base_Creature(string name,int hp) {
	this->Hp = hp;
	this->Name = name;
}