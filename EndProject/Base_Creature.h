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
	//卡片(上)動作 and 數值
	vector<Card_Property> MovementUp;
	//卡片(下)動作 and 數值
	vector<Card_Property> MovementDown;
};
class Base_Creature
{
public:
	//Constructure
	Base_Creature();
	Base_Creature(string name,int hp);

	//Property
	string Name;
	int Hp;
	vector<Card>Cards;
};

