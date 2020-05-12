#pragma once
#include<vector>
#include<iostream>
using namespace std;
struct Card_Property
{
	string Movement;
	int Movement_Value;
};
struct Creature_Card
{
	//卡片ID
	int ID;
	//敏捷值
	int Dexterity_Value;
	//卡片動作 and 數值
	vector<Card_Property> Movement;
	/*卡片狀態	0:在牌堆裡	1:棄牌區*/
	int status = 0;
	//重洗標誌
	bool Shuffle_Mark;
};
struct Position
{
	int x;
	int y;
};

/*=============生物模板=============*/

class Monster_Base
{
public:
	//Constructure
	Monster_Base();
	Monster_Base(string name,int hp);
	Monster_Base(string name, int hp, int atk, int range, int elite_hp, int elite_damage, int elite_range);

	//Property
	Position position;
	//生物名子
	string Name;
	//生物生命
	int Hp;
	//生物傷害
	int Damage;
	//生物範圍
	int Range;
	//菁英生物生命
	int Elite_Hp;
	//菁英生物傷害
	int Elite_Damage;
	//菁英生物範圍
	int Elite_Range;
	//怪物狀態 0:隱藏	1:普通	2:菁英
	int mode;
};

