#include"Monster.h"
#include<fstream>

int main(int argc, char* argv[])
{	
	fstream File_Character, File_Monster;
	bool DEBUG_MODE = false;
	
	//防止編譯錯誤
	if (argc == 4) {
		File_Character.open(argv[1]);
		File_Monster.open(argv[2]);
		DEBUG_MODE = atoi(argv[3]);
	}
}

