#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Map
{
public:
	Map(){}
	Map(int Width, int High){}
	/*===fuction===*/
	void check_road(int x,int y, int dir);
	void print_Map(vector<Character> player, vector<Ethnicity> Monster);
	/*====value====*/
	int Width = 0;	//�e
	int High = 0;		//��
	vector<vector<int>> Game_Map;	//0:��	1:��		2:��ê��		3:��
	vector<Position> Init_Pos;

};