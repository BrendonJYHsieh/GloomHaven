#pragma once
#include "Base_Creature.h"
class Ethnicity :
	public Base_Creature
{
public:
	//Constructure Ä~©Ó
	Ethnicity();
	Ethnicity(string name, int hp, int damage, int range);
	~Ethnicity();

private:
	vector<Card>Deck;
	vector<Base_Creature> Creature_List;
};

