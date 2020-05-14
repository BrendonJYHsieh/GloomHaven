#pragma once
#include"Ethnicity.h"
#include"Character.h"
#include"GameMap.h"
#include <conio.h>
#include<Windows.h>
#include<fstream>
#include<sstream>

/*=============main_function==============*/

void Main_Game(fstream& File_Character,fstream& File_Monster);			//�D�{��
void read_Character_Data(fstream& File_Character, vector<Character>& Base_Character);	//Ū�������ɮ�
void read_Monster_Data(fstream& File_Monster, vector<Ethnicity>& Base_Monster);			//Ū���Ǫ��ɮ�
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character);

/*==============DEBUG_MODE================*/

void get_All_Base_Character_Data(vector<Character> Base_Character);	//��ܩҦ����⪺�ܼƭ�
void get_All_Base_Monster_Data(vector<Ethnicity> Base_Monster);		//��ܩҦ��رڪ��ܼƭ�

/*================UI_MODE=================*/
void Main_Game_UI();		//UI�Ҧ�
int Project_Start_UI();		//�}�l����

/*=============Windows.h��function==============*/

void setPrintPosition(int x, int y);	//����Print���_�l��m

void SetColor(int color);				//�����C��
