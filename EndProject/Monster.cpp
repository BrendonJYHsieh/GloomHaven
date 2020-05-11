#include "Ethnicity.h"

Ethnicity::Ethnicity(string name)
{
	this->Ethnicity_Name = name;
}

void Ethnicity::Add_Creature(string name, int hp, int atk, int range, int elite_hp, int elite_damage, int elite_range) 
{
	Base_Creature new_Creature(name, hp, atk, range, elite_hp, elite_damage, elite_range);
	this->Creature_List.push_back(new_Creature);
}