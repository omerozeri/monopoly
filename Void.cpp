#include"GameEngine.h"
#include<crtdbg.h>

void main()
{
	srand(std::time(nullptr));
	cout << right << setw(70) << "******welcome to monopoly******" << endl;
	cout << left << setfill('-') << setw(110) << "-" << endl;
	try {
		GameEngine game;
		game.start_game();
	}
	catch (exception& e) { cout << e.what(); }

}