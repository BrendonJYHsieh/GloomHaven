#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Map
{
public:
	Map(){}
	Map(int Width, int High){}
	~Map() {
		Monster_Count = 0;
		Width = 0;	
		High = 0;
		Game_Map.clear();
		Init_Pos.clear();
	}
	/*===fuction===*/
	void check_road(int x,int y);
	void print_Map(vector<Character> player, vector<Ethnicity> Monster);
	void print_Map_UI(vector<Character> player, vector<Ethnicity> Monster);
	/*====value====*/
	int Monster_Count = 0;
	int Width = 0;	//�e
	int High = 0;		//��
	vector<vector<int>> Game_Map;	//0:��	1:��		2:��ê��		3:��
	vector<Position> Init_Pos;
};