#pragma once
#include<vector>
#include<iostream>
using namespace std;
struct Card_Property
{
	string Movement;
	int Movement_Value;
};
struct Card
{
	//卡片ID
	int ID;
	//敏捷值
	int Dexterity_Value;
	//卡片動作 and 數值
	vector<Card_Property> Movement;
};

/*=============生物模板=============*/

class Base_Creature
{
public:
	//Constructure
	Base_Creature();
	Base_Creature(string name,int hp);

	//Property

	//生物名子
	string Name;
	//生物生命
	int Hp;
	//生物傷害
	int Damage;
	//生物範圍
	int Attack_Range;
	//
};

