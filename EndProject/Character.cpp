#include"Game_Manager.h"

void Character::Add_NewCard() 
{
	Player_Card new_Card;
}

void Character::Attack(int value, vector<Ethnicity>& Monster) 
{
	bool find_target = false;
	do {
		char target;
		cin >> target;
		if (target == '0')
		{
			return;
		}
		for (int i = 0; i < Monster.size(); i++)
		{
			for (int j = 0; j < Monster[i].Creature_List.size(); j++)
			{
				if (Monster[i].Creature_List[j].icon == target&&Monster[i].Creature_List[j].active==true)
				{
					int x = Monster[i].Creature_List[j].position.x; int y = Monster[i].Creature_List[j].position.y;
					if (find_by_step(this->position.x, this->position.y, x, y, 1)==true) 
					{
						Monster[i].Creature_List[j].Hp -= value;
						find_target = true;
					}
				}
			}
		}
		if (find_target == false)
			cout << "error target!!!" << endl;
	} while (find_target==false);
}

void Character::Attack(int value, int range, vector<Ethnicity>& Monster)
{

}