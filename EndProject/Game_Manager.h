#pragma once
#include"Ethnicity.h"
#include"Players.h"
#include"GameMap.h"
#include <conio.h>
#include<Windows.h>
#include<fstream>

/*=============main_function==============*/
void Main_Game(fstream& File_Character,fstream& File_Monster);			//�D�{��
void get_Character_Data(vector<Character> Player);

/*==============DEBUG_MODE================*/

/*================UI_MODE=================*/
void Main_Game_UI();
int Project_Start_UI();		//�}�l����

/*=============Windows.h��function==============*/

void setPrintPosition(int x, int y);	//����Print���_�l��m

void SetColor(int color);				//�����C��
