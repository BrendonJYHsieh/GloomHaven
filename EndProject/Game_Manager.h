#pragma once
#include"Ethnicity.h"
#include"Players.h"
#include"GameMap.h"
#include <conio.h>
#include<Windows.h>
#include<fstream>

/*=============main_function==============*/
void Main_Game(fstream& File_Character,fstream& File_Monster);			//主程式
void get_Character_Data(vector<Character> Player);

/*==============DEBUG_MODE================*/

/*================UI_MODE=================*/
void Main_Game_UI();
int Project_Start_UI();		//開始介面

/*=============Windows.h的function==============*/

void setPrintPosition(int x, int y);	//改變Print的起始位置

void SetColor(int color);				//改變顏色
