#include"Game_Manager.h"
/*=============main_function==============*/
//�C���D�{��
void Main_Game(fstream& File_Character,fstream& File_Monster)
{
	vector<Character> Base_Character;	//����ҪO�A�A�Ω󤧫�Ыب���M��ɱq�̭��ƻs������
	vector<Ethnicity> Base_Monster;		//�Ǫ��ҪO�A�A�Ω󤧫�ЫةǪ��M��ɱq�̭��ƻs�Ǫ����
	read_Character_Data(File_Character, Base_Character);	//CharacterŪ��
	read_Monster_Data(File_Monster, Base_Monster);			//MonsterŪ��
	//��J����ƶq
	//��J�����T
	//��J�a�ϸ��|
	//Ū���a�ϸ��
	//��ܰ_�l��m
	//�}�l�C��
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
		File_Charactervector.ignore();
		Character Base_type(Charactor_Name,Hp,Hand);		//�s���ҪO
		/*====Ū������ҪO�d����T====*/
		for (int j = 0; j < Deck; j++)	//�@�զ@��Deck�i�d 
		{
			Player_Card newCard;	//�s���d��
			string per_line,upString,downString;string skill_Name;	int skill_Value;
			File_Charactervector >> newCard.ID >> newCard.Dexterity_Value;		//Ū���d����ID �M �ӱ���
			getline(File_Charactervector, per_line);		//�I�U��q��O��
			stringstream interval(per_line);
			getline(interval, upString, '-');getline(interval, downString, '-');		//�H"-"���ɱN��q�r����Φ� �W�������ޯ� �M �U�������ޯ�
			interval.clear(); interval.str("");		//�M��stringstream
			interval << upString;
			while (interval >> skill_Name >> skill_Value)	//��"�Ů�"�N�r����Φ� ��O �M ��	
			{
				Card_Property newMovement;
				newMovement.Movement = skill_Name, newMovement.Movement_Value = skill_Value;
				newCard.MovementUp.push_back(newMovement);
			}
			interval.clear(); interval.str("");		//�M��stringstream
			interval << downString;
			while (interval >> skill_Name >> skill_Value)	//��"�Ů�"�N�r����Φ� ��O �M ��	
			{
				Card_Property newMovement;
				newMovement.Movement = skill_Name, newMovement.Movement_Value = skill_Value;
				newCard.MovementDown.push_back(newMovement);
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
					interval >> newMovement.Movement_Value;
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

/*==============DEBUG_MODE================*/

void get_All_Base_Character_Data(vector<Character> Base_Player) 
{
	for (int i = 0; i < Base_Player.size(); i++)
	{
		cout << "����W�G" << Base_Player[i].Character_name << "  ���� HP�G" << Base_Player[i].Hp << " �����P�ơG" << Base_Player[i].Hand << endl << "�ޯ�d�G" << endl;
		for (int j = 0; j < Base_Player[i].Deck.size(); j++)
		{
			cout <<"ID�G	"<< Base_Player[i].Deck[j].ID << "	�ӱ��ȡG	" << Base_Player[i].Deck[j].Dexterity_Value << "	�W�G";
			for (int k = 0; k < Base_Player[i].Deck[j].MovementUp.size(); k++)
				cout << Base_Player[i].Deck[j].MovementUp[k].Movement << " " << Base_Player[i].Deck[j].MovementUp[k].Movement_Value << " ";
			cout << " | �U�G";
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
		cout << "�رڦW�G" << Base_Monster[i].Ethnicity_Name
			<< " ���q�ͩR�G" << Base_Monster[i].Creature_List[0].Hp
			<< " ���q�����G" << Base_Monster[i].Creature_List[0].Damage
			<< " ���q�d��G" << Base_Monster[i].Creature_List[0].Range
			<< " �׭^�ͩR�G" << Base_Monster[i].Creature_List[0].Elite_Hp
			<< " �׭^�����G" << Base_Monster[i].Creature_List[0].Elite_Damage
			<< " �׭^�d��G" << Base_Monster[i].Creature_List[0].Elite_Range << endl;
		cout << "�ޯ�d�G" << endl;
		for (int j = 0; j < 6; j++) 
		{
			cout << "ID�G" << Base_Monster[i].Deck[j].ID << "	�ӱ��ȡG" << Base_Monster[i].Deck[j].Dexterity_Value << "	";
			for (int k = 0; k < Base_Monster[i].Deck[j].Movement.size(); k++) 
			{
				cout << Base_Monster[i].Deck[j].Movement[k].Movement<<" ";
				if (Base_Monster[i].Deck[j].Movement[k].Movement == "move")
					cout << Base_Monster[i].Deck[j].Movement[k].Move_Command << " ";
				else
					cout << Base_Monster[i].Deck[j].Movement[k].Movement_Value << " ";
			}
			cout <<"���~�лx�G"<< Base_Monster[i].Deck[j].Shuffle_Mark << endl;
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