#pragma once
#include<vector>
#include<iostream>
using namespace std;
class Map;

struct Player_Card
{
	//�d��ID
	int ID;
	//�ӱ���
	int Dexterity_Value;
	//�d��(�W)�ʧ@ and �ƭ�
	vector<Card_Property> MovementUp;
	//�d��(�U)�ʧ@ and �ƭ�
	vector<Card_Property> MovementDown;
	/*�d�����A	0:�b�P���	1:��W	2:��P��  3:����  4:�X�P��	�����ϥ�ERASE�N�������A�קK���s�}�l�C���ɲ��Ͱ��D*/
	int status = 3;
};

/*==========����ҪO===========*/

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
	/*====��T====*/
	//icon
	char ID;
	//��m
	Position position;
	//�W�l
	string Character_name;
	//�ثe�ͩR��
	int Hp;
	//�̤j�ͩR��
	int Max_HP;
	//��q�@��
	int Shield;
	//��P�ƶq
	int Hand;
	//�n���X����i�P
	int Command[2] = {0,0};
	//�O�_�����𪬺A
	bool Rest = false;
	//�P��
	vector<Player_Card> Deck;
};