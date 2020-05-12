#include "Ethnicity.h"

void Ethnicity::add_newMonster(string name, int hp, int atk, int range, int elite_hp, int elite_damage, int elite_range) 
{
	Monster_Base newMonster(name, hp, atk, range, elite_hp, elite_damage, elite_range);
	this->Creature_List.push_back(newMonster);
}