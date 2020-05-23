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
//�C���D�{��
void Main_Game(fstream& File_Character,fstream& File_Monster, fstream& File_Map);			//�D�{��
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character);	//�Ыب���
void choose_Start_Position(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map);	//��ܰ_�l��m
void main_Battle(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map);
void check(Character C);
void check_Monsters_Active(vector<Ethnicity>& Monster, Map Game_Map);

//�ʧ@
void players_round(vector<Character>& play_Character, Character& Character, vector<Ethnicity>& Monster, Map& Game_Map);
void monsters_round(vector<Character>& play_Character,Ethnicity& Monster_Ethnicity,Monster_Base& monster, Map Game_Map, vector<Ethnicity>& Monster, vector<char> attack_Sort);
void end_round(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Map);
void character_move(Character& C, int step, Map& Game_Map, vector<Character> play_Character, vector<Ethnicity> Monster); //���Ⲿ��
void monster_move(Monster_Base& C, string position_input, Map& Game_Map, vector<Character> play_Character, vector<Ethnicity> Monster);
bool monster_Attack(Monster_Base& M, int value, int range, vector<char> attack_Sort, vector<Ethnicity> Monster, vector<Character>& play_Character, Map& Game_Map);
//Ū��
void read_Character_Data(fstream& File_Character, vector<Character>& Base_Character);	//Ū�������ɮ�
void read_Monster_Data(fstream& File_Monster, vector<Ethnicity>& Base_Monster);			//Ū���Ǫ��ɮ�
void read_Map_Data(fstream& File_Map,Map& Game_Map, vector<Ethnicity>& Base_Monster,int);//Ū���a���ɮ�
/*==============Support================*/

int calculate_Discard(Character); //�p�⨤���P�諸�ƶq
bool IsPlayHandCard(Character&,string); //�P�_�O�_���X�P
bool IsCardInHand(Character &C, int card); //�P�_�X���P�O�_�b���T and �X�P
bool check_player_done(bool* player, int num);
void show_AttackList( vector<char> attack_Sort,vector<Character> Play_Character,vector<Ethnicity> Monster);
int get_Character_Dex(vector<Character> Play_Character, char name, int num);
int get_Monster_Dex(vector<Ethnicity> Monster, char name);
bool find_by_step(int x1, int y1, int x2, int y2, int step);
bool vision_search(Position, Position, Map);
bool move_Error(int x, int y, vector<Character> play_Character, vector<Ethnicity> Monster, Map Game_Map);
bool move_Error_Monster(int x, int y, vector<Character> play_Character, Map Game_Map);
void print_character_sort_onActive_monster(vector<Ethnicity> Monster,vector<Character>); //�Ǫ����Ӷ��Ǳ� and print 
bool abcSort(Monster_Base a, Monster_Base b);

/*==============DEBUG_MODE================*/

void get_All_Base_Character_Data(vector<Character> Base_Character);	//��ܩҦ����⪺�ܼƭ�
void get_All_Base_Monster_Data(vector<Ethnicity> Base_Monster);		//��ܩҦ��رڪ��ܼƭ�
void get_int_Map(Map Map);		//���int�������a��
void check_all_dex(vector<Character> Play_Character, vector<Ethnicity> Monster);	//�ˬd���^�X�Ҧ��ͪ����ӱ���

/*================UI_MODE=================*/
void Main_Game_UI();		//UI�Ҧ�
int Project_Start_UI();		//�}�l����

/*=============Windows.h��function==============*/

void setPrintPosition(int x, int y);	//����Print���_�l��m

void SetColor(int color);				//�����C��
