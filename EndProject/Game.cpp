#include"Game_Manager.h"
/*=============main_function==============*/
//�C���D�{��
void Main_Game(fstream& File_Character,fstream& File_Monster)
{
	vector<Character> Player;
	get_Character_Data(Player);
}

void get_Character_Data(vector<Character> player)
{
	int Charactor_number = 0;
	cout << "�п�J�X������ƶq:" << endl;
	cin >> Charactor_number;
}

/*==============DEBUG_MODE================*/

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