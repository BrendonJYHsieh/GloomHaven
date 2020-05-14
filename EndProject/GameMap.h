#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Obstacle //障礙物物件
{
public:
	Position position;
};

class Door		//門物件
{
public:
	Position position;
};

class Map : public Obstacle,public Door
{
public:
	Map(){}
	Map(int Width, int High){}
	/*===fuction===*/
	
	/*====value====*/
	int Width = 0;	//寬
	int High = 0;	//高
	vector<vector<bool>> Game_Map;	//0:牆	1:路
	vector<vector<Door>> Door_List;		//3:門
	vector<vector<Obstacle>> Obstacle_List;	//2:障礙物
};