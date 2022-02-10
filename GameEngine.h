#pragma once
#include<queue>
#include<list>
#include"Slot.h"
#include"Player.h"
#include"instruction.h"
#include"Asset.h"
#include <fstream>
#include<algorithm>
#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<exception>
#include<typeinfo>
using namespace std;
#define FILE_NAME "board.txt"
#define SIZE_OF_PLAYER 4
#define SIZE_OF_CARDS 30
#define FILE_ERROR_OPEN "ERROR the file text did'nt open\n"
#define BAD_CASTING "ERROR bad dynamic cast\n"
class GameEngine
{	vector<Player*> player_array;
	vector<Player*>::iterator player_turn;
	queue<int>Deck;
	list<Slot*> board;
public:
	GameEngine();
	void build_borad()throw(string);
	void insert_player();
	void make_cards();
	void move_player(Player& player_now);
	void start_new_raund();
	void quit();
	void Asset_slot()throw(string);
	void insturction_slot()throw(string);
	bool turn();
	void start_game();
	bool status_game();
	int extract_card();
	~GameEngine();
};

