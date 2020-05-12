#include"Game_Manager.h"
/*=============main_function==============*/
//遊戲主程式
void Main_Game(fstream& File_Character,fstream& File_Monster)
{
	vector<Character> Player;
	get_Character_Data(Player);
}

void get_Character_Data(vector<Character> player)
{
	int Charactor_number = 0;
	cout << "請輸入出場角色數量:" << endl;
	cin >> Charactor_number;
}

/*==============DEBUG_MODE================*/

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