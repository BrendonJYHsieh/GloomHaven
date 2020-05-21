#include"Game_Manager.h"
/*=============main_function==============*/

//�C���D�{��
void Main_Game(fstream& File_Character,fstream& File_Monster,fstream& File_Map)
{
	vector<Character> Base_Character;	//����ҪO�A�A�Ω󤧫�Ыب���M��ɱq�̭��ƻs������
	vector<Ethnicity> Monster;			//�Ҧ��ر�
	Map GameMap; //�Ҧ�Map
	vector<Character> play_Character;	//���a��ܪ�����C��

	read_Character_Data(File_Character, Base_Character);	//CharacterŪ��
	read_Monster_Data(File_Monster, Monster);			//MonsterŪ��
	while (1) 
	{
		creat_Character(Base_Character, play_Character);		//�Ыب���
		read_Map_Data(File_Map, GameMap, Monster, play_Character.size()); //MapŪ��
		get_All_Base_Character_Data(play_Character);	//�ˬdCharacter���
		get_All_Base_Monster_Data(Monster);				//�ˬdMonster���
		//get_int_Map(GameMap);	//�ˬd�a�ϸ��
		choose_Start_Position(play_Character, Monster, GameMap);	//��ܰ_�l��m
		check_Monsters_Active(Monster, GameMap);	//�ˬd�Ǫ����A
		//�}�l�C���D�y�{
		main_Battle(play_Character, Monster, GameMap);
		play_Character.clear();
		for (int i = 0; i < Monster.size(); i++) 
		{
			Monster[i].Creature_List.clear();
		}
		GameMap.Game_Map.clear();
		GameMap.Init_Pos.clear();
		char again;
		cout << "�O�_��ܦA�C���@���H(y/n)";
		std::cin >> again;
		if (again == 'n')
			break;
	}
}
void creat_Character(vector<Character>& Base_Character, vector<Character>& play_Character)
{
	int character_count;
	do {
		cout << "�п�J�X������ƶq:" << endl;	//��J����ƶq
		std::cin >> character_count;
		if (character_count < 2 || character_count>4)
			cout << "�ƶq���~!" << endl;
	} while (character_count < 2 || character_count>4);
	for (int i = 0; i < character_count; i++)
	{
		int character_number = 0; string character_name;
		std::cin >> character_name;
		for (int j = 0; j < Base_Character.size(); j++)
		{
			if (character_name == Base_Character[j].Character_name)		//���ҪO��������
			{
				character_number = j;
				break;
			}
		}
		Character newCharacter = Base_Character[character_number];		//�ƻs�ҪO�������
		newCharacter.ID = 'A' + i;
		for (int j = 0; j < newCharacter.Hand; j++)
		{
			int active_Card_ID;
			do {
				std::cin >> active_Card_ID;
				if (active_Card_ID < 0 || character_count > newCharacter.Deck.size() - 1)
					cout << "��J���~!" << endl;
			} while (active_Card_ID < 0 || character_count > newCharacter.Deck.size() - 1);
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
void main_Battle(vector<Character>& play_Character, vector<Ethnicity>& Monster, Map& Game_Map) 
{
	bool* already_played = nullptr;
	srand(time(NULL));
	int round = 1;
	while(1)	//�����C������ 1.����ƶq �Ǫ��ƶq ���ƶq
	{
		already_played = new bool[play_Character.size()];
		for (int i = 0; i < play_Character.size(); i++) {
			already_played[i] = false;
			//cout << already_played[i] << endl;
		}
		do {
			char who;
			std::cin >> who;
			for (int i = 0; i < play_Character.size(); i++) {
				if (who == i + 'A') {
					int Discard_num = calculate_Discard(play_Character[i]); //�p���P��
					string command; // �Y��-1 check�ɬ����O ��L�h�� �X�P���Ĥ@�i
					std::cin >> command;
					if (command == "-1"&&Discard_num>=2&& !already_played[i]) {
						play_Character[i].Dex[0] = 99;
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
										play_Character[i].Dex[0] = play_Character[i].Deck[k].Dexterity_Value;
									else if(play_Character[i].Deck[k].ID == card2)
										play_Character[i].Dex[1] = play_Character[i].Deck[k].Dexterity_Value;
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
		//cout << "End" << endl;
		//�Ǫ��ǳ�
		for (int i = 0; i < Monster.size(); i++)	//��i�Ӻر�
		{
			bool finished = false;
			do
			{
				int choose = rand() % (Monster[i].Deck.size());
				if (Monster[i].Deck[choose].status == 0)	//�T�{�O�_�b�P�դ�
				{
					Monster[i].Deck[choose].status = 2;	//�令�X�P��
					Monster[i].Dex = Monster[i].Deck[choose].Dexterity_Value;
					finished = true;		//�������
				}
			} while (finished == false);		//������ܧY���X���j��
		}
		check_all_dex(play_Character,Monster);
		//�P�_�X�ⶶ��
		vector<char> attack_Sort;	//�H�ӱ��ȱƧǪ���������
		//���ƨ���
		attack_Sort.push_back(play_Character[0].ID);	//�N����A�[�J�Ƨ�
		for (int i = 1; i < play_Character.size(); i++) 
		{
			for (int j = 0; j < attack_Sort.size(); j++) 
			{
				if (play_Character[i].Dex[0] < get_Character_Dex(play_Character, attack_Sort[j], 0))
				{
					attack_Sort.insert(attack_Sort.begin() + j, play_Character[i].ID);
					break;
				}
				else if (play_Character[i].Dex[0] == get_Character_Dex(play_Character, attack_Sort[j], 0))
				{
					if (play_Character[i].Dex[1] < get_Character_Dex(play_Character, attack_Sort[j], 1))
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
			for (int j = 0; j < attack_Sort.size(); j++) 
			{
				if (attack_Sort[j] >= 'A' && attack_Sort[j] <= 'Z') //�P�_�O�_�O���a����
				{
					if (Monster[i].Dex < get_Character_Dex(play_Character, attack_Sort[j], 0)) 
					{
						attack_Sort.insert(attack_Sort.begin() + j, 'a' + i);
						break;
					}
				}
				else 
				{
					if (Monster[i].Dex < Monster[attack_Sort[j] - 'a'].Dex) 
					{
						attack_Sort.insert(attack_Sort.begin() + j, 'a' + i);
						break;
					}
				}
				if (j + 1 == attack_Sort.size())
				{
					attack_Sort.push_back('a' + i);
					break;
				}
			}
		}
		//�ˬd�Ƨ�
		for (int i = 0; i < attack_Sort.size(); i++)
		{
			cout << attack_Sort[i] << " ";
		}cout << endl;


		//�ʧ@����
		cout << endl << "Battle Log : " << endl;
		for (int i = 0; i < attack_Sort.size(); i++) 
		{
			if (attack_Sort[i] <= 'Z' && attack_Sort[i] >= 'A')	//������
			{
				if (play_Character[attack_Sort[i] - 'A'].Rest == false) 
				{
					cout << play_Character[attack_Sort[i] - 'A'].ID << "'s round : ";
					int card_num; char UpOrDown;
					cin >> card_num >> UpOrDown;
					cout << play_Character[attack_Sort[i] - 'A'].ID << " : ";
					if (play_Character[attack_Sort[i] - 'A'].Deck[card_num].status == 4) 
					{
						if (UpOrDown == 'u') 
						{
							for (int j = 0; j < play_Character[attack_Sort[i] - 'A'].Deck[card_num].MovementUp.size(); j++) 
							{

							}
						}
						else 
						{
							for (int j = 0; j < play_Character[attack_Sort[i] - 'A'].Deck[card_num].MovementDown.size(); j++)
							{

							}
						}
						play_Character[attack_Sort[i] - 'A'].Deck[card_num].status = 2;
					}
				}
				else 
				{
					cout << play_Character[attack_Sort[i] - 'A'].ID << " : Rest" << endl;
				}
			}
			else //�Ǫ����
			{
				int Card_pos;
				for (int j = 0; j < Monster[attack_Sort[i] - 'a'].Deck.size();j++) 
				{
					if (Monster[attack_Sort[i] - 'a'].Deck[j].status == 2)
						Card_pos = j;
				}
				for (int j = 0; j < Monster[attack_Sort[i] - 'a'].Creature_List.size(); j++) 
				{
					if (Monster[attack_Sort[i] - 'a'].Creature_List[j].active == false)
						continue;
					cout << Monster[attack_Sort[i] - 'a'].Creature_List[j].icon << " : ";
					for (int k = 0; k < Monster[attack_Sort[i] - 'a'].Deck[Card_pos].Movement.size(); k++) 
					{
						cout << Monster[attack_Sort[i] - 'a'].Deck[Card_pos].Movement[k].Movement << " ";
						if (Monster[attack_Sort[i] - 'a'].Deck[Card_pos].Movement[k].Movement == "move")
							cout << Monster[attack_Sort[i] - 'a'].Deck[Card_pos].Movement[k].Move_Command << " ";
						else if (Monster[attack_Sort[i] - 'a'].Deck[Card_pos].Movement[k].Movement == "attack")
							cout << Monster[attack_Sort[i] - 'a'].Deck[Card_pos].Movement[k].Movement_Value << " range:" << Monster[attack_Sort[i] - 'a'].Deck[Card_pos].Movement[k].range << " ";
						else
							cout << Monster[attack_Sort[i] - 'a'].Deck[Card_pos].Movement[k].Movement_Value << " ";
					}
					cout << endl;
				}
			}
		}
		//�^�X����

	}
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
//���o����ӱ���by name
int get_Character_Dex(vector<Character> Play_Character,char name, int num) 
{
	for (int i = 0; i < Play_Character.size(); i++) 
	{
		if (Play_Character[i].ID == name) 
		{
			return Play_Character[i].Dex[num];
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
	//cin >> File_Name;	//��J�a���ɦW
	//File_Map.open(File_Name, ios::in);	//������
	File_Map.open("map1.txt", ios::in);		//���ե�
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
		cout << "	" << Play_Character[i].ID << " : " << Play_Character[i].Dex[0] << " " << Play_Character[i].Dex[1] << endl;
	}
	cout << "monsters:" << endl;
	for (int i = 0; i <Monster.size(); i++)
	{
		cout << "	" << Monster[i].Ethnicity_Name << " : " << Monster[i].Dex << endl;
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