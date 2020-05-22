#pragma once
#include<vector>
#include<iostream>
using namespace std;
class Map;

struct Player_Card
{
	//卡片ID
	int ID;
	//敏捷值
	int Dexterity_Value;
	//卡片(上)動作 and 數值
	vector<Card_Property> MovementUp;
	//卡片(下)動作 and 數值
	vector<Card_Property> MovementDown;
	/*卡片狀態	0:在牌堆裡	1:手上	2:棄牌區  3:離場  4:出牌中	取消使用ERASE代替離場，避免重新開始遊戲時產生問題*/
	int status = 3;
};

/*==========角色模板===========*/

class Character
{
public:
	Character();
	Character(string name,int hp,int hand):Character_name(name),Hp(hp),Hand(hand),Max_HP(hp){}
	/*=====function=====*/

	void Add_NewCard();
	bool Attack(int value,vector<Ethnicity>& Monster);
	bool Attack(int value ,int range, vector<Ethnicity>& Monster,Map map);
	void long_Rest();
	void Skill_shield(int x) {
		this->Shield = x;
	}
	void Skill_heal(int x) {
		if ((this->Hp + x) > this->Max_HP) {
			this->Hp = this->Max_HP;
		}
		else {
			this->Hp += x;
		}
	}
	/*====資訊====*/
	//icon
	char ID;
	//位置
	Position position;
	//名子
	string Character_name;
	//目前生命值
	int Hp;
	//最大生命值
	int Max_HP;
	//能量護盾
	int Shield;
	//手牌數量
	int Hand;
	//要打出的兩張牌
	int Command[2] = {0,0};
	//是否為長休狀態
	bool Rest = false;
	//牌組
	vector<Player_Card> Deck;
};