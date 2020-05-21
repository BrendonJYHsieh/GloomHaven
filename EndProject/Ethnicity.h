#pragma once
#include "Monster_Base.h"
class Ethnicity 
{
public:
	//Constructure Ä~©Ó
	Ethnicity();
	Ethnicity(string name, int hp, int atk, int range, int elite_hp, int elite_damage, int elite_range):Ethnicity_Name(name)
	{
		Monster_Base newMonster(name, hp, atk, range, elite_hp, elite_damage, elite_range);
		this->Ethnicity_Base_value = newMonster;
	}

	void add_newMonster(string name, int hp, int atk, int range, int elite_hp, int elite_damage, int elite_range);

	string Ethnicity_Name;
	vector<Monster_Base> Creature_List;
	Monster_Base Ethnicity_Base_value;	//¼ÒªO
	//¦^¦X±Ó±¶­È
	int Dex;
	vector<Creature_Card>Deck;
};