#include "GameEngine.h"

GameEngine::GameEngine()
{
	build_borad();
	insert_player();
	make_cards();
}

void GameEngine::build_borad() throw(string)
{
	string slot_type;
	string name;
	ifstream in(FILE_NAME, ios::in);
	if (!in.is_open())throw(FILE_ERROR_OPEN);
	in.seekg(3, in.beg);
	while (!in.eof()) {
		in.ignore(0);
		getline(in, slot_type, ',');
		if (slot_type == "I")
		{
			string i_type;
			getline(in, i_type, ',');
			getline(in, name, '\n');
			board.push_back(new instruction(i_type, name));
#ifdef DEBUG
			cout << *board.back();
#endif // DEBUG
		}
		else if (slot_type == "P")
		{
			string city_type;
			int price_buy, rent_price;
			getline(in, city_type, ',');
			getline(in, name, ',');
			in >> price_buy;
			in.seekg(1, in.cur);
			in >> rent_price;
			in.seekg(2, in.cur);
			board.push_back(new Asset(name, city_type, price_buy, rent_price));
#ifdef DEBUG
			cout << *board.back();

#endif // DEBUG

		}
	}
		in.close();
	
}

void GameEngine::insert_player()
{
#ifndef DEBUG
	int num_of_player;
	cout << "Enter the number of the players:";
	cin >> num_of_player;
	for (int i = 0; i < num_of_player; i++)
	{
		player_array.push_back(new Player(*board.begin()));

	}
#endif // !DEBUG
#ifdef DEBUG
	for (int i = 0; i < SIZE_OF_PLAYER; i++)
	{
		player_array.push_back(new Player(*board.begin()));
	}
#endif // DEBUG
}

void GameEngine::make_cards()
{
	for (int i = 0; i < SIZE_OF_CARDS; i++) {
		int card = rand() % 700 + 1;
		if (card > 350) card = -card % 350;
		Deck.push(card);
	}
}

void GameEngine::move_player(Player& player_now)
{
	list<Slot*>::iterator iter = find(board.begin(), board.end(),player_turn.operator*()->loction);
	int cube = rand() % 6 + 1;
	for (int i = 0; i < cube; i++)
	{
		iter++;
		if (*iter == board.back())
		{
			iter = board.begin();
			start_new_raund();
		}

	}
	player_now.loction = *iter;
}

void GameEngine::start_new_raund()
{
	this->player_turn.operator*()->wallet += WALLET_BEGIN;
	for (int i = 0; i < this->player_turn.operator*()->property_num; i++)
	{
		if (this->player_turn.operator*()->property[i]->get_pawned_years() != 0)this->player_turn.operator*()->property[i]->set_pawned_year();
	}
}

void GameEngine::quit()
{
	Player* tmp = *player_turn;
	for (int i = 0; i < player_turn.operator*()->property_num; i++)
	{
		player_turn.operator*()->property[i]->remove_ownership();
	}
	if (player_turn.operator*() == player_array.back()) {
		player_turn = player_array.begin();
		player_array.pop_back();
		delete tmp;
	}/// extrem case last player
	else {
		player_turn = player_array.erase(player_turn);
		delete tmp;
	}
}

void GameEngine::Asset_slot() throw(string)
{
	char answer;
	int bill;
	Asset* tmp = dynamic_cast <Asset*>(this->player_turn.operator*()->loction);
	if (!tmp) throw(BAD_CASTING);
	if (tmp->get_ownership()==nullptr)//case if dont have onership
	{
		cout << "Would you like to buy this asset?\n If you do press 1 other, you'll click anything :";
#ifdef DEBUG
		answer = '1'; cout << endl;
#endif // DEBUG
#ifndef DEBUG
		cin >> answer; cout << endl;
#endif // !DEBUG

		if (answer == '1' && this->player_turn.operator*()->buy_asset(*tmp))
		{
			cout << right << setw(80) << "****congratulations you buy a new proprty*****" << endl; return;
		}
		else { cout << "the asset stay without ownership continue to the next turn" << endl; return; }
	}
	else
	{
		vector <Player*>::iterator player_owner=find(player_array.begin(), player_array.end(), tmp->get_ownership());
		if (player_owner.operator*() == player_turn.operator*())
		{
			cout << "You landed on an area you own" << endl; return;
		}
		
		cout << "You landed on " << player_owner.operator*()->name<< " property, you need to pay rent" << endl;
		if (!player_turn.operator*()->charge_money(-tmp->get_rent_price()))
		{
			
			bill = player_turn.operator*()->wallet;
			quit();
		}
		else bill = tmp->get_rent_price();
		if (tmp->get_pawned_years() == 0)
		{
			cout << "Player:" << player_owner.operator*()->name << " get money: ";
			player_owner.operator*()->charge_money(bill);
		}
	}

}

void GameEngine::insturction_slot() throw(string)
{
	instruction* tmp = dynamic_cast<instruction*>(player_turn.operator*()->loction);
	if (!tmp) throw(BAD_CASTING);
	if (tmp->get_name_slot() == "Jail")
	{
		player_turn.operator*()->jail = true;
		cout << "Your going for jail until the next turn"<<endl;
	}
	else if (tmp->get_name_slot() == "Get Ticket")
		if (!player_turn.operator*()->charge_money(extract_card()))quit();
		else return;//for case if the player arrived to the first slot alrady realized 

}

bool GameEngine::turn()
{
	char answer;
	bool jail = player_turn.operator*()->jail;
	cout << left << setfill('-') << setw(115) << "-"<<endl;
	cout << right<<setfill(' ')<<setw(60)<<"****now turn of " << player_turn.operator*()->name <<"****"<< endl;
	if (jail) {
		cout << "player:" << player_turn.operator*()->name << " in jail wait for the next raund\n";
		player_turn.operator*()->jail = false;
		return status_game();
	}
#ifndef DEBUG
	cout << "do you want to keep playing ?;-)\n No press 1 otherwhise press somthing: ";
	cin >> answer;
#endif // !DEBUG
#ifdef DEBUG
answer = '2';
#endif // DEBUG


	if (answer == '1') {
		quit();
		if (player_array.size() == 1) return false;
		else if (*player_turn == player_array.back())player_turn = player_array.begin();
		return true;
	}
	cout << "current loction is: "<<endl << *(player_turn.operator*()->loction);
	move_player(*player_turn.operator*());
	cout << "the new loction:"<<endl << *player_turn.operator*()->loction;
	if (strcmp(typeid(*player_turn.operator*()->loction).name(), typeid(Asset).name()) == 0)
	Asset_slot();
	else insturction_slot();
	cout <<endl<< right << setw(70)<<setfill(' ') << "****You've got left in your wallet " << player_turn.operator*()->wallet << " NIS****" << endl;
	return status_game();
}

void GameEngine::start_game()
{
	player_turn = player_array.begin();
	bool play = true;
	while (play) {
		play = turn();
	}
	/*cout << "end of the game !\n";*/
	cout <<right<<setw(60)<<setfill(' ')<<"end of the game ! Player: "<< player_array.front()->name << " WINS!****" << endl;
}

bool GameEngine::status_game()
{
	if (player_array.size() == 1) return false;
	else if (*player_turn == player_array.back())player_turn = player_array.begin();
	else player_turn++;;
	return true;
}

int GameEngine::extract_card()
{
	int card = Deck.front();
	Deck.pop();
	Deck.push(card);
	if (card > 0)cout << "You received a credit: "; else cout << "You charge is :";
	cout << card << endl;
	return card;
}

GameEngine::~GameEngine()
{
	while (board.size() != 0)
	{
		Slot* tmp_slot= board.front();
		board.pop_front();
		delete tmp_slot;
	}
	while (player_array.size() != 0)
	{
		Player* tmp_player = player_array.back();
		player_array.pop_back();
		delete tmp_player;
	}
	
	while (Deck.size()!=0)
	{
		Deck.pop();
	}

	
}

