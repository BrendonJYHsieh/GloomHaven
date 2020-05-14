#pragma once
#include"Ethnicity.h"
#include"Character.h"
#include"GameMap.h"
#include <conio.h>
#include<Windows.h>
#include<fstream>
#include<sstream>
#include<algorithm>

/*=============main_function==============*/
//�C���D�{��
void Main_Game(fstream& File_Character,fstream& File_Monster, fstream& File_Map);			//�D�{��
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character);	//�Ыب���
void choose_Start_Position(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map);	//��ܰ_�l��m
//Ū��
void read_Character_Data(fstream& File_Character, vector<Character>& Base_Character);	//Ū�������ɮ�
void read_Monster_Data(fstream& File_Monster, vector<Ethnicity>& Base_Monster);			//Ū���Ǫ��ɮ�
void read_Map_Data(fstream& File_Map,Map& Game_Map, vector<Ethnicity>& Base_Monster,int);//Ū���a���ɮ�

/*==============DEBUG_MODE================*/

void get_All_Base_Character_Data(vector<Character> Base_Character);	//��ܩҦ����⪺�ܼƭ�
void get_All_Base_Monster_Data(vector<Ethnicity> Base_Monster);		//��ܩҦ��رڪ��ܼƭ�
void get_int_Map(Map Map);

/*================UI_MODE=================*/
void Main_Game_UI();		//UI�Ҧ�
int Project_Start_UI();		//�}�l����

/*=============Windows.h��function==============*/

void setPrintPosition(int x, int y);	//����Print���_�l��m

void SetColor(int color);				//�����C��
