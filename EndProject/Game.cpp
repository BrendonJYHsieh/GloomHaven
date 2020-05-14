#include"Game_Manager.h"
/*=============main_function==============*/

//遊戲主程式
void Main_Game(fstream& File_Character,fstream& File_Monster,fstream& File_Map)
{
	vector<Character> Base_Character;	//角色模板，，用於之後創建角色清單時從裡面複製角色資料
	vector<Ethnicity> Monster;			//所有種族
	Map GameMap; //所有Map
	vector<Character> play_Character;	//玩家選擇的角色列表

	read_Character_Data(File_Character, Base_Character);	//Character讀檔
	read_Monster_Data(File_Monster, Monster);			//Monster讀檔
	creat_Character(Base_Character, play_Character);		//創建角色
	read_Map_Data(File_Map, GameMap, Monster,play_Character.size()); //Map讀檔
	//get_All_Base_Character_Data(play_Character);	//檢查Character資料
	//get_All_Base_Monster_Data(Monster);				//檢查Monster資料
	//get_int_Map(GameMap);	//檢查地圖資料
	choose_Start_Position(play_Character,Monster, GameMap);
	//選擇起始位置
	//開始遊戲
}
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character)
{
	int character_count;
	do {
		cout << "請輸入出場角色數量:" << endl;	//輸入角色數量
		cin >> character_count;
		if (character_count < 2 || character_count>4)
			cout << "數量錯誤!" << endl;
	} while (character_count < 2 || character_count>4);
	for (int i = 0; i < character_count; i++)
	{
		int character_number = 0; string character_name;
		cin >> character_name;
		for (int j = 0; j < Base_Character.size(); j++)
		{
			if (character_name == Base_Character[j].Character_name)		//找到模板中的角色
				character_number = j; break;
		}
		Character newCharacter = Base_Character[character_number];		//複製模板中的資料
		for (int j = 0; j < newCharacter.Hand; j++)
		{
			int active_Card_ID;
			do {
				cin >> active_Card_ID;
				if (active_Card_ID < 0 || character_count > newCharacter.Deck.size() - 1)
					cout << "輸入錯誤!" << endl;
			} while (active_Card_ID < 0 || character_count > newCharacter.Deck.size() - 1);
			newCharacter.Deck[active_Card_ID].status = 1;	//設定起始的手牌
		}
		play_Character.push_back(newCharacter);
	}
}
void choose_Start_Position(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map)
{
	Game_Map.check_road(Game_Map.Init_Pos[0].x, Game_Map.Init_Pos[0].y);
	Game_Map.print_Map(play_Character, Monster);
	for (int i = 0; i < play_Character.size(); i++) 
	{

	}
}
//讀檔
void read_Character_Data(fstream& File_Charactervector, vector<Character>& Base_Character)
{
	int Charactor_count,Hp,Hand,Deck; string Charactor_Name;
	/*========讀取幾個角色模板=========*/
	File_Charactervector >> Charactor_count;
	for (int i = 0; i < Charactor_count; i++) 
	{
		/*========讀取角色模板資訊=========*/
		File_Charactervector >> Charactor_Name >> Hp >> Hand >> Deck;
		Character Base_type(Charactor_Name,Hp,Hand);		//新的模板
		/*====讀取角色模板卡片資訊====*/
		for (int j = 0; j < Deck; j++)	//一組共有Deck張卡 
		{
			Player_Card newCard;	//新的卡片
			string per_line,upString,downString;string skill_Name;	int skill_Value;
			File_Charactervector >> newCard.ID >> newCard.Dexterity_Value;		//讀取卡片的ID 和 敏捷值
			getline(File_Charactervector, per_line);		//截下整段能力值
			stringstream interval(per_line);
			getline(interval, upString, '-');getline(interval, downString);		//以"-"為界將整段字串分割成 上部分的技能 和 下部分的技能
			interval.clear(); interval.str("");		//清空stringstream
			interval << upString;
			while (interval >> skill_Name >> skill_Value)	//用"空格"將字串分割成 能力 和 值	
			{
				if (skill_Name == "range") 
				{
					newCard.MovementUp[newCard.MovementUp.size() - 1].range = skill_Value;
				}
				else 
				{
					Card_Property newMovement;
					newMovement.Movement = skill_Name, newMovement.Movement_Value = skill_Value;
					newCard.MovementUp.push_back(newMovement);
				}
			}
			interval.clear(); interval.str("");		//清空stringstream
			interval << downString;
			while (interval >> skill_Name >> skill_Value)	//用"空格"將字串分割成 能力 和 值	
			{
				if (skill_Name == "range")
				{
					newCard.MovementDown[newCard.MovementDown.size() - 1].range = skill_Value;
				}
				else
				{
					Card_Property newMovement;
					newMovement.Movement = skill_Name, newMovement.Movement_Value = skill_Value;
					newCard.MovementDown.push_back(newMovement);
				}
			}
			interval.clear(); interval.str("");
			Base_type.Deck.push_back(newCard);		//將新的卡片加進卡組
		}
		Base_Character.push_back(Base_type);		//將新的角色模板加入模板列表
	}
}
void read_Monster_Data(fstream& File_Monster, vector<Ethnicity>& Base_Monster) 
{
	int Monster_count;
	File_Monster >> Monster_count;		//種族數量
	for (int i = 0; i < Monster_count; i++) 
	{
		string Ethnicity_Name; int hp, atk, range, elite_hp, elite_damage, elite_range;
		File_Monster >> Ethnicity_Name >> hp >> atk >> range >> elite_hp >> elite_damage >> elite_range;
		Ethnicity Base_Type(Ethnicity_Name, hp, atk,range, elite_hp, elite_damage, elite_range);	//宣告怪物模板
		for (int j = 0; j < 6; j++)		//怪物固定六張技能卡
		{
			string per_line, Movement;
			int skill_Value;
			stringstream interval("");
			Creature_Card newCard;	//新的卡片
			File_Monster >> Ethnicity_Name >> newCard.ID >> newCard.Dexterity_Value;	//讀取卡片資料
			getline(File_Monster, per_line);	//截下整段能力值
			interval << per_line;
			while (interval >> Movement)	//以"空格"分割字串
			{
				Card_Property newMovement;
				if (Movement == "move")		//判斷是否為"move指令"
				{
					interval >> newMovement.Move_Command;
				}
				else if (Movement == "d")	//如果是重洗標誌就跳出
				{
					newCard.Shuffle_Mark = false;
					break;
				}
				else if (Movement == "r")	//如果是重洗標誌就跳出
				{
					newCard.Shuffle_Mark = true; 
					break;
				}
				else
				{
					interval >> skill_Value;
					if (Movement == "range") 
					{
						newCard.Movement[newCard.Movement.size() - 1].range = skill_Value;
						continue;
					}
					else 
					{
						newMovement.Movement_Value = skill_Value;
					}
				}
				newMovement.Movement = Movement;
				newCard.Movement.push_back(newMovement);
			}
			interval.clear();		//清空stringstream
			interval.str("");
			Base_Type.Deck.push_back(newCard);
		}
		Base_Monster.push_back(Base_Type);
	}
}
void read_Map_Data(fstream& File_Map, Map& Map, vector<Ethnicity>& Monster,int Player_num)
{
	string File_Name;	
	//cin >> File_Name;	//輸入地圖檔名
	//File_Map.open(File_Name, ios::in);	//正式用
	File_Map.open("map1.txt", ios::in);		//測試用
	File_Map >> Map.High >> Map.Width;
	cout << Map.High << " " << Map.Width << endl;
	vector<int>temp;
	for (int i = 0; i < Map.High; i++) 
	{
		for (int j = 0; j < Map.Width; j++) 
		{
			char temp_num;
			File_Map >> temp_num;
			temp_num -= 48;
			if (temp_num==1) 
			{
				temp_num = 4;
			}
			temp.push_back(temp_num);
		}
		Map.Game_Map.push_back(temp);
		temp.clear();
	}
	int x, y;
	for (int i = 0; i < 4; i++) 
	{
		File_Map >> x >> y;
		Position temp;
		temp.x = x;
		temp.y = y;
		Map.Game_Map[y][x] = 5;
		Map.Init_Pos.push_back(temp);
	}
	File_Map >> Map.Monster_Count;
	for (int i = 0; i < Map.Monster_Count; i++) 
	{
		string Monster_Type;
		Monster_Base Monster_temp;
		Position temp;
		int Status[3];
		int mode;
		File_Map >> Monster_Type;
		for (int j = 0; j < Monster.size(); j++) 
		{
			if (Monster_Type == Monster[j].Ethnicity_Base_value.Name) 
			{
				File_Map >> temp.x >> temp.y >> Status[0] >> Status[1] >> Status[2];
				mode = Status[Player_num - 2];
			}
			else 
				continue;
			if (mode == 0) 
			{
				break;
			}
			else if (mode == 1) 
			{
				Monster_temp.Damage = Monster[j].Ethnicity_Base_value.Damage;
				Monster_temp.Hp = Monster[j].Ethnicity_Base_value.Hp;
				Monster_temp.Name = Monster[j].Ethnicity_Base_value.Name;
				Monster_temp.Range = Monster[j].Ethnicity_Base_value.Range;
				Monster_temp.mode = mode;
				Monster_temp.position = temp;
				Monster_temp.icon = 'a' + i;
				Monster[j].Creature_List.push_back(Monster_temp);
			}
			else 
			{
				Monster_temp.Damage = Monster[j].Ethnicity_Base_value.Elite_Damage;
				Monster_temp.Hp = Monster[j].Ethnicity_Base_value.Elite_Hp;
				Monster_temp.Name = Monster[j].Ethnicity_Base_value.Name;
				Monster_temp.Range = Monster[j].Ethnicity_Base_value.Elite_Range;
				Monster_temp.mode = mode;
				Monster_temp.position = temp;
				Monster_temp.icon = 'a' + i;
				Monster[j].Creature_List.push_back(Monster_temp);
			}
		}	
	}
}

/*==============DEBUG_MODE================*/

void get_All_Base_Character_Data(vector<Character> Base_Player) 
{
	for (int i = 0; i < Base_Player.size(); i++)
	{
		cout << "角色名：" << Base_Player[i].Character_name << "  角色 HP：" << Base_Player[i].Hp << " 角色手牌數：" << Base_Player[i].Hand << endl << "技能卡：" << endl;
		for (int j = 0; j < Base_Player[i].Deck.size(); j++)
		{
			cout << "ID：	" << Base_Player[i].Deck[j].ID << " 狀態: " << Base_Player[i].Deck[j].status << "	敏捷值：	" << Base_Player[i].Deck[j].Dexterity_Value << "	上：";
			for (int k = 0; k < Base_Player[i].Deck[j].MovementUp.size(); k++) 
			{
				cout << Base_Player[i].Deck[j].MovementUp[k].Movement << " " << Base_Player[i].Deck[j].MovementUp[k].Movement_Value << " ";
				if (Base_Player[i].Deck[j].MovementUp[k].Movement == "attack")
					cout << "range " << Base_Player[i].Deck[j].MovementUp[k].range << " ";
			}
			cout << " | 下：";
			for (int k = 0; k < Base_Player[i].Deck[j].MovementDown.size(); k++) 
			{
				cout << Base_Player[i].Deck[j].MovementDown[k].Movement << " " << Base_Player[i].Deck[j].MovementDown[k].Movement_Value << " ";
				if (Base_Player[i].Deck[j].MovementDown[k].Movement == "attack")
					cout <<"range "<< Base_Player[i].Deck[j].MovementDown[k].range << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}
void get_All_Base_Monster_Data(vector<Ethnicity> Base_Monster) 
{
	for (int i = 0; i < Base_Monster.size(); i++) 
	{
		cout << "種族名：" << Base_Monster[i].Ethnicity_Name
			<< " 普通生命：" << Base_Monster[i].Ethnicity_Base_value.Hp
			<< " 普通攻擊：" << Base_Monster[i].Ethnicity_Base_value.Damage
			<< " 普通範圍：" << Base_Monster[i].Ethnicity_Base_value.Range
			<< " 菁英生命：" << Base_Monster[i].Ethnicity_Base_value.Elite_Hp
			<< " 菁英攻擊：" << Base_Monster[i].Ethnicity_Base_value.Elite_Damage
			<< " 菁英範圍：" << Base_Monster[i].Ethnicity_Base_value.Elite_Range << endl << endl;
		for (int j = 0; j < Base_Monster[i].Creature_List.size(); j++)
		{
			cout << "怪物" << Base_Monster[i].Creature_List[j].icon;
			if (Base_Monster[i].Creature_List[j].mode == 2)
				cout << ": 菁英";
			else
				cout << ": 普通";
			cout << " 生命值:" << Base_Monster[i].Creature_List[j].Hp
				<< " 傷害:" << Base_Monster[i].Creature_List[j].Damage
				<< " 範圍:" << Base_Monster[i].Creature_List[j].Range << endl;
		}
		cout << "技能卡：" << endl;
		for (int j = 0; j < 6; j++) 
		{
			cout << "ID：" << Base_Monster[i].Deck[j].ID << " 狀態: " << Base_Monster[i].Deck[j].status << "	敏捷值：" << Base_Monster[i].Deck[j].Dexterity_Value << "	";
			for (int k = 0; k < Base_Monster[i].Deck[j].Movement.size(); k++) 
			{
				cout << Base_Monster[i].Deck[j].Movement[k].Movement<<" ";
				if (Base_Monster[i].Deck[j].Movement[k].Movement == "move") 
				{
					cout << Base_Monster[i].Deck[j].Movement[k].Move_Command << " ";
				}
				else 
				{
					cout << Base_Monster[i].Deck[j].Movement[k].Movement_Value << " ";
					if (Base_Monster[i].Deck[j].Movement[k].Movement == "attack")
						cout << " range " << Base_Monster[i].Deck[j].Movement[k].range << " ";
				}
			}
			cout <<"重洗標誌："<< Base_Monster[i].Deck[j].Shuffle_Mark << endl;
		}
		cout << endl << endl;
	}
}
void get_int_Map(Map Map) 
{
	for (int i = 0; i < Map.High; i++) {
		for (int j = 0; j < Map.Width; j++) {
			cout << Map.Game_Map[i][j];
		}
		cout << endl;
	}
}

/*================UI_MODE=================*/

void Main_Game_UI() 
{
	switch (Project_Start_UI())
	{
	case 0:		//開始遊戲
		break;
	case 1:		//結束遊戲
		system("cls");
		cout << "感謝您的遊玩" << endl << endl;
		system("pause");
		return;
		break;
	default:
		break;
	}
}

//開始介面  回傳值 = 0:開始遊戲 ，回傳值 = 1:結束遊戲
int Project_Start_UI() 
{
	cout << "    GloomHaven   " << endl << endl;
	cout << "=================" << endl;
	cout << "=      "; SetColor(240); cout << "開始"; SetColor(7);cout << "     =" << endl;
	cout << "=      離開     =" << endl;
	cout << "=================" << endl << endl << endl;
	int mode = 0;			//選擇要開始遊戲或是離開
	char keyBoard_Input;	//鍵盤輸入
	while (1) 
	{
		keyBoard_Input = _getch();
		//將反白的文字用原來的顏色蓋過
		if (mode == 1)
		{
			setPrintPosition(7, 4);
			SetColor(7); cout << "離開";
		}
		else if (mode == 0)
		{
			setPrintPosition(7, 3);
			SetColor(7); cout << "開始";
		}
		//根據keyBoard輸入決定要哪一個選項
		switch (keyBoard_Input)
		{
		case 'W':
		case 'w':
			if (mode == 0) 
				mode = 1;
			else 
				mode--;
			break;
		case 'S':
		case 's':
			if (mode == 1)
				mode = 0;
			else
				mode++;
			break;
		}
		//將原本的文字用反白蓋過
		if (mode == 1)
		{
			setPrintPosition(7, 4);
			SetColor(240); cout << "離開";
		}
		else if (mode == 0)
		{
			setPrintPosition(7, 3);
			SetColor(240); cout << "開始";
		}
		setPrintPosition(0, 30);	SetColor(7);	//重置 print點 和 顏色 (若要使用setPrintPosition 或是 SetColor 使用後，請使用這段重置他們的設定)
		if (keyBoard_Input == 13)		//Enter鍵 回傳mode;
			return mode;
	}
}

/*=============Windows.h的function==============*/
void setPrintPosition(int x, int y)		//改變Print的起始位置
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(out, coordinate);
}
void SetColor(int color)				//改變顏色
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}