#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Obstacle //��ê������
{
public:
	Position position;
};

class Door		//������
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
	int Width = 0;	//�e
	int High = 0;	//��
	vector<vector<bool>> Game_Map;	//0:��	1:��
	vector<vector<Door>> Door_List;		//3:��
	vector<vector<Obstacle>> Obstacle_List;	//2:��ê��
};