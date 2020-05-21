#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Card_Property
{
	string Movement;
	int Movement_Value;
	string Move_Command;	//僅怪物move指令時使用
	int range = 0;	//範圍 預設為0，表近戰
};
struct Creature_Card
{
	//卡片ID
	int ID;
	//敏捷值
	int Dexterity_Value;
	//卡片動作 and 數值
	vector<Card_Property> Movement;
	/*卡片狀態	0:在牌堆裡	1:棄牌區 2:出牌中*/
	int status = 0;
	//重洗標誌
	bool Shuffle_Mark = false;
};
struct Position
{
	int x = 0;
	int y = 0;
};

/*=============生物模板=============*/

class Monster_Base
{
public:
	//Constructure
	Monster_Base() {
		this->Hp = 0;
		this->Name = "";
	}
	Monster_Base(string name,int hp) {
		this->Hp = hp;
		this->Name = name;
		this->Max_HP = hp;
	}
	Monster_Base(string name, int hp, int atk, int range, int elite_hp, int elite_damage, int elite_range) {
		this->Name = name; 
		this->Hp = hp; 
		this->Max_HP = hp;
		this->Damage = atk; 
		this->Range = range; 
		this->Elite_Hp = elite_hp; 
		this->Elite_Damage = elite_damage; 
		this->Elite_Range = elite_range;
	}
	//Property
	Position position;
	//生物名子
	string Name;
	//生物目前生命
	int Hp;
	//最大生命
	int Max_HP;
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
	//怪物狀態 0:隱藏1:普通	2:菁英
	int mode = 0;
	//敏捷值
	int Dex;
	//icon
	char icon;
	//判斷是否在可視範圍內，如果不在，就不會進行任何動作
	bool active=false;
};

