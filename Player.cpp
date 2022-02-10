#include "Player.h"


#ifdef DEBUG
int Player::player_num = 1;
#endif // DEBUG

Player::Player(Slot* loction) :wallet(WALLET_BEGIN), property_num(0), loction(loction), jail(false), property(NULL)
{
#ifdef DEBUG
	char buff[2];
	char* name_tmp = new char[8];
	strcpy(name_tmp, "player#");
	_itoa_s(player_num++, buff, 2, 10);
	strcat(name_tmp, buff);
	name = name_tmp;
#else
	cout << "enter the player name:";
	cin >> name;
	

#endif
}

Player& Player::operator=(const Player&) throw(string)
{
	throw ERROR_COPY_CONSTRTUCTOR;
}

void Player::add_property(Asset& new_asset)
{
	Asset** tmp = new Asset * [property_num + 1];
	for (int i = 0; i < property_num; i++)
	{
		tmp[i] = property[i];
	}
	tmp[property_num++] = &new_asset;
	delete[] property;
	property = tmp;
}

bool Player::buy_asset(Asset& asset)
{
	if (!remove_pawned_years())///chake if he have pawned on some house get false have:true dont have
	{
		cout << left << setfill('-') << setw(100) << "-" << endl; "----You have debts to pay before you buy a house----\n";
		return false;
	}
	
	if (wallet-asset.get_house_price() >= 0) {
		this->wallet -= asset.get_house_price();
		add_property(asset);
		asset.set_ownership(*this); 
		return true;
	}
	else {
		cout<<right<<setw(80)<<setfill(' ')<< "****you dont have enough money try another time****\n"; return false;
	}

}

Player::Player(const Player& other) throw(string)
{
	throw ERROR_COPY_CONSTRTUCTOR;
}


bool Player::operator==(const Player& other)
{
	if (this->name != other.name || this->loction != other.loction || this->wallet != other.wallet || this->property_num != other.property_num) return false;
	for (int i = 0; i < this->property_num; i++)
	{
		if (this->property[i] != other.property[i])return false;
	}
	return true;

}

bool Player::charge_money(int money)
{
	wallet += money;
	if (wallet< 0)
	{
		if (!this->add_pledging())
		{
			cout << right <<setw(80)<<setfill(' ')<<"you dont have enough money or proprty **YOU LOOSE!**" << endl;
			return false;//dont have property to pay(quit)
		}
	}
	if (wallet > 0)
	{
		if (this->remove_pawned_years()) cout <<left<<setw(60)<<setfill(' ')<<"your wallet acaunt whit positive surplus" << endl;//any case have money in wallet try to remove
		return true;
	}

}

bool Player::add_pledging()/// מוסיף שנות משיכון על בתים שלא משועבדים
{
	
	for (int i = 0; i <property_num; i++)
	{
		if (property[i]->get_pawned_years()==0)
		{
			property[i]->set_pawned_year();
			cout << "property:\n"<<*property[i]; cout << "get in pledging" << endl;
			wallet += property[i]->get_house_price();
			if (wallet >= 0) return true;
		}
		
	}
	return false;
}

bool Player::remove_pawned_years()
{
	bool succses=true;
	for (int i = 0; i < property_num; i++)
	{
		bool succes = false;
		if (property[i]->get_pawned_years() != 0)//for case player have proprty pawned 
		{
			if ((int)property[i] <= wallet)
			{
				wallet -= (int)property[i];
				property[i]->set_pawned_year(true);
				succses = true;
			}
		}
		else bool succes = true;
	}
	return succses;/// if return false he have pawned ;
}

Player::~Player()
{
	delete[] property;
}

ostream& operator<<(ostream& out, const Player& p)
{
	out << "player: " << p.name << endl << "current location :" << p.loction;
	return out;
}
