#pragma once
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

	/*�d�����A	0:�b�P���	1:��W	2:��P��	�����ɨϥ�erase�N�d�P�R��*/
	int status = 0;
};

/*==========����ҪO===========*/

class Base_Character 
{
public:
	Base_Character();
	~Base_Character();
private:
	int Hp;
	int Hand;

};