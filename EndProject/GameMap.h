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
	int Width = 0;	//寬
	int High = 0;	//高
	vector<vector<int>> Game_Map;	//0:牆	1:路		2:障礙物		3:門
	vector<Position> Init_Pos;

};