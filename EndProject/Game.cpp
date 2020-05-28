#include"Game_Manager.h"
/*=============main_function==============*/

//�C���D�{��
void Main_Game(fstream& File_Character,fstream& File_Monster,fstream& File_Map, int DEBUG_MODE)
{
	vector<Character> Base_Character;	//����ҪO�A�A�Ω󤧫�Ыب���M��ɱq�̭��ƻs������
	vector<Ethnicity> Monster;			//�Ҧ��ر�
	vector<Character> play_Character;	//���a��ܪ�����C��

	read_Character_Data(File_Character, Base_Character);	//CharacterŪ��
	read_Monster_Data(File_Monster, Monster);			//MonsterŪ��
	while (1) 
	{
		Map GameMap; //�Ҧ�Map
		creat_Character(Base_Character, play_Character);		//�Ыب���
		cout << endl;
		read_Map_Data(File_Map, GameMap, Monster, play_Character.size()); //MapŪ��
		//get_All_Base_Character_Data(play_Character);	//�ˬdCharacter���
		get_All_Base_Monster_Data(Monster);				//�ˬdMonster���
		//get_int_Map(GameMap);	//�ˬd�a�ϸ��
		cout<<endl<< "***�п�J�_�l��m***:";
		choose_Start_Position(play_Character, Monster, GameMap);	//��ܰ_�l��m
		check_Monsters_Active(Monster, GameMap);	//�ˬd�Ǫ����A
		//�}�l�C���D�y�{
		main_Battle(play_Character, Monster, GameMap,DEBUG_MODE);
		play_Character.clear();
		for (int i = 0; i < Monster.size(); i++) 
		{
			Monster[i].Creature_List.clear();
			Monster[i].Shuffle_Mark = false;
			for (int j = 0; j < Monster[i].Deck.size(); j++) 
				Monster[i].Deck[j].status = 0;
		}
		GameMap.~Map();
		string again;
		do {
			cout << "�O�_��ܦA�C���@���H(y/exit)";
			std::cin >> again;
		} while (again != "y" && again != "Y" && again != "exit");
		if (again == "exit")
			break;
	}
}
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character)
{
	char character_count;
	do {
		cout << "�п�J�X������ƶq(�п�J2~4������ơA�ګ��U�A�F):";	//��J����ƶq
		std::cin >> character_count;
		if ((character_count - '0') < 2 || (character_count - '0') > 4)
			cout << "�ƶq���~!" << endl;
	} while ((character_count - '0') < 2 || (character_count - '0') > 4);
	for (int i = 0; i < character_count - '0'; i++)
	{
		cout << "***�п�J��"<< i + 1 << "������***�G";
		int character_number = 0;
		bool right_Character = false;
		do
		{	
			string character_name;
			std::cin >> character_name;
			for (int j = 0; j < Base_Character.size(); j++)
			{
				if (character_name == Base_Character[j].Character_name)		//���ҪO��������
				{
					right_Character = true;
					character_number = j;
					break;
				}
			}
			if (right_Character == false) 
			{
				cout << "�䤣�즹����A�Э��s��J..." << endl;
			}
		} while (right_Character == false);

		Character newCharacter = Base_Character[character_number];		//�ƻs�ҪO�������
		newCharacter.ID = 'A' + i;
		for (int j = 0; j < newCharacter.Hand; j++)
		{
			bool wrong_Input = false;
			int active_Card_ID;
			do {
				cout << "�п�J��" << j + 1 << "�i�d���G";
				wrong_Input = false;
				std::cin >> active_Card_ID;
				if (active_Card_ID >= newCharacter.Deck.size() || active_Card_ID < 0) 
				{
					wrong_Input = true;
				}
				else 
				{
					if (newCharacter.Deck[active_Card_ID].status == 1)
					{
						wrong_Input = true;
					}
				}
				if (wrong_Input) 
				{
					cout << "��J���~!" << endl;
				}
					
			} while (wrong_Input);
			newCharacter.Deck[active_Card_ID].status = 1;	//�]�w�_�l����P
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
		//���q���G��bug�ް_��J���~ �ӥB�����D�o�ͭ�] �ڤ���A���ݬ� �U���������ڬݬݳo��cin�|���|���L
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
			//if (position_input[j] == 13)	//enter�䵲��
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
void main_Battle(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map, int DEBUG_MODE)
{
	bool* already_played = nullptr;
	srand(time(NULL));
	int round = 1;
	while(end_Game(play_Character,Monster,Game_Map))	//�����C������ 1.����ƶq �Ǫ��ƶq ���ƶq
	{
		//get_All_Base_Monster_Data(Monster);
		cout << "round " << round << ":" << endl;
		already_played = new bool[play_Character.size()];
		for (int i = 0; i < play_Character.size(); i++) {
			already_played[i] = false;
			//cout << already_played[i] << endl;
		}
		//���a����ǳ�
		do {
			string who;
			std::cin >> who;
			for (int i = 0; i < play_Character.size(); i++) {
				if (who[0] == play_Character[i].ID) {
					int Discard_num = calculate_Discard(play_Character[i]); //�p���P��
					string command; // �Y��-1 check�ɬ����O ��L�h�� �X�P���Ĥ@�i
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
				else if (who == "check") {
					print_character_sort_onActive_monster(Monster, play_Character);
					break;
				}
				/*else {
					cout << "Enter CharacterId and choose card" << endl;
				}*/
			}
		} while (check_player_done(already_played, play_Character.size()));
		delete[] already_played;
		//�Ǫ��ǳ�
		for (int i = 0; i < Monster.size(); i++)	//��i�Ӻر�
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
			if (DEBUG_MODE == 0) 
			{
				bool finished = false;
				do
				{
					int choose = rand() % (Monster[i].Deck.size());
					if (Monster[i].Deck[choose].status == 0)	//�T�{�O�_�b�P�դ�
					{
						Monster[i].Deck[choose].status = 2;	//�令�X�P��
						Monster[i].Command = choose;
						if (Monster[i].Deck[choose].Shuffle_Mark) {
							Monster[i].Shuffle_Mark = true;
						}
						finished = true;		//�������
					}
				} while (finished == false);		//������ܧY���X���j��
			}
			else 
			{
				for (int j = 0; j < Monster[i].Deck.size(); j++) 
				{
					if (Monster[i].Deck[j].status == 0) 
					{
						Monster[i].Deck[j].status = 2;	//�令�X�P��
						Monster[i].Command = j;
						if (Monster[i].Deck[j].Shuffle_Mark) {
							Monster[i].Shuffle_Mark = true;
						}
						break;
					}
				}
			}
		}
		//check_all_dex(play_Character,Monster);	//�ˬd�ӱ���
		//�P�_�X�ⶶ��
		vector<char> attack_Sort;	//�H�ӱ��ȱƧǪ���������
		//���ƨ���
		attack_Sort.push_back(play_Character[0].ID);	//�N����A�[�J�Ƨ�
		for (int i = 1; i < play_Character.size(); i++)
		{
			for (int j = 0; j < attack_Sort.size(); j++)
			{
				int fir_Dex, sec_Dex;
				if (play_Character[i].Command[0] == -1)
				{
					fir_Dex = 99; sec_Dex = 99;
				}
				else
				{
					fir_Dex = play_Character[i].Deck[play_Character[i].Command[0]].Dexterity_Value;
					sec_Dex = play_Character[i].Deck[play_Character[i].Command[1]].Dexterity_Value;
				}
				if (fir_Dex < get_Character_Dex(play_Character, attack_Sort[j], 0))
				{
					attack_Sort.insert(attack_Sort.begin() + j, play_Character[i].ID);
					break;
				}
				else if (fir_Dex == get_Character_Dex(play_Character, attack_Sort[j], 0))
				{
					if (sec_Dex < get_Character_Dex(play_Character, attack_Sort[j], 1))
					{
						attack_Sort.insert(attack_Sort.begin() + j, play_Character[i].ID);
						break;
					}
					else if (j + 1 == attack_Sort.size()) //�ĤG�ӱӱ��Ȥ��M�ۦP�θ��j�A�ѩ�O�Ө���r�����ǥ[�i�ƧǡA�ҥH��������U�@��P�_�A�p�G����O�̫�@��A�h�����N����[��Ƨǳ̫�@��
					{
						attack_Sort.push_back(play_Character[i].ID);
						break;
					}
					else {
						continue;
					}
				}
				else if (j + 1 == attack_Sort.size()) //�ƧǤ����̫�@��
				{
					attack_Sort.push_back(play_Character[i].ID);
					break;
				}
				else
				{

				}
			}
		}
		//�A�ƩǪ�		�ѩ�Ǫ��O�H�رڨӱơA�ҥH�ǦC�̧ڱN�Ǫ����N���H('a'+i�N��)�A��ɭԼg�����ɭn�y�L�`�N
		for (int i = 0; i < Monster.size(); i++)
		{
			if (Monster[i].Command == -1)
				continue;
			for (int k = 0; k < Monster[i].Creature_List.size(); k++)
			{
				if (Monster[i].Creature_List[k].active == false)
					continue;
				for (int j = 0; j < attack_Sort.size(); j++)
				{
					if (attack_Sort[j] >= 'A' && attack_Sort[j] <= 'Z') //�P�_�O�_�O���a����
					{
						if (Monster[i].Deck[Monster[i].Command].Dexterity_Value < get_Character_Dex(play_Character, attack_Sort[j], 0))
						{
							attack_Sort.insert(attack_Sort.begin() + j, Monster[i].Creature_List[k].icon);
							break;
						}
					}
					else
					{
						if (Monster[i].Deck[Monster[i].Command].Dexterity_Value < get_Monster_Dex(Monster, attack_Sort[j]))
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
		//�ˬd�Ƨ�
		show_AttackList(attack_Sort, play_Character, Monster);

		//�ʧ@����
		for (int i = 0; i < attack_Sort.size(); i++)
		{
			if (attack_Sort[i] <= 'Z' && attack_Sort[i] >= 'A')		//������
			{
				for (int j = 0; j < play_Character.size(); j++) 
				{
					if (play_Character[j].ID == attack_Sort[i]) 
					{
						players_round(play_Character, play_Character[j], Monster, Game_Map);
					}
				}
			}
			else //�Ǫ����
			{
				for (int j = 0; j < Monster.size(); j++)
				{
					for (int k = 0; k < Monster[j].Creature_List.size(); k++)
					{
						if (attack_Sort[i] == Monster[j].Creature_List[k].icon)
						{
							monsters_round(play_Character, Monster[j], Monster[j].Creature_List[k], Game_Map,Monster,attack_Sort);
							break;
						}
					}
				}
			}
		}
		//�^�X����
		attack_Sort.clear();
		end_round(play_Character, Monster, Game_Map);
		round++;
	}
}
bool end_Game(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Map) 
{
	if (play_Character.size() == 0) 
	{
		cout << "monster win~" << endl;
		return false;
	}
	bool all_Monsters_Dead = true;
	for (int i = 0; i < Monster.size(); i++) 
	{
		if (Monster[i].Creature_List.size() != 0) 
		{
			all_Monsters_Dead = false;
		}
	}
	bool all_Door_open = true;
	for (int i = 0; i < Map.High; i++) 
	{
		for (int j = 0; j < Map.Width; j++) 
		{
			if (Map.Game_Map[i][j] == 3) 
			{
				all_Door_open = false;
			}
		}
	}
	if (all_Monsters_Dead == true && all_Door_open ==true) 
	{
		cout << "character win~" << endl;
		return false;
	}
	return true;
}
//���
void players_round(vector<Character>& play_Character, Character& Character, vector<Ethnicity>& Monster, Map& Game_Map)
{
	if (Character.Rest == false)
	{
		cout << Character.ID << "'s rturn: card " << Character.Command[0] << " " << Character.Command[1] << endl;
		int card_num=0; char UpOrDown=' ';
		string temp;
		while (cin >> temp) {
			if (temp.size() == 2) {
				card_num = temp[0] - 48;
				UpOrDown = temp[1];
			}
			if (temp == "check") {
				print_character_sort_onActive_monster(Monster, play_Character);
			}
			else if (Character.Deck[card_num].status == 4&& temp.size() == 2)
			{
				if (UpOrDown == 'u'&& temp.size() == 2)
				{
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
								if (Character.Attack(Character.Deck[card_num].MovementUp[j].Movement_Value, Character.Deck[card_num].MovementUp[j].range, Monster, Game_Map) == true)
									Game_Map.print_Map(play_Character, Monster);
							}
						}
						else if (Character.Deck[card_num].MovementUp[j].Movement == "shield") {
							Character.Skill_shield(Character.Deck[card_num].MovementUp[j].Movement_Value);
							cout << Character.ID << " shield " << Character.Deck[card_num].MovementUp[j].Movement_Value << " this turn" << endl;
						}
						else if (Character.Deck[card_num].MovementUp[j].Movement == "heal") {
							Character.Skill_heal(Character.Deck[card_num].MovementUp[j].Movement_Value);
							cout << Character.ID << " heal " << Character.Deck[card_num].MovementUp[j].Movement_Value << ", now is " << Character.Hp << endl;
						}
						else if (Character.Deck[card_num].MovementUp[j].Movement == "move") {
							character_move(Character, Character.Deck[card_num].MovementUp[j].Movement_Value, Game_Map, play_Character, Monster);
							Game_Map.print_Map(play_Character, Monster);
						}
					}
					Character.Deck[card_num].status = 2;
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
								if (Character.Attack(Character.Deck[card_num].MovementDown[j].Movement_Value, Character.Deck[card_num].MovementDown[j].range, Monster, Game_Map) == true)
									Game_Map.print_Map(play_Character, Monster);
							}
						}
						else if (Character.Deck[card_num].MovementDown[j].Movement == "shield") {
							Character.Skill_shield(Character.Deck[card_num].MovementDown[j].Movement_Value);
							cout << Character.ID << " shield " << Character.Deck[card_num].MovementDown[j].Movement_Value << " this turn" << endl;
						}
						else if (Character.Deck[card_num].MovementDown[j].Movement == "heal") {
							Character.Skill_heal(Character.Deck[card_num].MovementDown[j].Movement_Value);
							cout << Character.ID << " heal " << Character.Deck[card_num].MovementDown[j].Movement_Value << ", now is " << Character.Hp << endl;
						}
						else if (Character.Deck[card_num].MovementDown[j].Movement == "move") {
							character_move(Character, Character.Deck[card_num].MovementDown[j].Movement_Value, Game_Map, play_Character, Monster);
							Game_Map.print_Map(play_Character, Monster);
						}
					}
					Character.Deck[card_num].status = 2;
					break;
				}
				else if(UpOrDown == 'd'&& temp.size() == 2)
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
								if (Character.Attack(Character.Deck[card_num].MovementDown[j].Movement_Value, Character.Deck[card_num].MovementDown[j].range, Monster, Game_Map) == true)
									Game_Map.print_Map(play_Character, Monster);
							}
						}
						else if (Character.Deck[card_num].MovementDown[j].Movement == "shield") {
							Character.Skill_shield(Character.Deck[card_num].MovementDown[j].Movement_Value);
							cout << Character.ID << " shield " << Character.Deck[card_num].MovementDown[j].Movement_Value << " this turn" << endl;
						}
						else if (Character.Deck[card_num].MovementDown[j].Movement == "heal") {
							Character.Skill_heal(Character.Deck[card_num].MovementDown[j].Movement_Value);
							cout << Character.ID << " heal " << Character.Deck[card_num].MovementDown[j].Movement_Value << ", now is " << Character.Hp << endl;
						}
						else if (Character.Deck[card_num].MovementDown[j].Movement == "move") {
							character_move(Character, Character.Deck[card_num].MovementDown[j].Movement_Value, Game_Map, play_Character, Monster);
							Game_Map.print_Map(play_Character, Monster);
						}
					}
					Character.Deck[card_num].status = 2;
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
								if (Character.Attack(Character.Deck[card_num].MovementUp[j].Movement_Value, Character.Deck[card_num].MovementUp[j].range, Monster, Game_Map) == true)
									Game_Map.print_Map(play_Character, Monster);
							}
						}
						else if (Character.Deck[card_num].MovementUp[j].Movement == "shield") {
							Character.Skill_shield(Character.Deck[card_num].MovementUp[j].Movement_Value);
							cout << Character.ID << " shield " << Character.Deck[card_num].MovementUp[j].Movement_Value << " this turn" << endl;
						}
						else if (Character.Deck[card_num].MovementUp[j].Movement == "heal") {
							Character.Skill_heal(Character.Deck[card_num].MovementUp[j].Movement_Value);
							cout << Character.ID << " heal " << Character.Deck[card_num].MovementUp[j].Movement_Value << ", now is " << Character.Hp << endl;
						}
						else if (Character.Deck[card_num].MovementUp[j].Movement == "move") {
							character_move(Character, Character.Deck[card_num].MovementUp[j].Movement_Value, Game_Map, play_Character, Monster);
							Game_Map.print_Map(play_Character, Monster);
						}
					}
					Character.Deck[card_num].status = 2;
					break;
				}
				
			}
			else {
			cout << "Please Enter Right Command" << endl;
			}	
		}	
	}
	else
	{
		cout << Character.ID << "'turn: card -1" << endl;
		Character.long_Rest();
	}
}
void monsters_round(vector<Character>& play_Character, Ethnicity& Monster_Ethnicity, Monster_Base& monster, Map Game_Map,vector<Ethnicity>& Monster, vector<char> attack_Sort)
{
	if (Monster_Ethnicity.Command == -1) {
		return;
	}
	for (int i = 0; i < Monster_Ethnicity.Deck.size(); i++)
	{
		if (Monster_Ethnicity.Deck[i].status == 2) 
		{
			for (int j = 0; j < Monster_Ethnicity.Deck[i].Movement.size(); j++) 
			{
				if (Monster_Ethnicity.Deck[i].Movement[j].Movement == "attack") {
					if (monster_Attack(monster, Monster_Ethnicity.Deck[i].Movement[j].Movement_Value, Monster_Ethnicity.Deck[i].Movement[j].range, attack_Sort, Monster, play_Character, Game_Map) == true)
					{
						Game_Map.print_Map(play_Character, Monster);
					}
					//cout << "attack" << endl;
				}
				else if (Monster_Ethnicity.Deck[i].Movement[j].Movement == "shield") {
					monster.Skill_shield(Monster_Ethnicity.Deck[Monster_Ethnicity.Command].Movement[j].Movement_Value);
					cout << monster.icon << " shield " << Monster_Ethnicity.Deck[Monster_Ethnicity.Command].Movement[j].Movement_Value << " this turn" << endl;
				}
				else if (Monster_Ethnicity.Deck[i].Movement[j].Movement == "heal") {
					monster.Skill_heal(Monster_Ethnicity.Deck[Monster_Ethnicity.Command].Movement[j].Movement_Value);
					cout << monster.icon << " heal " << Monster_Ethnicity.Deck[Monster_Ethnicity.Command].Movement[j].Movement_Value << ", now is " << monster.Hp << endl;
				}
				else if (Monster_Ethnicity.Deck[i].Movement[j].Movement == "move") {
					monster_move(monster, Monster_Ethnicity.Deck[i].Movement[j].Move_Command, Game_Map, play_Character, Monster);
					Game_Map.print_Map(play_Character, Monster);
				}
			}
			break;
		}
	}
}
void end_round(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Map) {
	bool no_monster = true;
	//�@���k0
	for (int i = 0; i < play_Character.size(); i++) {
		play_Character[i].Shield = 0;
	}
	for (int i = 0; i < Monster.size(); i++) {
		if (Monster[i].Command != -1) 
		{
			Monster[i].Deck[Monster[i].Command].status = 1;
		}
		for (int j = 0; j < Monster[i].Creature_List.size(); j++) {
			Monster[i].Creature_List[j].Shield = 0;
			if (Monster[i].Creature_List[j].active) {
				no_monster = false;
			}
		}
		//�Ǫ��P�_�O�_�����~
		if (Monster[i].Shuffle_Mark) {
			for (int j = 0; j < Monster[i].Deck.size(); j++) {
				if (Monster[i].Deck[j].status == 1) {
					Monster[i].Deck[j].status = 0;
				}
			}
			Monster[i].Shuffle_Mark = false;
		}
	}
	//�P�_���⦳�S���b���W�M�P�_���S���Ѿl�Ǫ� �}�� and ���m������𪬺A
	bool open_Door = false;
	for (int i = 0; i < play_Character.size(); i++) 
	{
		play_Character[i].Rest = false;
		if (Map.Game_Map[play_Character[i].position.y][play_Character[i].position.x] == 3 && no_monster == true) {
			Map.Game_Map[play_Character[i].position.y][play_Character[i].position.x] = 1;
			open_Door = true;
		}
	}
	//���Ҧ������}���A���s������
	
	if (open_Door == true) 
	{
		for (int i = 0; i < play_Character.size(); i++)
		{
			Map.check_road(play_Character[i].position.x, play_Character[i].position.y);
		}
		Map.print_Map(play_Character, Monster);
	}
	for (int i = 0; i < Monster.size(); i++) 
	{
		for (int j = 0; j < Monster[i].Creature_List.size(); j++)
		{
			int x = Monster[i].Creature_List[j].position.x;
			int y = Monster[i].Creature_List[j].position.y;
			if (Map.Game_Map[y][x] == 1) 
			{
				Monster[i].Creature_List[j].active = true;
			}
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
						if (play_Character[j].position.x == C.position.x && play_Character[j].position.y == C.position.y&&play_Character[j].ID!= C.ID)
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
//�Ǫ�����
void monster_move(Monster_Base& C, string position_input, Map& Game_Map, vector<Character> play_Character, vector<Ethnicity> Monster) {
	Position start = C.position;
	for (int i = 0; i < position_input.size(); i++)
	{
		start = C.position;
		switch (position_input[i])
		{
		case'w':
		case 'W':
			if (move_Error_Monster(C.position.x, C.position.y - 1, play_Character, Game_Map) == true)
			{
				C.position.y--;
			}
			break;
		case's':
		case 'S':
			if (move_Error_Monster(C.position.x, C.position.y + 1, play_Character, Game_Map) == true)
			{
				C.position.y++;
			}
			break;
		case'a':
		case 'A':
			if (move_Error_Monster(C.position.x - 1, C.position.y, play_Character, Game_Map) == true)
			{
				C.position.x--;
			}
			break;
		case'd':
		case 'D':
			if (move_Error(C.position.x + 1, C.position.y, play_Character, Monster, Game_Map) == true)
			{
				C.position.x++;
			}
		}
		if (i == position_input.size() - 1)
		{
			for (int j = 0; j < Monster.size(); j++)
			{
				for (int k = 0; k < Monster[j].Creature_List.size(); k++) {
					if (Monster[j].Creature_List[k].position.x == C.position.x && Monster[j].Creature_List[k].position.y == C.position.y&& Monster[j].Creature_List[k].icon!=C.icon)
					{
						C.position = start;
					}
				}
			}
		}
	}
}
bool vision_search(Position p1, Position p2, Map Map) {
	int xvalue, yvalue;
	if (p1.x > p2.x&& p1.y >= p2.y) {
		swap(p1, p2);
	}
	else if (p1.x > p2.x&& p1.y <= p2.y) {
		swap(p1, p2);
	}
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
	//�ײv���� ���W��k�U
	else if (p1.x < p2.x && p2.y >= p1.y) {
		float tan = (p1.y - p2.y) / (p1.x - p2.x);
		cout << tan << endl;
		for (float i = 0; i <= p2.x - p1.x; i += 0.0001) {
			xvalue = floor(i + p1.x + 0.5);
			yvalue = floor(i * tan + p1.y + 0.5);
			if (Map.Game_Map[yvalue][xvalue] = 0) {
				return true;
			}
		}
	}
	//�ײv���t ���U��k�W
	else if (p1.x < p2.x && p1.y >= p2.y) {
		float tan = (p1.y - p2.y) / (p1.x - p2.x) * -1;
		cout << tan << endl;
		for (float i = 0; i <= p2.x - p1.x; i += 0.0001) {
			xvalue = floor(i + 0.5 + p1.x);
			yvalue = floor(p1.y + 0.5 - i * tan);
			if (Map.Game_Map[yvalue][xvalue] = 0) {
				return true;
			}
		}
	}
	return false;
}
bool monster_Attack(Monster_Base& M,int value,int range, vector<char> attack_Sort, vector<Ethnicity> Monster, vector<Character>& play_Character, Map& Game_Map)
{
	vector<int> target_List;
	int min_Distance = -1;
	for (int i = 0; i < play_Character.size(); i++) 
	{
		if (min_Distance == -1)
			min_Distance = abs(M.position.x - play_Character[i].position.x) + abs(M.position.y - play_Character[i].position.y);
		int distance = abs(M.position.x - play_Character[i].position.x) + abs(M.position.y - play_Character[i].position.y);
		if (range + M.Range == 0) 
		{
			if (distance == 1) 
			{
				target_List.push_back(i);
			}
		}
		else 
		{
			if (distance <= range + M.Range && vision_search(M.position, play_Character[i].position, Game_Map) == false)
			{
				target_List.push_back(i);
			}
		}
		if (distance < min_Distance)
			min_Distance = distance;
	}
	for (int i = target_List.size() - 1; i >= 0; i--) 
	{
		if ((abs(M.position.x - play_Character[target_List[i]].position.x) + abs(M.position.y - play_Character[target_List[i]].position.y)) > min_Distance)
			target_List.erase(target_List.begin() + i);
	}
	int final_Target = 99;
	for (int i = 0; i < attack_Sort.size(); i++) 
	{
		for (int j = 0; j < target_List.size(); j++) 
		{
			if (play_Character[target_List[j]].ID == attack_Sort[i]) 
			{
				final_Target = target_List[j];
			}
		}
		if (final_Target != 99)
			break;
	}
	if (final_Target == 99) 
	{
		cout << "no one lock" << endl;
		return false;
	}
	int distance = abs(M.position.x - play_Character[final_Target].position.x) + abs(M.position.y - play_Character[final_Target].position.y);
	cout << M.icon << " lock " << play_Character[final_Target].ID << " in distance " << distance << endl;
	//b attack A 3 damage, A shield 1, A remain 12 hp
	cout << M.icon << " attack " << play_Character[final_Target].ID << " " << (M.Damage +value) << " damage, " << play_Character[final_Target].ID << " shield " << play_Character[final_Target].Shield << ", " << play_Character[final_Target].ID << " remain ";
	if (play_Character[final_Target].Shield < M.Damage + value) 
	{
		play_Character[final_Target].Hp -= ((M.Damage + value) - play_Character[final_Target].Shield);
	}
	else 
	{
		play_Character[final_Target].Shield -= (M.Damage + value);
	}
	cout << play_Character[final_Target].Hp << " hp" << endl;
	if (play_Character[final_Target].Hp <= 0) 
	{
		cout << play_Character[final_Target].ID << " is killed!!" << endl;
		play_Character.erase(play_Character.begin() + final_Target);
	}
	return false;
}
//�p�⨤���P�諸�ƶq
int calculate_Discard(Character C) {
	int num = 0;
	for (int i = 0; i < C.Deck.size(); i++) {
		if (C.Deck[i].status == 2) {
			num++;
		}
	}
	return num;
}
//�P�_�O�_����P
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
//�P�_�O�_����P �Y�O���ܪ��A�אּ�X�P
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
//�C�X��������
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
						cout<<"����:" << Play_Character[j].ID << " " << setw(2) << setfill('0')<<"�ӱ���:"<< Play_Character[j].Deck[Play_Character[j].Command[0]].Dexterity_Value << " �d���@:" << Play_Character[j].Command[0] << " �d���G:" << Play_Character[j].Command[1] << endl;
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
								cout << Monster[j].Deck[Monster[j].Command].Movement[L].Movement_Value << " " << "range " << Monster[j].Deck[Monster[j].Command].Movement[L].range << " ";
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
//���o����ӱ���by name
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
//Ū��
void read_Character_Data(fstream& File_Charactervector, vector<Character>& Base_Character)
{
	int Charactor_count,Hp,Hand,Deck; string Charactor_Name;
	/*========Ū���X�Ө���ҪO=========*/
	File_Charactervector >> Charactor_count;
	for (int i = 0; i < Charactor_count; i++) 
	{
		/*========Ū������ҪO��T=========*/
		File_Charactervector >> Charactor_Name >> Hp >> Hand >> Deck;
		Character Base_type(Charactor_Name,Hp,Hand);		//�s���ҪO
		/*====Ū������ҪO�d����T====*/
		for (int j = 0; j < Deck; j++)	//�@�զ@��Deck�i�d 
		{
			Player_Card newCard;	//�s���d��
			string per_line,upString,downString;string skill_Name;	int skill_Value;
			File_Charactervector >> newCard.ID >> newCard.Dexterity_Value;		//Ū���d����ID �M �ӱ���
			getline(File_Charactervector, per_line);		//�I�U��q��O��
			stringstream interval(per_line);
			getline(interval, upString, '-');getline(interval, downString);		//�H"-"���ɱN��q�r����Φ� �W�������ޯ� �M �U�������ޯ�
			interval.clear(); interval.str("");		//�M��stringstream
			interval << upString;
			while (interval >> skill_Name >> skill_Value)	//��"�Ů�"�N�r����Φ� ��O �M ��	
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
			interval.clear(); interval.str("");		//�M��stringstream
			interval << downString;
			while (interval >> skill_Name >> skill_Value)	//��"�Ů�"�N�r����Φ� ��O �M ��	
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
			Base_type.Deck.push_back(newCard);		//�N�s���d���[�i�d��
		}
		Base_Character.push_back(Base_type);		//�N�s������ҪO�[�J�ҪO�C��
	}
}
void read_Monster_Data(fstream& File_Monster, vector<Ethnicity>& Base_Monster) 
{
	int Monster_count;
	File_Monster >> Monster_count;		//�رڼƶq
	for (int i = 0; i < Monster_count; i++) 
	{
		string Ethnicity_Name; int hp, atk, range, elite_hp, elite_damage, elite_range;
		File_Monster >> Ethnicity_Name >> hp >> atk >> range >> elite_hp >> elite_damage >> elite_range;
		Ethnicity Base_Type(Ethnicity_Name, hp, atk,range, elite_hp, elite_damage, elite_range);	//�ŧi�Ǫ��ҪO
		for (int j = 0; j < 6; j++)		//�Ǫ��T�w���i�ޯ�d
		{
			string per_line, Movement;
			int skill_Value;
			stringstream interval("");
			Creature_Card newCard;	//�s���d��
			File_Monster >> Ethnicity_Name >> newCard.ID >> newCard.Dexterity_Value;	//Ū���d�����
			getline(File_Monster, per_line);	//�I�U��q��O��
			interval << per_line;
			while (interval >> Movement)	//�H"�Ů�"���Φr��
			{
				Card_Property newMovement;
				if (Movement == "move")		//�P�_�O�_��"move���O"
				{
					interval >> newMovement.Move_Command;
				}
				else if (Movement == "d")	//�p�G�O���~�лx�N���X
				{
					newCard.Shuffle_Mark = false;
					break;
				}
				else if (Movement == "r")	//�p�G�O���~�лx�N���X
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
			interval.clear();		//�M��stringstream
			interval.str("");
			Base_Type.Deck.push_back(newCard);
		}
		Base_Monster.push_back(Base_Type);
	}
}
void read_Map_Data(fstream& File_Map, Map& Map, vector<Ethnicity>& Monster,int Player_num)
{
	string File_Name;	
	do 
	{
		cout << "�п�J�a�Ϧ�}�G";
		cin >> File_Name;	//��J�a���ɦW
		File_Map.open(File_Name, ios::in);	//������
		if (!File_Map)
			cout << "�䤣���}�ɮ�" << endl;
	} while (!File_Map);
	//File_Map.open("map1.txt", ios::in);		//���ե�
	File_Map >> Map.High >> Map.Width;
	vector<int>temp;
	for (int i = 0; i < Map.High; i++)
	{
		for (int j = 0; j < Map.Width; j++)
		{
			char temp_num;
			File_Map >> temp_num;
			int temp_num_int = temp_num - '0';
			if (temp_num_int == 1)
			{
				temp_num_int = 4;
			}
			else if (temp_num == 2)
			{
				temp_num_int = 6;
			}
			temp.push_back(temp_num_int);
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
	int a = Monster.size();
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
				Monster_temp.Max_HP = Monster[j].Ethnicity_Base_value.Hp;
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
				Monster_temp.Max_HP = Monster[j].Ethnicity_Base_value.Elite_Hp;
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
//�T�{�Ǫ����A
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
//�T�{���ʸ��|
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
bool move_Error_Monster(int x, int y, vector<Character> play_Character, Map Game_Map)
{
	if (Game_Map.Game_Map[y][x] != 1)
	{
		return false;
	}
	for (int i = 0; i < play_Character.size(); i++)
	{
		if (play_Character[i].position.x == x && play_Character[i].position.y == y)
		{
			return false;
		}
	}
	return true;
}
//
void print_character_sort_onActive_monster(vector<Ethnicity> Monster, vector<Character> play_Character) {
	vector<Monster_Base>temp;
	for (int i = 0; i < play_Character.size(); i++) {
		cout << play_Character[i].ID << "-hp:" << play_Character[i].Hp << ", shield: " << play_Character[i].Shield << endl;
	}
	for (int i = 0; i < Monster.size(); i++)
	{
		for (int j = 0; j < Monster[i].Creature_List.size(); j++)
		{
			if (Monster[i].Creature_List[j].active)
			{
				temp.push_back(Monster[i].Creature_List[j]);
			}
		}
	}
	sort(temp.begin(), temp.end(),abcSort);
	for (int i = 0; i < temp.size(); i++) {
		cout << temp[i].icon << "-hp:" << temp[i].Hp << ", shield: " << temp[i].Shield << endl;
	}

}
bool abcSort(Monster_Base a,Monster_Base b) {
	if (a.icon > b.icon)
	{
		return false;
	}
	else {
		return true;
	}
}
/*==============DEBUG_MODE================*/

void get_All_Base_Character_Data(vector<Character> Base_Player) 
{
	for (int i = 0; i < Base_Player.size(); i++)
	{
		cout << "����W�G" << Base_Player[i].Character_name << "  ���� HP�G" << Base_Player[i].Hp << " �����P�ơG" << Base_Player[i].Hand << endl << "�ޯ�d�G" << endl;
		for (int j = 0; j < Base_Player[i].Deck.size(); j++)
		{
			cout << "ID�G	" << Base_Player[i].Deck[j].ID << " ���A: " << Base_Player[i].Deck[j].status << "	�ӱ��ȡG	" << Base_Player[i].Deck[j].Dexterity_Value << "	�W�G";
			for (int k = 0; k < Base_Player[i].Deck[j].MovementUp.size(); k++) 
			{
				cout << Base_Player[i].Deck[j].MovementUp[k].Movement << " " << Base_Player[i].Deck[j].MovementUp[k].Movement_Value << " ";
				if (Base_Player[i].Deck[j].MovementUp[k].Movement == "attack")
					cout << "range " << Base_Player[i].Deck[j].MovementUp[k].range << " ";
			}
			cout << " | �U�G";
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
		cout << "�رڦW�G" << Base_Monster[i].Ethnicity_Name
			<< " ���q�ͩR�G" << Base_Monster[i].Ethnicity_Base_value.Hp
			<< " ���q�����G" << Base_Monster[i].Ethnicity_Base_value.Damage
			<< " ���q�d��G" << Base_Monster[i].Ethnicity_Base_value.Range
			<< " �׭^�ͩR�G" << Base_Monster[i].Ethnicity_Base_value.Elite_Hp
			<< " �׭^�����G" << Base_Monster[i].Ethnicity_Base_value.Elite_Damage
			<< " �׭^�d��G" << Base_Monster[i].Ethnicity_Base_value.Elite_Range << endl << endl;
		for (int j = 0; j < Base_Monster[i].Creature_List.size(); j++)
		{
			cout << "�Ǫ�" << Base_Monster[i].Creature_List[j].icon;
			if (Base_Monster[i].Creature_List[j].mode == 2)
				cout << ": �׭^";
			else
				cout << ": ���q";
			cout << " �ͩR��:" << Base_Monster[i].Creature_List[j].Hp
				<< " �ˮ`:" << Base_Monster[i].Creature_List[j].Damage
				<< " �d��:" << Base_Monster[i].Creature_List[j].Range << endl;
		}
		cout << "�ޯ�d�G" << endl;
		for (int j = 0; j < 6; j++) 
		{
			cout << "ID�G" << Base_Monster[i].Deck[j].ID << " ���A: " << Base_Monster[i].Deck[j].status << "	�ӱ��ȡG" << Base_Monster[i].Deck[j].Dexterity_Value << "	";
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
			cout <<"���~�лx�G"<< Base_Monster[i].Deck[j].Shuffle_Mark << endl;
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
	case 0:		//�}�l�C��
		break;
	case 1:		//�����C��
		system("cls");
		cout << "�P�±z���C��" << endl << endl;
		system("pause");
		return;
		break;
	default:
		break;
	}
}

//�}�l����  �^�ǭ� = 0:�}�l�C�� �A�^�ǭ� = 1:�����C��
int Project_Start_UI() 
{
	cout << "    GloomHaven   " << endl << endl;
	cout << "=================" << endl;
	cout << "=      "; SetColor(240); cout << "�}�l"; SetColor(7);cout << "     =" << endl;
	cout << "=      ���}     =" << endl;
	cout << "=================" << endl << endl << endl;
	int mode = 0;			//��ܭn�}�l�C���άO���}
	char keyBoard_Input;	//��L��J
	while (1) 
	{
		keyBoard_Input = _getch();
		//�N�ϥժ���r�έ�Ӫ��C��\�L
		if (mode == 1)
		{
			setPrintPosition(7, 4);
			SetColor(7); cout << "���}";
		}
		else if (mode == 0)
		{
			setPrintPosition(7, 3);
			SetColor(7); cout << "�}�l";
		}
		//�ھ�keyBoard��J�M�w�n���@�ӿﶵ
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
		//�N�쥻����r�Τϥջ\�L
		if (mode == 1)
		{
			setPrintPosition(7, 4);
			SetColor(240); cout << "���}";
		}
		else if (mode == 0)
		{
			setPrintPosition(7, 3);
			SetColor(240); cout << "�}�l";
		}
		setPrintPosition(0, 30);	SetColor(7);	//���m print�I �M �C�� (�Y�n�ϥ�setPrintPosition �άO SetColor �ϥΫ�A�Шϥγo�q���m�L�̪��]�w)
		if (keyBoard_Input == 13)		//Enter�� �^��mode;
			return mode;
	}
}

/*=============Windows.h��function==============*/
void setPrintPosition(int x, int y)		//����Print���_�l��m
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(out, coordinate);
}
void SetColor(int color)				//�����C��
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}