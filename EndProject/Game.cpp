#include"Game_Manager.h"
/*=============main_function==============*/
//遊戲主程式
void Main_Game(fstream& File_Character,fstream& File_Monster)
{
	vector<Character> Base_Character;	//角色模板，，用於之後創建角色清單時從裡面複製角色資料
	vector<Ethnicity> Base_Monster;		//怪物模板，，用於之後創建怪物清單時從裡面複製怪物資料
	read_Character_Data(File_Character, Base_Character);	//Character讀檔
	read_Monster_Data(File_Monster, Base_Monster);			//Monster讀檔
	//輸入角色數量
	//輸入角色資訊
	//輸入地圖路徑
	//讀取地圖資料
	//選擇起始位置
	//開始遊戲
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
		File_Charactervector.ignore();
		Character Base_type(Charactor_Name,Hp,Hand);		//新的模板
		/*====讀取角色模板卡片資訊====*/
		for (int j = 0; j < Deck; j++)	//一組共有Deck張卡 
		{
			Player_Card newCard;	//新的卡片
			string per_line,upString,downString;string skill_Name;	int skill_Value;
			File_Charactervector >> newCard.ID >> newCard.Dexterity_Value;		//讀取卡片的ID 和 敏捷值
			getline(File_Charactervector, per_line);		//截下整段能力值
			stringstream interval(per_line);
			getline(interval, upString, '-');getline(interval, downString, '-');		//以"-"為界將整段字串分割成 上部分的技能 和 下部分的技能
			interval.clear(); interval.str("");		//清空stringstream
			interval << upString;
			while (interval >> skill_Name >> skill_Value)	//用"空格"將字串分割成 能力 和 值	
			{
				Card_Property newMovement;
				newMovement.Movement = skill_Name, newMovement.Movement_Value = skill_Value;
				newCard.MovementUp.push_back(newMovement);
			}
			interval.clear(); interval.str("");		//清空stringstream
			interval << downString;
			while (interval >> skill_Name >> skill_Value)	//用"空格"將字串分割成 能力 和 值	
			{
				Card_Property newMovement;
				newMovement.Movement = skill_Name, newMovement.Movement_Value = skill_Value;
				newCard.MovementDown.push_back(newMovement);
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
					interval >> newMovement.Movement_Value;
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

/*==============DEBUG_MODE================*/

void get_All_Base_Character_Data(vector<Character> Base_Player) 
{
	for (int i = 0; i < Base_Player.size(); i++)
	{
		cout << "角色名：" << Base_Player[i].Character_name << "  角色 HP：" << Base_Player[i].Hp << " 角色手牌數：" << Base_Player[i].Hand << endl << "技能卡：" << endl;
		for (int j = 0; j < Base_Player[i].Deck.size(); j++)
		{
			cout <<"ID：	"<< Base_Player[i].Deck[j].ID << "	敏捷值：	" << Base_Player[i].Deck[j].Dexterity_Value << "	上：";
			for (int k = 0; k < Base_Player[i].Deck[j].MovementUp.size(); k++)
				cout << Base_Player[i].Deck[j].MovementUp[k].Movement << " " << Base_Player[i].Deck[j].MovementUp[k].Movement_Value << " ";
			cout << " | 下：";
			for (int k = 0; k < Base_Player[i].Deck[j].MovementDown.size(); k++)
				cout << Base_Player[i].Deck[j].MovementDown[k].Movement << " " << Base_Player[i].Deck[j].MovementDown[k].Movement_Value << " ";
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
			<< " 普通生命：" << Base_Monster[i].Creature_List[0].Hp
			<< " 普通攻擊：" << Base_Monster[i].Creature_List[0].Damage
			<< " 普通範圍：" << Base_Monster[i].Creature_List[0].Range
			<< " 菁英生命：" << Base_Monster[i].Creature_List[0].Elite_Hp
			<< " 菁英攻擊：" << Base_Monster[i].Creature_List[0].Elite_Damage
			<< " 菁英範圍：" << Base_Monster[i].Creature_List[0].Elite_Range << endl;
		cout << "技能卡：" << endl;
		for (int j = 0; j < 6; j++) 
		{
			cout << "ID：" << Base_Monster[i].Deck[j].ID << "	敏捷值：" << Base_Monster[i].Deck[j].Dexterity_Value << "	";
			for (int k = 0; k < Base_Monster[i].Deck[j].Movement.size(); k++) 
			{
				cout << Base_Monster[i].Deck[j].Movement[k].Movement<<" ";
				if (Base_Monster[i].Deck[j].Movement[k].Movement == "move")
					cout << Base_Monster[i].Deck[j].Movement[k].Move_Command << " ";
				else
					cout << Base_Monster[i].Deck[j].Movement[k].Movement_Value << " ";
			}
			cout <<"重洗標誌："<< Base_Monster[i].Deck[j].Shuffle_Mark << endl;
		}
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