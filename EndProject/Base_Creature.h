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
	//�d��ID
	int ID;
	//�ӱ���
	int Dexterity_Value;
	//�d��(�W)�ʧ@ and �ƭ�
	vector<Card_Property> MovementUp;
	//�d��(�U)�ʧ@ and �ƭ�
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

