#pragma once
#include<vector>
#include<iostream>
using namespace std;
struct Card_Property_Player
{
	string Movement;
	int Movement_Value;
};
struct Player_Card
{
	//�d��ID
	int ID;
	//�ӱ���
	int Dexterity_Value;
	//�d��(�W)�ʧ@ and �ƭ�
	vector<Card_Property_Player> MovementUp;
	//�d��(�U)�ʧ@ and �ƭ�
	vector<Card_Property_Player> MovementDown;

	/*�d�����A	0:�b�P���	1:��W	2:��P��	�����ɨϥ�erase�N�d�P�R��*/
	int status = 0;
};

/*==========����ҪO===========*/

class Character
{
public:
	Character();
	~Character();

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