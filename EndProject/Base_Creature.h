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
	//�d���ʧ@ and �ƭ�
	vector<Card_Property> Movement;
};

/*=============�ͪ��ҪO=============*/

class Base_Creature
{
public:
	//Constructure
	Base_Creature();
	Base_Creature(string name,int hp);

	//Property

	//�ͪ��W�l
	string Name;
	//�ͪ��ͩR
	int Hp;
	//�ͪ��ˮ`
	int Damage;
	//�ͪ��d��
	int Attack_Range;
	//
};

