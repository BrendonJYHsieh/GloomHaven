#include"Game_Manager.h"

void main(int argc, char* argv[])
{	
	fstream File_Character, File_Monster, File_Map;
	int DEBUG_MODE = 0;		//0:未開啟	1:開啟	2:UI_Mode
	
	//防止編譯錯誤
	if (argc == 4) {
		File_Character.open(argv[1]);
		File_Monster.open(argv[2]);
		DEBUG_MODE = atoi(argv[3]);
	}


	/*====測試時使用====*/
	File_Character.open("character1.txt", ios::in);
	File_Monster.open("monster1.txt", ios::in);
	std::cin >> DEBUG_MODE;
	system("cls");


	switch (DEBUG_MODE)
	{
	case 0:
		Main_Game(File_Character, File_Monster, File_Map,DEBUG_MODE);
		break;
	case 1:
		Main_Game(File_Character, File_Monster, File_Map, DEBUG_MODE);
		break;
	case 2:
		Main_Game_UI(File_Character, File_Monster, File_Map);
		break;
	}
	
}

