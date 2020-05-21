#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Card_Property
{
	string Movement;
	int Movement_Value;
	string Move_Command;	//�ȩǪ�move���O�ɨϥ�
	int range = 0;	//�d�� �w�]��0�A����
};
struct Creature_Card
{
	//�d��ID
	int ID;
	//�ӱ���
	int Dexterity_Value;
	//�d���ʧ@ and �ƭ�
	vector<Card_Property> Movement;
	/*�d�����A	0:�b�P���	1:��P�� 2:�X�P��*/
	int status = 0;
	//���~�лx
	bool Shuffle_Mark = false;
};
struct Position
{
	int x = 0;
	int y = 0;
};

/*=============�ͪ��ҪO=============*/

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
	//�ͪ��W�l
	string Name;
	//�ͪ��ثe�ͩR
	int Hp;
	//�̤j�ͩR
	int Max_HP;
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
	//�Ǫ����A 0:����1:���q	2:�׭^
	int mode = 0;
	//�ӱ���
	int Dex;
	//icon
	char icon;
	//�P�_�O�_�b�i���d�򤺡A�p�G���b�A�N���|�i�����ʧ@
	bool active=false;
};

