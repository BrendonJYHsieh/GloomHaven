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
	
	/*====value====*/
	int Width = 0;	//�e
	int High = 0;	//��
	vector<vector<int>> Game_Map;	//0:��	1:��		2:��ê��		3:��
	vector<Position> Init_Pos;

};