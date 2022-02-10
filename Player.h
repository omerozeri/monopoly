#pragma once
#include <string>
#include <iostream>
#include"Asset.h"
#include"Slot.h"
#include<algorithm>
#include<list>
#include<vector>
#include<iterator>
#include "GameEngine.h"
#define WALLET_BEGIN 350
#ifdef DEBUG 
static int  player_num=1;
#endif
using namespace std;
class Asset;
class Player
{
	string name;
	int wallet;
	Slot* loction;
	Asset** property;
	int property_num;
	bool jail; 
	friend class GameEngine;
public:
	
#ifdef DEBUG
	int static player_num;
#endif // DEBUG
	Player(Slot* loction)throw(string);
	Player& operator=(const Player&) throw(string);
	void add_property(Asset& new_asset);
	bool buy_asset(Asset& asset);// try to buy new asset to player
	Player(const Player& other)throw(string);
	friend ostream& operator<<(ostream& out, const Player& p);
	bool operator==(const Player& player);
	bool charge_money(int money);
	bool add_pledging();
	string get_name() { return name; }
	void go_for_jail() { jail = true;}
	bool is_in_jail(){ return jail; }
	bool remove_pawned_years();
	~Player();
	
};



