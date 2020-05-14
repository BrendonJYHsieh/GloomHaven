#pragma once
#include"Ethnicity.h"
#include"Character.h"
#include"GameMap.h"
#include <conio.h>
#include<Windows.h>
#include<fstream>
#include<sstream>

/*=============main_function==============*/

void Main_Game(fstream& File_Character,fstream& File_Monster);			//主程式
void read_Character_Data(fstream& File_Character, vector<Character>& Base_Character);	//讀取角色檔案
void read_Monster_Data(fstream& File_Monster, vector<Ethnicity>& Base_Monster);			//讀取怪物檔案
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character);

/*==============DEBUG_MODE================*/

void get_All_Base_Character_Data(vector<Character> Base_Character);	//顯示所有角色的變數值
void get_All_Base_Monster_Data(vector<Ethnicity> Base_Monster);		//顯示所有種族的變數值

/*================UI_MODE=================*/
void Main_Game_UI();		//UI模式
int Project_Start_UI();		//開始介面

/*=============Windows.h的function==============*/

void setPrintPosition(int x, int y);	//改變Print的起始位置

void SetColor(int color);				//改變顏色
