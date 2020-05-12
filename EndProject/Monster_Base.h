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
	//�d��ID
	int ID;
	//�ӱ���
	int Dexterity_Value;
	//�d���ʧ@ and �ƭ�
	vector<Card_Property> Movement;
	/*�d�����A	0:�b�P���	1:��P��*/
	int status = 0;
	//���~�лx
	bool Shuffle_Mark;
};
struct Position
{
	int x;
	int y;
};

/*=============�ͪ��ҪO=============*/

class Monster_Base
{
public:
	//Constructure
	Monster_Base();
	Monster_Base(string name,int hp);
	Monster_Base(string name, int hp, int atk, int range, int elite_hp, int elite_damage, int elite_range);

	//Property
	Position position;
	//�ͪ��W�l
	string Name;
	//�ͪ��ͩR
	int Hp;
	//�ͪ��ˮ`
	int Damage;
	//�ͪ��d��
	int Range;
	//�׭^�ͪ��ͩR
	int Elite_Hp;
	//�׭^�ͪ��ˮ`
	int Elite_Damage;
	//�׭^�ͪ��d��
	int Elite_Range;
	//�Ǫ����A 0:����	1:���q	2:�׭^
	int mode;
};

