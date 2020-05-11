#pragma once
#include "Base_Creature.h"
class Monster :
	public Base_Creature
{
public:
	//Constructure Ä~©Ó
	Monster();
	Monster(string name, int hp, int damage, int range);
	//©Çª«¶Ë®`
	int Damage;
	//§ğÀ»½d³ò
	int Attack_Range;
};

