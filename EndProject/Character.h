#pragma once
#include<vector>
#include<iostream>
using namespace std;
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
	/*�d�����A	0:�b�P���	1:��W	2:��P��  3:����	�����ϥ�ERASE�N�������A�קK���s�}�l�C���ɲ��Ͱ��D*/
	int status = 3;
};

/*==========����ҪO===========*/

class Character
{
public:
	Character();
	Character(string name,int hp,int hand):Character_name(name),Hp(hp),Hand(hand){}
	/*=====function=====*/
	void Add_NewCard();
	/*====��T====*/
	//��m
	Position position;
	//�W�l
	string Character_name;
	//�ͩR��
	int Hp;
	//��P�ƶq
	int Hand;
	//�P��
	vector<Player_Card> Deck;
};