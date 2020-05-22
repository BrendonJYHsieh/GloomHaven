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
	while (1) 
	{
		creat_Character(Base_Character, play_Character);		//創建角色
		read_Map_Data(File_Map, GameMap, Monster, play_Character.size()); //Map讀檔
		//get_All_Base_Character_Data(play_Character);	//檢查Character資料
		//get_All_Base_Monster_Data(Monster);				//檢查Monster資料
		//get_int_Map(GameMap);	//檢查地圖資料
		choose_Start_Position(play_Character, Monster, GameMap);	//選擇起始位置
		check_Monsters_Active(Monster, GameMap);	//檢查怪物狀態
		//開始遊戲主流程
		main_Battle(play_Character, Monster, GameMap);
		play_Character.clear();
		for (int i = 0; i < Monster.size(); i++) 
		{
			Monster[i].Creature_List.clear();
		}
		GameMap.Game_Map.clear();
		GameMap.Init_Pos.clear();
		char again;
		cout << "是否選擇再遊玩一次？(y/n)";
		std::cin >> again;
		if (again == 'n')
			break;
	}
}
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character)
{
	int character_count;
	do {
		cout << "請輸入出場角色數量:" << endl;	//輸入角色數量
		std::cin >> character_count;
		if (character_count < 2 || character_count>4)
			cout << "數量錯誤!" << endl;
	} while (character_count < 2 || character_count>4);
	for (int i = 0; i < character_count; i++)
	{
		int character_number = 0; string character_name;
		std::cin >> character_name;
		for (int j = 0; j < Base_Character.size(); j++)
		{
			if (character_name == Base_Character[j].Character_name)		//找到模板中的角色
			{
				character_number = j;
				break;
			}
		}
		Character newCharacter = Base_Character[character_number];		//複製模板中的資料
		newCharacter.ID = 'A' + i;
		for (int j = 0; j < newCharacter.Hand; j++)
		{
			int active_Card_ID;
			do {
				std::cin >> active_Card_ID;
				if (active_Card_ID < 0 || character_count > newCharacter.Deck.size() - 1)
					cout << "輸入錯誤!" << endl;
			} while (active_Card_ID < 0 || character_count > newCharacter.Deck.size() - 1);
			newCharacter.Deck[active_Card_ID].status = 1;	//設定起始的手牌
		}
		play_Character.push_back(newCharacter);
	}
}
bool compare(Position a,Position b) 
{
	if (a.y > b.y)
		return false;
	else if (a.y == b.y && a.x > b.x)
		return false;
	else
		return true;
}
void choose_Start_Position(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map)
{
	sort(Game_Map.Init_Pos.begin(), Game_Map.Init_Pos.end(),compare);
	for (int i = 0; i < Game_Map.Init_Pos.size(); i++) 
	{
		Game_Map.check_road(Game_Map.Init_Pos[i].x, Game_Map.Init_Pos[i].y);
	}
	Game_Map.print_Map(play_Character, Monster);
	//cin.ignore();
	for (int i = 0; i < play_Character.size(); i++) 
	{
		string position_input;
		Position start_point;
		start_point = Game_Map.Init_Pos[0];
		//此段似乎有bug引起輸入錯誤 而且不知道發生原因 我之後再測看看 下次測試幫我看看這裡cin會不會跳過
		std::cin >> position_input;
		for (int j = 0; j < position_input.size(); j++)
		{
			switch (position_input[j])
			{
			case'w':
			case 'W':
				if (Game_Map.Game_Map[start_point.y - 1][start_point.x] == 5) 
				{
					start_point.y--;
				}
				break;
			case's':
			case 'S':
				if (Game_Map.Game_Map[start_point.y + 1][start_point.x] == 5)
				{
					start_point.y++;
				}
				break;
			case'a':
			case 'A':
				if (Game_Map.Game_Map[start_point.y][start_point.x - 1] == 5)
				{
					start_point.x--;
				}
				break;
			case'd':
			case 'D':
				if (Game_Map.Game_Map[start_point.y][start_point.x + 1] == 5)
				{
					start_point.x++;
				}
				break;
			case'e':
			case 'E':
				break;
			default:
				break;
			}
			//if (position_input[j] == 13)	//enter鍵結束
			//	break;
		}
		play_Character[i].position.y = start_point.y;
		play_Character[i].position.x = start_point.x;
		Game_Map.Game_Map[start_point.y][start_point.x] = 1;
		for (int j = 0; j < Game_Map.Init_Pos.size(); j++) 
		{
			if (Game_Map.Init_Pos[j].x == start_point.x && Game_Map.Init_Pos[j].y == start_point.y) 
			{
				Game_Map.Init_Pos.erase(Game_Map.Init_Pos.begin() + j);
			}
		}
		if (i == play_Character.size() - 1)
			break;
		Game_Map.print_Map(play_Character, Monster);
	}
	for (int i = 0; i < Game_Map.High; i++) 
	{
		for (int j = 0; j < Game_Map.Width; j++)
		{
			if (Game_Map.Game_Map[i][j]==5) 
			{
				Game_Map.Game_Map[i][j] = 1;
			}
			
		}
	}
	Game_Map.print_Map(play_Character, Monster);
}
void main_Battle(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map) 
{
	bool* already_played = nullptr;
	srand(time(NULL));
	int round = 1;
	while(1)	//結束遊戲條件 1.角色數量 怪物數量 門數量
	{
		cout << "round " << round << ":" << endl;
		already_played = new bool[play_Character.size()];
		for (int i = 0; i < play_Character.size(); i++) {
			already_played[i] = false;
			//cout << already_played[i] << endl;
		}
		//玩家角色準備
		do {
			char who;
			std::cin >> who;
			for (int i = 0; i < play_Character.size(); i++) {
				if (who == i + 'A') {
					int Discard_num = calculate_Discard(play_Character[i]); //計算棄牌數
					string command; // 若為-1 check時為指令 其他則為 出牌的第一張
					std::cin >> command;
					if (command == "-1"&&Discard_num>=2&& !already_played[i]) {
						play_Character[i].Command[0] = -1;
						play_Character[i].Rest = true;
						already_played[i] = true;
					}
					else if (command=="check") {
						check(play_Character[i]);
					}
					else if(IsPlayHandCard(play_Character[i],command) && !already_played[i]) {
						int card2;
						std::cin >> card2;
						if (IsCardInHand(play_Character[i], card2)) {
							for (int j = 0; j < 2; j++) 
							{
								for (int k = 0; k < play_Character[i].Deck.size(); k++) 
								{
									if (play_Character[i].Deck[k].ID == command[0] - '0')
										play_Character[i].Command[0] = play_Character[i].Deck[k].ID;
									else if(play_Character[i].Deck[k].ID == card2)
										play_Character[i].Command[1] = play_Character[i].Deck[k].ID;
								}
							}
							already_played[i] = true;
						}
						else {
							break;
						}
					}
					else {
						cout << "Wrong Command" << endl;
					}
					break;
				}
			}
		} while (check_player_done(already_played, play_Character.size()));
		delete[] already_played;
		//怪物準備
		for (int i = 0; i < Monster.size(); i++)	//第i個種族
		{
			bool all_deactivate = true;
			for (int j = 0; j < Monster[i].Creature_List.size(); j++) 
			{
				if (Monster[i].Creature_List[j].active == true)
					all_deactivate = false;
			}
			if (all_deactivate == true) 
			{
				Monster[i].Command = -1;
				continue;
			}
			bool finished = false;
			do
			{
				int choose = rand() % (Monster[i].Deck.size());
				if (Monster[i].Deck[choose].status == 0)	//確認是否在牌組中
				{
					Monster[i].Deck[choose].status = 2;	//改成出牌中
					Monster[i].Command = choose;
					finished = true;		//結束選擇
				}
			} while (finished == false);		//結束選擇即跳出此迴圈
		}
		//check_all_dex(play_Character,Monster);	//檢查敏捷值
		//判斷出手順序
		vector<char> attack_Sort;	//以敏捷值排序的攻擊順序
		//先排角色
		attack_Sort.push_back(play_Character[0].ID);	//將角色A加入排序
		for (int i = 1; i < play_Character.size(); i++) 
		{
			for (int j = 0; j < attack_Sort.size(); j++) 
			{
				if (play_Character[i].Deck[play_Character[i].Command[0]].Dexterity_Value < get_Character_Dex(play_Character, attack_Sort[j], 0))
				{
					attack_Sort.insert(attack_Sort.begin() + j, play_Character[i].ID);
					break;
				}
				else if (play_Character[i].Deck[play_Character[i].Command[0]].Dexterity_Value == get_Character_Dex(play_Character, attack_Sort[j], 0))
				{
					if (play_Character[i].Deck[play_Character[i].Command[1]].Dexterity_Value < get_Character_Dex(play_Character, attack_Sort[j], 1))
					{
						attack_Sort.insert(attack_Sort.begin() + j, play_Character[i].ID);
						break;
					}
					else if (j + 1 == attack_Sort.size()) //第二個敏捷值仍然相同或較大，由於是照角色字母順序加進排序，所以直接跳到下一位判斷，如果此位是最後一位，則直接將角色加到排序最後一位
					{
						attack_Sort.push_back(play_Character[i].ID);
						break;
					}
					else {
						continue;
					}
				}
				else if (j + 1 == attack_Sort.size()) //排序中的最後一位
				{
					attack_Sort.push_back(play_Character[i].ID);
					break;
				}
				else 
				{

				}
			}
		}
		//再排怪物		由於怪物是以種族來排，所以序列裡我將怪物的代號以('a'+i代替)，到時候寫攻擊時要稍微注意
		for (int i = 0; i < Monster.size(); i++) 
		{
			for (int k = 0; k < Monster[i].Creature_List.size(); k++) 
			{
				if (Monster[i].Creature_List[k].active == false)
					continue;
				for (int j = 0; j < attack_Sort.size(); j++)
				{
					if (attack_Sort[j] >= 'A' && attack_Sort[j] <= 'Z') //判斷是否是玩家角色
					{
						if (Monster[i].Deck[Monster[i].Command].Dexterity_Value < get_Character_Dex(play_Character, attack_Sort[j], 0))
						{
							attack_Sort.insert(attack_Sort.begin() + j,Monster[i].Creature_List[k].icon);
							break;
						}
					}
					else
					{
						if (Monster[i].Deck[Monster[i].Command].Dexterity_Value < get_Monster_Dex( Monster, attack_Sort[j]))
						{
							attack_Sort.insert(attack_Sort.begin() + j, Monster[i].Creature_List[k].icon);
							break;
						}
						else if (Monster[i].Deck[Monster[i].Command].Dexterity_Value == get_Monster_Dex(Monster, attack_Sort[j]) && Monster[i].Creature_List[k].icon < attack_Sort[j])
						{
							attack_Sort.insert(attack_Sort.begin() + j, Monster[i].Creature_List[k].icon);
							break;
						}
					}
					if (j + 1 == attack_Sort.size())
					{
						attack_Sort.push_back(Monster[i].Creature_List[k].icon);
						break;
					}
				}
			}
		}
		//檢查排序
		show_AttackList(attack_Sort, play_Character, Monster);
		/*for (int i = 0; i < attack_Sort.size(); i++)
		{
			cout << attack_Sort[i] << " ";
		}cout << endl;*/

		//動作執行
		for (int i = 0; i < attack_Sort.size(); i++) 
		{
			if (attack_Sort[i] <= 'Z' && attack_Sort[i] >= 'A')		//角色行動
			{
				players_round(play_Character,play_Character[attack_Sort[i] - 'A'], Monster, Game_Map);
			}
			else //怪物行動
			{
				for (int j = 0; j < Monster.size(); j++) 
				{
					for (int k = 0; k < Monster[j].Creature_List.size(); k++)
					{
						if (attack_Sort[i] == Monster[j].Creature_List[k].icon) 
						{
							monsters_round(play_Character, Monster[j], Monster[j].Creature_List[k], Game_Map);
							break;
						}
					}
				}
			}
		}
		//回合結算

		round++;
	}
}
//行動
void players_round(vector<Character>& play_Character,Character& Character, vector<Ethnicity>& Monster, Map& Game_Map) 
{
	if (Character.Rest == false)
	{
		cout << Character.ID << "'s rturn: card " << Character.Command[0] << " " << Character.Command[1] << endl;
		int card_num; char UpOrDown;
		cin >> card_num >> UpOrDown;
		if (Character.Deck[card_num].status == 4)
		{
			if (UpOrDown == 'u')
			{
				for (int j = 0; j < Character.Deck[card_num].MovementUp.size(); j++)
				{
					if (Character.Deck[card_num].MovementUp[j].Movement == "attack") {
						if (Character.Deck[card_num].MovementUp[j].range == 0) 
						{
							if(Character.Attack(Character.Deck[card_num].MovementUp[j].Movement_Value, Monster)==true)
								Game_Map.print_Map(play_Character, Monster);
						}
						else 
						{

						}
					}
					else if (Character.Deck[card_num].MovementUp[j].Movement == "shield") {
						Character.Skill_shield(Character.Deck[card_num].MovementUp[j].Movement_Value);
						cout << "shield" << endl;
					}
					else if (Character.Deck[card_num].MovementUp[j].Movement == "") {
						Character.Skill_heal(Character.Deck[card_num].MovementUp[j].Movement_Value);
						cout << "heal" << endl;
					}
					else if (Character.Deck[card_num].MovementUp[j].Movement == "") {
						character_move(Character, Character.Deck[card_num].MovementUp[j].Movement_Value, Game_Map, play_Character, Monster);
						Game_Map.print_Map(play_Character, Monster);
						cout << "move" << endl;
					}
				}
				for (int j = 0; j < Character.Deck.size(); j++) {
					if (Character.Deck[j].status == 4 && Character.Deck[j].ID != card_num) {
						card_num = Character.Deck[j].ID;
						break;
					}
				}
				for (int j = 0; j < Character.Deck[card_num].MovementDown.size(); j++)
				{
					if (Character.Deck[card_num].MovementDown[j].Movement == "attack") {
						if (Character.Deck[card_num].MovementDown[j].range == 0)
						{
							if (Character.Attack(Character.Deck[card_num].MovementDown[j].Movement_Value, Monster) == true)
								Game_Map.print_Map(play_Character, Monster);
						}
						else
						{

						}
					}
					else if (Character.Deck[card_num].MovementDown[j].Movement == "shield") {
						Character.Skill_shield(Character.Deck[card_num].MovementDown[j].Movement_Value);
						cout << "shield" << endl;
					}
					else if (Character.Deck[card_num].MovementDown[j].Movement == "heal") {
						Character.Skill_heal(Character.Deck[card_num].MovementDown[j].Movement_Value);
						cout << "heal" << endl;
					}
					else if (Character.Deck[card_num].MovementDown[j].Movement == "move") {
						character_move(Character, Character.Deck[card_num].MovementDown[j].Movement_Value, Game_Map,play_Character, Monster);
						Game_Map.print_Map(play_Character, Monster);
						cout << "move" << endl;
					}
				}
			}
			else
			{
				for (int j = 0; j < Character.Deck[card_num].MovementDown.size(); j++)
				{
					if (Character.Deck[card_num].MovementDown[j].Movement == "attack") {
						if (Character.Deck[card_num].MovementDown[j].range == 0)
						{
							if (Character.Attack(Character.Deck[card_num].MovementDown[j].Movement_Value, Monster) == true)
								Game_Map.print_Map(play_Character, Monster);
						}
						else
						{

						}
					}
					else if (Character.Deck[card_num].MovementDown[j].Movement == "shield") {
						Character.Skill_shield(Character.Deck[card_num].MovementDown[j].Movement_Value);
						cout << "shield" << endl;
					}
					else if (Character.Deck[card_num].MovementDown[j].Movement == "heal") {
						Character.Skill_heal(Character.Deck[card_num].MovementDown[j].Movement_Value);
						cout << "heal" << endl;
					}
					else if (Character.Deck[card_num].MovementDown[j].Movement == "move") {
						character_move(Character, Character.Deck[card_num].MovementDown[j].Movement_Value, Game_Map, play_Character, Monster);
						Game_Map.print_Map(play_Character, Monster);
						cout << "move" << endl;
					}
				}
				for (int j = 0; j < Character.Deck.size(); j++) {
					if (Character.Deck[j].status == 4 && Character.Deck[j].ID != card_num) {
						card_num = Character.Deck[j].ID;
						break;
					}
				}
				for (int j = 0; j < Character.Deck[card_num].MovementUp.size(); j++)
				{
					if (Character.Deck[card_num].MovementUp[j].Movement == "attack") {
						if (Character.Deck[card_num].MovementUp[j].range == 0)
						{
							if (Character.Attack(Character.Deck[card_num].MovementUp[j].Movement_Value, Monster) == true)
								Game_Map.print_Map(play_Character, Monster);
						}
						else
						{

						}
					}
					else if (Character.Deck[card_num].MovementUp[j].Movement == "shield") {
						Character.Skill_shield(Character.Deck[card_num].MovementUp[j].Movement_Value);
						cout << "shield" << endl;
					}
					else if (Character.Deck[card_num].MovementUp[j].Movement == "") {
						Character.Skill_heal(Character.Deck[card_num].MovementUp[j].Movement_Value);
						cout << "heal" << endl;
					}
					else if (Character.Deck[card_num].MovementUp[j].Movement == "") {
						character_move(Character, Character.Deck[card_num].MovementUp[j].Movement_Value, Game_Map, play_Character, Monster);
						Game_Map.print_Map(play_Character, Monster);
						cout << "move" << endl;
					}
				}
			}
			Character.Deck[card_num].status = 2;
		}
	}
	else
	{
		cout << Character.ID << "'turn: card -1" << endl;
	}
}
void monsters_round(vector<Character>& play_Character, Ethnicity& Monster_Ethnicity, Monster_Base& monster, Map Game_Map) 
{
	cout << monster.icon << "'s round : ";
	for (int i = 0; i < Monster_Ethnicity.Deck.size(); i++)
	{
		if (Monster_Ethnicity.Deck[i].status == 2) 
		{
			for (int j = 0; j < Monster_Ethnicity.Deck[i].Movement.size(); j++) 
			{
				if (Monster_Ethnicity.Deck[i].Movement[j].Movement == "attack") {
					cout << "attack" << endl;
				}
				else if (Monster_Ethnicity.Deck[i].Movement[j].Movement == "shield") {
					cout << "shield" << endl;
				}
				else if (Monster_Ethnicity.Deck[i].Movement[j].Movement == "heal") {
					cout << "heal" << endl;
				}
				else if (Monster_Ethnicity.Deck[i].Movement[j].Movement == "move") {
					cout << "move" << endl;
				}
			}
			break;
		}
	}
}
void character_move(Character& C, int step, Map& Game_Map, vector<Character> play_Character, vector<Ethnicity> Monster) {
	string position_input;
	Position start = C.position;
	bool wrong = false;
	do{
		wrong = false;
		C.position = start;
		std::cin >> position_input;
		if (position_input.size() <= step) 
		{
			for (int i = 0; i < position_input.size(); i++) 
			{
				switch (position_input[i])
				{
				case'w':
				case 'W':
					if (move_Error(C.position.x,C.position.y-1,play_Character,Monster,Game_Map)==true)
					{
						C.position.y--;
					}
					else
						wrong = true;
					break;
				case's':
				case 'S':
					if (move_Error(C.position.x, C.position.y+1, play_Character, Monster, Game_Map) == true)
					{
						C.position.y++;
					}
					else
						wrong = true;
					break;
				case'a':
				case 'A':
					if (move_Error(C.position.x-1, C.position.y, play_Character, Monster, Game_Map) == true)
					{
						C.position.x--;
					}
					else
						wrong = true;
					break;
				case'd':
				case 'D':
					if (move_Error(C.position.x+1, C.position.y, play_Character, Monster, Game_Map) == true)
					{
						C.position.x++;
					}
					else
						wrong = true;
					break;
				case'e':
				case 'E':
					break;
				}
				if (i == position_input.size() - 1) 
				{
					for (int j = 0; j < play_Character.size(); j++) 
					{
						if (play_Character[j].position.x == C.position.x && play_Character[j].position.y == C.position.y) 
						{
							wrong = true;
						}
					}
				}
				if (wrong) {
					cout << "Error Move!" << endl;
					break;
				}
			}
		}
		else {
			cout << "Error Move!" << endl;
			wrong = true;
		}
	} while (wrong == true);
}
bool vision_search(Position p1, Position p2, Map Map) {
	int xvalue, yvalue;
	if (p1.x == p2.x) {
		xvalue = p1.x;
		if (p1.y > p2.y) {
			for (int i = p1.y; i >= p2.y; i--) {
				yvalue = i;
				if (Map.Game_Map[yvalue][xvalue] == 0) {
					return true;
				}
			}
		}
		else {
			for (int i = p1.y; i <= p2.y; i++) {
				yvalue = i;
				if (Map.Game_Map[yvalue][xvalue] == 0) {
					return true;
				}
			}
		}
	}
	//斜率為正 左上到右下
	else if (p1.x < p2.x&& p1.y <= p2.y) {
		float tan = (p1.y - p2.y - 1) / (p1.x - p2.x - 1);
		cout << tan << endl;
		for (float i = p1.x; i < p2.x + 1; i += 0.0001) {
			xvalue = floor(i);
			yvalue = floor(i * tan) + p1.y;
			if (Map.Game_Map[yvalue][xvalue] == 0) {
				return true;
			}
		}
	}
	//斜率為正 右下到左上
	else if (p1.x > p2.x && p1.y >= p2.y) {
		float tan = (p1.y - p2.y - 1) / (p1.x - p2.x - 1);
		cout << tan << endl;
		for (float i = p1.x; i > p2.x; i -= 0.0001) {
			xvalue = floor(i);
			yvalue = floor(i * tan);
			if (Map.Game_Map[yvalue][xvalue] == 0) {
				return true;
			}
		}
	}
	//斜率為負 左下到右上
	else if (p1.x < p2.x&& p1.y >= p2.y) {
		float tan = (p1.y - p2.y + 1) / (p1.x - p2.x - 1) * -1;
		cout << tan << endl;
		for (float i = p1.x; i < p2.x + 1; i += 0.0001) {
			int xvalue = floor(i);
			int yvalue = p1.y - floor(i * tan);
			if (Map.Game_Map[yvalue][xvalue] == 0) {
				return true;
			}
		}
	}
	//斜率為負 右上到左下
	else if (p1.x > p2.x && p1.y <= p2.y) {
		float tan = (p1.y - p2.y + 1) / (p1.x - p2.x - 1) * -1;
		cout << tan << endl;
		for (float i = p1.x; i > p2.x; i -= 0.0001) {
			xvalue = floor(i);
			yvalue = p2.y - floor(i * tan);
			if (Map.Game_Map[yvalue][xvalue] == 0) {
				return true;
			}
		}
	}
	return false;
}
//計算角色棄牌堆的數量
int calculate_Discard(Character C) {
	int num = 0;
	for (int i = 0; i < C.Deck.size(); i++) {
		if (C.Deck[i].status == 2) {
			num++;
		}
	}
	return num;
}
//判斷是否打手牌
bool IsPlayHandCard(Character &C,string command ) {
	if (command.size() > 1) {
		return false;
	}
	else if (command.size() == 1 && command[0] >= 48 && command[0] <= 57) {
		for (int i = 0; i < C.Deck.size(); i++) {
			if (C.Deck[i].ID == (command[0] - '0')) {
				C.Deck[i].status = 4;
				return true;
			}
		}
		return false;
	}
	else {
		return false;
	}
}
//判斷是否為手牌 若是的話狀態改為出牌
bool IsCardInHand(Character &C,int card) {
	for (int i = 0; i < C.Deck.size(); i++) {
		if (C.Deck[i].ID == card) {
			C.Deck[i].status = 4;
			return true;
		}
	}
	return false;
}
//Check
void check(Character C) {
	cout << "HandCard:";
	for (int i = 0; i < C.Deck.size(); i++) {
		if (C.Deck[i].status == 1) {
			cout << C.Deck[i].ID << " ";
		}
	}
	cout << "Discard:";
	for (int i = 0; i < C.Deck.size(); i++) {
		if (C.Deck[i].status == 2) {
			cout << C.Deck[i].ID << " ";
		}
	}
	cout << "NowPlay:";
	for (int i = 0; i < C.Deck.size(); i++) {
		if (C.Deck[i].status == 4) {
			cout << C.Deck[i].ID << " ";
		}
	}
	cout << endl;

}
bool check_player_done(bool* player, int num) {
	for (int i = 0; i < num; i++) {
		if (!player[i]) {
			return true;
		}
	}
	return false;
}
//列出攻擊順序
void show_AttackList(vector<char> attack_Sort, vector<Character> Play_Character, vector<Ethnicity> Monster)
{
	for (int i = 0; i < attack_Sort.size(); i++) 
	{
		if (attack_Sort[i] <= 'Z' && attack_Sort[i] >= 'A') 
		{
			for (int j = 0; j < Play_Character.size(); j++) 
			{
				if (Play_Character[j].ID == attack_Sort[i]) 
				{
					if (Play_Character[j].Command[0] != -1) 
					{
						cout << Play_Character[j].ID << " " << setw(2) << setfill('0') << Play_Character[j].Deck[Play_Character[j].Command[0]].Dexterity_Value << " " << Play_Character[j].Command[0] << " " << Play_Character[j].Command[1] << endl;
					}
					else 
					{
						cout << Play_Character[j].ID << " 99 -1" << endl;
					}
				}
			}
		}
		else 
		{
			for (int j = 0; j < Monster.size(); j++) 
			{
				if (Monster[j].Command == -1)
					continue;
				for (int k = 0; k < Monster[j].Creature_List.size(); k++)
				{
					if (attack_Sort[i] == Monster[j].Creature_List[k].icon) 
					{
						cout << Monster[j].Ethnicity_Name << " " << setw(2) << setfill('0') << Monster[j].Deck[Monster[j].Command].Dexterity_Value<<" ";
						for (int L = 0; L < Monster[j].Deck[Monster[j].Command].Movement.size(); L++) 
						{
							cout << Monster[j].Deck[Monster[j].Command].Movement[L].Movement << " ";
							if (Monster[j].Deck[Monster[j].Command].Movement[L].Movement == "attack") 
							{
								cout << Monster[j].Deck[Monster[j].Command].Movement[L].Movement_Value << " ";
								if (Monster[j].Deck[Monster[j].Command].Movement[L].range != 0) 
								{
									cout << "range " << Monster[j].Deck[Monster[j].Command].Movement[L].range << " ";
								}
							}
							else if (Monster[j].Deck[Monster[j].Command].Movement[L].Movement == "move") 
							{
								cout << Monster[j].Deck[Monster[j].Command].Movement[L].Move_Command << " ";
							}
							else
							{
								cout << Monster[j].Deck[Monster[j].Command].Movement[L].Movement_Value << " ";
							}
						}
						cout << endl;
					}
				}
			}
		}
	}
}
//取得角色敏捷值by name
int get_Character_Dex(vector<Character> Play_Character,char name, int num) 
{
	for (int i = 0; i < Play_Character.size(); i++) 
	{
		if (Play_Character[i].ID == name) 
		{
			if (Play_Character[i].Command[0] == -1)
				return 99;
			else
				return Play_Character[i].Deck[Play_Character[i].Command[num]].Dexterity_Value;
		}
	}
}
int get_Monster_Dex(vector<Ethnicity> Monster, char name)
{
	for (int i = 0; i < Monster.size(); i++) 
	{
		for (int j = 0; j < Monster[i].Creature_List.size(); j++)
		{
			if (Monster[i].Creature_List[j].icon == name)
				return Monster[i].Deck[Monster[i].Command].Dexterity_Value;
		}
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
		int mode=0;
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
	File_Map.close();
}
//確認怪物狀態
void check_Monsters_Active(vector<Ethnicity>& Monster, Map Game_Map) 
{
	for (int i = 0; i < Monster.size(); i++) 
	{
		for (int j = 0; j < Monster[i].Creature_List.size(); j++) 
		{
			int x = Monster[i].Creature_List[j].position.x; int y = Monster[i].Creature_List[j].position.y;
			if (Game_Map.Game_Map[y][x] == 1) 
			{
				Monster[i].Creature_List[j].active = true;
			}
		}
	}
}
bool find_by_step(int x1, int y1, int x2, int y2, int step)
{
	if (x1 == x2 && y1 == y2)
	{
		return true;
	}
	if (step > 0)
	{
		if (find_by_step(x1 + 1, y1, x2, y2, step - 1) == true
			|| find_by_step(x1, y1 + 1, x2, y2, step - 1) == true
			|| find_by_step(x1 - 1, y1, x2, y2, step - 1) == true
			|| find_by_step(x1, y1 - 1, x2, y2, step - 1) == true)
		{
			return true;
		}
	}
	else if (step == 0)
	{
		return false;
	}
}
//確認移動路徑
bool move_Error(int x,int y,vector<Character> play_Character, vector<Ethnicity> Monster, Map Game_Map)
{
	if (Game_Map.Game_Map[y][x] != 1 && Game_Map.Game_Map[y][x] != 3)
	{
		return false;
	}
	for (int i = 0; i < Monster.size(); i++) 
	{
		for (int j = 0; j < Monster[i].Creature_List.size(); j++)
		{
			if (Monster[i].Creature_List[j].position.x == x && Monster[i].Creature_List[j].position.y == y) 
			{
				return false;
			}
		}
	}
	return true;
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
void check_all_dex(vector<Character> Play_Character, vector<Ethnicity> Monster) 
{
	cout << endl << "player:" << endl;
	for (int i = 0; i < Play_Character.size(); i++) 
	{
		cout << "	" << Play_Character[i].ID << " : " << Play_Character[i].Deck[Play_Character[i].Command[0]].Dexterity_Value << " " << Play_Character[i].Deck[Play_Character[i].Command[1]].Dexterity_Value << endl;
	}
	cout << "monsters:" << endl;
	for (int i = 0; i <Monster.size(); i++)
	{
		if (Monster[i].Command == -1) 
		{
			cout << "	" << Monster[i].Ethnicity_Name << " : deactivate." << endl;
		}
		else 
		{
			cout << "	" << Monster[i].Ethnicity_Name << " : " << Monster[i].Deck[Monster[i].Command].Dexterity_Value << endl;
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