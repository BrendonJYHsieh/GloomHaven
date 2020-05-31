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
#include<iomanip>

/*=============main_function==============*/
void Main_Game(fstream& File_Character,fstream& File_Monster, fstream& File_Map,int DEBUG_MODE); //主程式
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character);	//創建角色 - 已防呆
void choose_Start_Position(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map);	//選擇起始位置 - 已防呆
void main_Battle(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map, int DEBUG_MODE); //回合開始
bool end_Game(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Map); //判斷是否結束遊戲
/*==============Movement================*/
void players_round(vector<Character>& play_Character, Character& Character, vector<Ethnicity>& Monster, Map& Game_Map); //角色回合 
void monsters_round(vector<Character>& play_Character,Ethnicity& Monster_Ethnicity,Monster_Base& monster, Map Game_Map, vector<Ethnicity>& Monster, vector<char> attack_Sort); //怪物回合
void end_round(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Map); //回合結算 
void check(Character C); //狀態輸出
void character_move(Character& C, int step, Map& Game_Map, vector<Character> play_Character, vector<Ethnicity> Monster); //角色移動
void monster_move(Monster_Base& C, string position_input, Map& Game_Map, vector<Character> play_Character, vector<Ethnicity> Monster); //怪物移動
bool monster_Attack(Monster_Base& M, int value, int range, vector<char> attack_Sort, vector<Ethnicity> Monster, vector<Character>& play_Character, Map& Game_Map); //怪物攻擊
/*==============ReadFile================*/
void read_Character_Data(fstream& File_Character, vector<Character>& Base_Character);	//讀取角色檔案
void read_Monster_Data(fstream& File_Monster, vector<Ethnicity>& Base_Monster);			//讀取怪物檔案
void read_Map_Data(fstream& File_Map,Map& Game_Map, vector<Ethnicity>& Base_Monster,int);//讀取地圖檔案
/*==============Support================*/
int calculate_Discard(Character); //計算角色棄牌堆的數量
bool IsPlayHandCard(Character&,string); //判斷是否為出牌
bool IsCardInHand(Character &C, int card); //判斷出的牌是否在正確 and 出牌
void check_Monsters_Active(vector<Ethnicity>& Monster, Map Game_Map); //檢查怪物是否現身
bool check_player_done(bool* player, int num); //判斷是否都出完牌了
void show_AttackList( vector<char> attack_Sort,vector<Character> Play_Character,vector<Ethnicity> Monster); //Show攻擊順序
int get_Character_Dex(vector<Character> Play_Character, char name, int num); //取得特定名稱的敏捷值
int get_Monster_Dex(vector<Ethnicity> Monster, char name); //取得特定名稱的敏捷值
bool find_by_step(int x1, int y1, int x2, int y2, int step); //遞迴判斷可以走的路
bool vision_search(Position, Position, Map); //線性插值法
bool move_Error(int x, int y, vector<Character> play_Character, vector<Ethnicity> Monster, Map Game_Map); //判斷角色是否移動正確
bool move_Error_Monster(int x, int y, vector<Character> play_Character, Map Game_Map); //判斷怪物是否移動正確
void print_character_sort_onActive_monster(vector<Ethnicity> Monster,vector<Character>); //怪物按照順序排 and print 
bool abcSort(Monster_Base a, Monster_Base b); //英文排序

/*==============DEBUG_MODE================*/
void get_All_Base_Character_Data(vector<Character> Base_Character);	//顯示所有角色的變數值
void get_All_Base_Monster_Data(vector<Ethnicity> Base_Monster);		//顯示所有種族的變數值
void get_int_Map(Map Map);		//顯示int版本的地圖
void check_all_dex(vector<Character> Play_Character, vector<Ethnicity> Monster);	//檢查此回合所有生物的敏捷值
/*================UI_MODE=================*/
void Main_Game_UI();		//UI模式
int Project_Start_UI();		//開始介面
/*=============Windows.h的function==============*/
void setPrintPosition(int x, int y);	//改變Print的起始位置
void SetColor(int color);				//改變顏色
