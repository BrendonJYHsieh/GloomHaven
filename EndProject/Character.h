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
	void Attack(int value,vector<Ethnicity>& Monster);
	void Attack(int value ,int range, vector<Ethnicity>& Monster);

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
	//��i�P���ӱ���
	int Dex[2] = {0,0};
	//�O�_�����𪬺A
	bool Rest = false;
	//�P��
	vector<Player_Card> Deck;
};