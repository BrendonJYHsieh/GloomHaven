#pragma once
#include<vector>
#include<iostream>
using namespace std;

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

	/*卡片狀態	0:在牌堆裡	1:手上	2:棄牌區	離場時使用erase將卡牌刪除*/
	int status = 0;
};

/*==========角色模板===========*/

class Character
{
public:
	Character();
	~Character();

	//位置
	Position position;
	//名子
	string Character_name;
	//生命值
	int Hp;
	//手牌數量
	int Hand;
	//牌組
	vector<Player_Card> Deck;
};