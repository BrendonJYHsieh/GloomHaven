#include"Game_Manager.h"

void Character::Add_NewCard() 
{
	Player_Card new_Card;
}

bool Character::Attack(int value, vector<Ethnicity>& Monster) 
{
	do {
		cout << "請輸入攻擊目標(距離:1):";
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

bool Character::Attack(int value, int range, vector<Ethnicity>& Monster, Map map)
{
	do {
		cout << "請輸入攻擊目標(距離:" << range << "):";
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
				if (Monster[i].Creature_List[j].icon == target && Monster[i].Creature_List[j].active == true)
				{
					int x = Monster[i].Creature_List[j].position.x; int y = Monster[i].Creature_List[j].position.y;
					if (find_by_step(this->position.x, this->position.y, x, y, range) == true && vision_search(this->position, Monster[i].Creature_List[j].position,map)==false)
					{
						cout << this->ID << " attack " << target << " " << value << " damage, " << Monster[i].Creature_List[j].icon << " shield " << Monster[i].Creature_List[j].Shield << ", ";
						Monster[i].Creature_List[j].Hp -= (value - Monster[i].Creature_List[j].Shield);
						cout << Monster[i].Creature_List[j].icon << " remain " << Monster[i].Creature_List[j].Hp << " hp" << endl;
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

bool Character::Attack_UI(int value, int range, vector<Ethnicity>& Monster, Map map ,int printPoint, vector<string>& game_Massage_string)
{
	vector<char> target;
	string output_log;
	for (int i = 0; i < Monster.size(); i++) 
	{
		for (int j = 0; j < Monster[i].Creature_List.size(); j++) 
		{
			if (Monster[i].Creature_List[j].active == true && find_by_step(this->position.x, this->position.y, Monster[i].Creature_List[j].position.x, Monster[i].Creature_List[j].position.y, range) == true && vision_search(this->position, Monster[i].Creature_List[j].position, map) == false) 
			{
				target.push_back(Monster[i].Creature_List[j].icon);
			}
		}
	}
	if (target.size() > 0)
	{
		setPrintPosition(0, printPoint + 5);
		cout << "====選擇攻擊對象====" << endl;
		for (int i = 0; i < target.size(); i++) 
		{
			setPrintPosition(0, printPoint + 7 + i); cout << "=   " << target[i]; setPrintPosition(13, printPoint + 7 + i); cout << "=";
		}
		setPrintPosition(0, printPoint + 7 + target.size()); cout << "=   放棄攻擊 =";
		target.push_back('0');
		bool chooseComplete = false;
		int nowchoose = 0, choose = 1;
		while (chooseComplete == false) 
		{
			if (nowchoose != choose) 
			{
				setPrintPosition(1, printPoint + 7 + choose); cout << "  ";
				setPrintPosition(1, printPoint + 7 + nowchoose); cout << "→";
				choose = nowchoose;
				setPrintPosition(0, 49);
			}
			else 
			{
				switch (keyBoard(_getch())) 
				{
				case 'w':
					nowchoose--;
					if (nowchoose < 0)
						nowchoose = target.size() - 1;
					break;
				case 's':
					nowchoose++;
					if (nowchoose == target.size())
						nowchoose = 0;
					break;
				case 13:
					chooseComplete = true;
					break;
				}
			}
		}
		if (target[nowchoose] == '0') 
		{
			setPrintPosition(0, printPoint + 5);
			for (int i = 0; i < target.size() + 2; i++)
			{
				cout << "                                                                                                                         " << endl;
			}
			setPrintPosition(0, printPoint + 5);
			output_log.push_back(this->ID);
			output_log += "放棄攻擊";
			cout << "====" << output_log << "====" << endl << endl;
		}
		else 
		{
			for (int i = 0; i < Monster.size(); i++)
			{
				for (int j = 0; j < Monster[i].Creature_List.size(); j++)
				{
					if (Monster[i].Creature_List[j].icon == target[nowchoose]) 
					{
						output_log.push_back(this->ID);
						output_log += "攻擊"; output_log.push_back(target[nowchoose]); output_log += "(護甲：" + to_string(Monster[i].Creature_List[j].Shield) + ")\t"+to_string(value)+"點傷害，";
						Monster[i].Creature_List[j].Hp -= (value - Monster[i].Creature_List[j].Shield);
						if (Monster[i].Creature_List[j].Hp <= 0)
						{
							output_log.push_back(target[nowchoose]); output_log += "死亡";
							setPrintPosition((Monster[i].Creature_List[j].position.x + 1) * 2, Monster[i].Creature_List[j].position.y); cout << "□";
							Monster[i].Creature_List.erase(Monster[i].Creature_List.begin() + j);
						}
						else 
						{
							output_log.push_back(target[nowchoose]); output_log += "剩餘" + to_string(Monster[i].Creature_List[j].Hp) + "點生命";
						}
						setPrintPosition(0, printPoint + 5);
						for (int i = 0; i < target.size() + 2; i++)
						{
							cout << "                                                                                                                         " << endl;
						}
						setPrintPosition(0, printPoint + 5);
						cout << "====" << output_log << "====" << endl << endl;
						break;
					}
				}
			}
		}
		system("pause");
		setPrintPosition(0, 49);
	}
	else 
	{
		setPrintPosition(0, printPoint + 5);
		cout << "====沒有可攻擊對像====" << endl << endl;
		output_log.push_back(this->ID);
		output_log += "放棄攻擊";
		system("pause");
	}
	game_Massage_string.push_back(output_log);
	return true;
}

void Character::long_Rest() 
{
	this->Skill_heal(2);
	cout << this->ID << " heal 2, now hp is " << this->Hp << endl;
	bool remove_Complete = false;
	do 
	{
		int remove;
		cin >> remove;
		if (this->Deck[remove].status == 2) 
		{
			this->Deck[remove].status = 0;
			cout << "remove card: " << remove << endl;
			for (int i = 0; i < this->Deck.size(); i++) 
			{
				if (this->Deck[i].status == 2)
					this->Deck[i].status = 1;
			}
			remove_Complete = true;
		}
	} while (remove_Complete == false);
}