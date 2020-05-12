#include"Game_Manager.h"
#include<fstream>

void main(int argc, char* argv[])
{	
	fstream File_Character, File_Monster;
	bool DEBUG_MODE = false;
	
	//防止編譯錯誤
	if (argc == 4) {
		File_Character.open(argv[1]);
		File_Monster.open(argv[2]);
		DEBUG_MODE = atoi(argv[3]);
	}
	switch (Project_Start())
	{
	case 0:		//開始遊戲
		Main_Game();
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

