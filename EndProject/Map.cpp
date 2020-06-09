#include"Game_Manager.h"

void Map::check_road(int x,int y) 
{
	int in_map = Game_Map[y][x];
	if (Game_Map[y][x] == 4 || Game_Map[y][x] == 1) 
	{
		Game_Map[y][x] = 1;
		if (Game_Map[y - 1][x] == 4 || Game_Map[y - 1][x] == 2 || Game_Map[y - 1][x] == 5 || Game_Map[y - 1][x] == 6)
		{
			this->check_road(x, y - 1);
		}
		if (Game_Map[y + 1][x] == 4 || Game_Map[y + 1][x] == 2 || Game_Map[y + 1][x] == 5 || Game_Map[y + 1][x] == 6)
		{
			this->check_road(x, y + 1);
		}
		if (Game_Map[y][x - 1] == 4 || Game_Map[y][x - 1] == 2 || Game_Map[y][x - 1] == 5 || Game_Map[y][x - 1] == 6)
		{
			this->check_road(x - 1, y);
		}
		if (Game_Map[y][x + 1] == 4 || Game_Map[y][x + 1] == 2 || Game_Map[y][x + 1] == 5 || Game_Map[y][x + 1] == 6)
		{
			this->check_road(x + 1, y);
		}
	}
	else if (Game_Map[y][x] == 5) 
	{
		if (Game_Map[y - 1][x] == 4)
		{
			this->check_road(x, y - 1);
		}
		if (Game_Map[y + 1][x] == 4)
		{
			this->check_road(x, y + 1);
		}
		if (Game_Map[y][x - 1] == 4)
		{
			this->check_road(x - 1, y);
		}
		if (Game_Map[y][x + 1] == 4)
		{
			this->check_road(x + 1, y);
		}
	}
	else if (Game_Map[y][x] == 6) 
	{
		Game_Map[y][x] = 2;
		if (Game_Map[y - 1][x] == 4 || Game_Map[y - 1][x] == 6)
		{
			this->check_road(x, y - 1);
		}
		if (Game_Map[y + 1][x] == 4 || Game_Map[y + 1][x] == 6)
		{
			this->check_road(x, y + 1);
		}
		if (Game_Map[y][x - 1] == 4 || Game_Map[y][x - 1] == 6)
		{
			this->check_road(x - 1, y);
		}
		if (Game_Map[y][x + 1] == 4 || Game_Map[y][x + 1] == 6)
		{
			this->check_road(x + 1, y);
		}
	}
}

void Map::print_Map(vector<Character> player, vector<Ethnicity> Monster)
{
	bool start_point = false;	//辨識初始點*已經列印了
	for (int i = 0; i < High; i++) 
	{
		for (int j = 0; j < Width; j++)
		{
			bool check_Continue = false;
			for (int k = 0; k < player.size(); k++) 
			{
				if ((i == player[k].position.y && i != 0) && (j == player[k].position.x && j != 0)) 
				{

					char output = 'A' + k;
					cout << output;
					check_Continue = true;
				}
			}
			for (int k = 0; k < Monster.size(); k++)
			{
				int list_count = Monster[k].Creature_List.size();
				for (int L=0; L < Monster[k].Creature_List.size(); L++) 
				{
					if (i == Monster[k].Creature_List[L].position.y && j == Monster[k].Creature_List[L].position.x && Game_Map[i][j] == 1)
						cout << Monster[k].Creature_List[L].icon, check_Continue = true;
				}
			}
			if (check_Continue == true)
				continue;
			if (Game_Map[i][j] == 0 || Game_Map[i][j] ==4 || Game_Map[i][j] ==6)
			{
				cout << " ";
			}
			else if (Game_Map[i][j] == 3) 
			{
				cout << "3";
			}
			else if(Game_Map[i][j]==5)
			{
				if (start_point == false) 
				{
					start_point = true;
					cout << "*";
				}
				else 
				{
					cout << "_";
				}
			}
			else 
			{
				cout << Game_Map[i][j];
			}
		}
		cout << endl;
	}
}

void Map::print_Map_UI(vector<Character> player, vector<Ethnicity> Monster) 
{
	//system("cls");
	setPrintPosition(0, 0);
	bool start_point = false;	//辨識初始點*已經列印了
	for (int i = 0; i < High; i++)
	{
		cout << "  ";
		for (int j = 0; j < Width; j++)
		{
			bool check_Continue = false;
			for (int k = 0; k < player.size(); k++)
			{
				if ((i == player[k].position.y && i != 0) && (j == player[k].position.x && j != 0))
				{
					char output = 'A' + k;
					SetColor(10); cout << "p" << output; SetColor(7);
					check_Continue = true;
				}
			}
			for (int k = 0; k < Monster.size(); k++)
			{
				int list_count = Monster[k].Creature_List.size();
				for (int L = 0; L < Monster[k].Creature_List.size(); L++)
				{
					if (i == Monster[k].Creature_List[L].position.y && j == Monster[k].Creature_List[L].position.x && Game_Map[i][j] == 1)
					{
						int num = (Monster[k].Creature_List[L].icon - 'a');
						char output = 'a' + num;
						SetColor(12);
						if (Monster[k].Creature_List[L].mode == 2)
							cout << output << "+";
						else
							cout << output << "-";
						SetColor(7);
						check_Continue = true;
					}
				}
			}
			if (check_Continue == true)
				continue;
			if (Game_Map[i][j] == 0 )
			{
				bool besideRoad = false;
				if (i > 0) 
				{
					if (Game_Map[i - 1][j] == 1 || Game_Map[i - 1][j] == 3 || Game_Map[i - 1][j] == 2 || Game_Map[i - 1][j] == 5)
						besideRoad = true;
				}
				if (i < this->High - 1) 
				{
					if (Game_Map[i + 1][j] == 1 || Game_Map[i + 1][j] == 3 || Game_Map[i + 1][j] == 2 || Game_Map[i + 1][j] == 5)
						besideRoad = true;
				}
				if (j > 0) 
				{
					if (Game_Map[i][j - 1] == 1 || Game_Map[i][j - 1] == 3 || Game_Map[i][j - 1] == 2 || Game_Map[i][j - 1] == 5)
						besideRoad = true;
				}
				if (j < this->Width - 1) 
				{
					if (Game_Map[i][j + 1] == 1 || Game_Map[i][j + 1] == 3 || Game_Map[i][j + 1] == 2 || Game_Map[i][j + 1] == 5)
						besideRoad = true;
				}
				if (besideRoad == true)
					cout << "■";
				else
					cout << "  ";
			}
			else if (Game_Map[i][j] == 4 || Game_Map[i][j] == 6) 
			{
				cout << "  ";
			}
			else if (Game_Map[i][j] == 3)
			{
				cout << "∩";
			}
			else if (Game_Map[i][j] == 5)
			{
				if (start_point == false)
				{
					start_point = true;
					SetColor(160); cout << "＊"; SetColor(7);
				}
				else
				{
					SetColor(170); cout << "＿"; SetColor(7);
				}
			}
			else if(Game_Map[i][j] == 1)
			{
				cout << "□";
			}
			else if(Game_Map[i][j] == 2)
			{
				cout << "≡";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < this->Width + 2; i++)
	{
		setPrintPosition(i * 2, this->High + 2);	cout << "══";
	}
	for (int i = 0; i < this->High + 2; i++)
	{
		setPrintPosition((this->Width + 2) * 2, i);	cout << "∥";
	}
	setPrintPosition(0, 49);
}