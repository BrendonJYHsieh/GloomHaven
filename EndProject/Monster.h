#pragma once
#include "Base_Creature.h"
class Monster :
	public Base_Creature
{
public:
	//Constructure �~��
	Monster();
	Monster(string name, int hp, int damage, int range);
	//�Ǫ��ˮ`
	int Damage;
	//�����d��
	int Attack_Range;
};

