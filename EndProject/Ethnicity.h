#pragma once
#include "Base_Creature.h"
class Ethnicity : public Base_Creature
{
public:
	//Constructure Ä~©Ó
	Ethnicity();
	Ethnicity(string name);
	~Ethnicity();

	void Add_Creature(string name, int hp, int atk, int range, int elite_hp, int elite_atk, int elite_range);
private:
	string Ethnicity_Name;
	vector<Base_Creature> Creature_List;
	vector<Creature_Card>Deck;
};

