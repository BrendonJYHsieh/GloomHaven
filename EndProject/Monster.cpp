#include "Monster.h"
Monster::Monster() :Base_Creature() {}
Monster::Monster(string name, int hp, int damage, int range) :Base_Creature(name, hp)
{
	this->Damage = damage;
	this->Attack_Range = range;
}