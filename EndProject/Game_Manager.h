#pragma once
#include"Ethnicity.h"
#include"Character.h"
#include"GameMap.h"
#include <conio.h>
#include<Windows.h>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<ctime>

/*=============main_function==============*/
//遊戲主程式
void Main_Game(fstream& File_Character,fstream& File_Monster, fstream& File_Map);			//主程式
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character);	//創建角色
void choose_Start_Position(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map);	//選擇起始位置
void main_Battle(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map);
void check(Character C);
//讀檔
void read_Character_Data(fstream& File_Character, vector<Character>& Base_Character);	//讀取角色檔案
void read_Monster_Data(fstream& File_Monster, vector<Ethnicity>& Base_Monster);			//讀取怪物檔案
void read_Map_Data(fstream& File_Map,Map& Game_Map, vector<Ethnicity>& Base_Monster,int);//讀取地圖檔案
/*==============Support================*/
int calculate_Discard(Character); //計算角色棄牌堆的數量
bool IsPlayHandCard(Character&,string); //判斷是否為出牌
bool IsCardInHand(Character &C, int card); //判斷出的牌是否在正確 and 出牌
bool check_player_done(bool* player, int num);
/*==============DEBUG_MODE================*/

void get_All_Base_Character_Data(vector<Character> Base_Character);	//顯示所有角色的變數值
void get_All_Base_Monster_Data(vector<Ethnicity> Base_Monster);		//顯示所有種族的變數值
void get_int_Map(Map Map);

/*================UI_MODE=================*/
void Main_Game_UI();		//UI模式
int Project_Start_UI();		//開始介面

/*=============Windows.h的function==============*/

void setPrintPosition(int x, int y);	//改變Print的起始位置

void SetColor(int color);				//改變顏色
