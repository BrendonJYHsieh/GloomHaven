#pragma once
#include "Monster_Base.h"
class Ethnicity : public Monster_Base
{
public:
	//Constructure Ä~©Ó
	Ethnicity();
	Ethnicity(string name);
	~Ethnicity();

	string Ethnicity_Name;
	vector<Monster_Base> Creature_List;
	vector<Creature_Card>Deck;
};

