#pragma once
#include"Ethnicity.h"

class Monster : public Ethnicity 
{
public:
	Monster();
	~Monster();
private:
	vector<Ethnicity> Ethnicity_List;
};