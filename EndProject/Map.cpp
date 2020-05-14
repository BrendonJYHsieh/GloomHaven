#include"Game_Manager.h"

void Map::check_road(int x,int y,int dir) 
{
	if (Game_Map[y][x] == 0 || Game_Map[y][x] == 3 || Game_Map[y][x] == 2)
		return;
	Game_Map[y][x] == 1;
	switch (dir) 
	{
	case 0:
		this->check_road(x, y - 1, 1); this->check_road(x, y + 1, 2);this->check_road(x - 1, y, 3); this->check_road(x + 1, y, 4);
		break;
	case 1:
		this->check_road(x, y - 1, 1); this->check_road(x - 1, y, 3); this->check_road(x + 1, y, 4);
		break;
	case 2:
		this->check_road(x, y + 1, 2);this->check_road(x - 1, y, 3); this->check_road(x + 1, y, 4);
		break;
	case 3:
		this->check_road(x, y - 1, 1); this->check_road(x, y + 1, 2); this->check_road(x - 1, y, 3);
		break;
	case 4:
		this->check_road(x, y - 1, 1); this->check_road(x, y + 1, 2); this->check_road(x + 1, y, 4);
		break;
	}
}

void Map::print_Map(vector<Character> player, vector<Ethnicity> Monster)
{
	for (int i = 0; i < High; i++) 
	{
		for (int j = 0; j < Width; j++)
		{
			bool check_Continue = false;
			for (int k = 0; k < player.size(); k++) 
			{
				if (i == player[k].position.y && j == player[k].position.x)
					cout << k + 'A'; check_Continue = true;
			}
			for (int k = 0; k < Monster.size(); k++)
			{
				for (int L; L < Monster[k].Creature_List.size(); L++) 
				{
					if (i == Monster[k].Creature_List[L].position.y && j == Monster[k].Creature_List[L].position.x)
						cout << Monster[k].Creature_List[L].icon; check_Continue = true;
				}
			}
			if (check_Continue == true)
				continue;
			if (Game_Map[i][j] == 0 || Game_Map[i][j] == 3 || Game_Map[i][j] ==4)
			{
				cout << " ";
			}
			else if(Game_Map[i][j]==5)
			{
				cout << "_";
			}
			else 
			{
				cout << Game_Map[i][j];
			}
		}
		cout << endl;
	}
}