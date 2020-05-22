#include"Game_Manager.h"

void Character::Add_NewCard() 
{
	Player_Card new_Card;
}

bool Character::Attack(int value, vector<Ethnicity>& Monster) 
{
	do {
		char target;
		cin >> target;
		if (target == '0')
		{
			return false;
		}
		for (int i = 0; i < Monster.size(); i++)
		{
			for (int j = 0; j < Monster[i].Creature_List.size(); j++)
			{
				if (Monster[i].Creature_List[j].icon == target && Monster[i].Creature_List[j].active==true)
				{
					int x = Monster[i].Creature_List[j].position.x; int y = Monster[i].Creature_List[j].position.y;
					if (find_by_step(this->position.x, this->position.y, x, y, 1)==true) 
					{
						cout << this->ID << " attack " << target << " " << value << " damage, " << Monster[i].Creature_List[j].icon << " shield " << Monster[i].Creature_List[j].Shield << ", ";
						Monster[i].Creature_List[j].Hp -= (value-Monster[i].Creature_List[j].Shield);
						Monster[i].Creature_List[j].Shield = 0;
						cout <<Monster[i].Creature_List[j].icon<<" remain "<< Monster[i].Creature_List[j].Hp <<" hp"<< endl;
						if (Monster[i].Creature_List[j].Hp <= 0) 
						{
							cout << Monster[i].Creature_List[j].icon << " is killed!!" << endl;
							Monster[i].Creature_List.erase(Monster[i].Creature_List.begin() + j);
							return true;
						}
						return false;
					}
				}
			}
		}
		cout << "error target!!!" << endl;
	} while (1);
}
//
//void Character::Attack(int value, int range, vector<Ethnicity>& Monster)
//{
//
//}