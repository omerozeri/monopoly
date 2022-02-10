#include "Asset.h"

Asset::Asset(string name_slot, string city, int house_price, int rent_price) :Slot(name_slot),house_price(house_price),rent_price(rent_price)
{
	this->pawned_years = 0;
	this->ownership = nullptr;
	city == "City1" ? this->city = City1 : city == "City2" ? this->city = City2 : city == "City3" ? this->city = City3 : this->city = City4;

}

Asset::Asset(const Slot& other) throw(string):Slot(other),house_price(0)
{
	throw ERROR_COPY_CONSTRTUCTOR;
}

bool Asset::operator==(const Slot& other)
{
	if (!Slot::operator==(other)) return false;
	const Asset* tmp = dynamic_cast<const Asset*>(&other);
	return(this->city == tmp->city && this->house_price == tmp->house_price && this->ownership == tmp->ownership && this->pawned_years == tmp->pawned_years);
}

void Asset::print(ostream& out) const
{
#ifdef DEBUG
	//cout << "print for DEBUG CITY:\n"; /*<< *this;*/
#endif // DEBUG

	out << left << setfill('-') << setw(115) << "-" << endl;
	out << left << setw(25) << setfill(' ') << "City Group:";
	out << left << setw(25) << setfill(' ') << "House Price:";
	out << left << setw(25) << setfill(' ') << "Rent Price:";
	out << left << setw(25) << setfill(' ') << "pawned_years:";

	out << left << setw(93) << setfill(' ') << "" << endl << endl;

	out << left << setw(25) << setfill(' ') << (city == City1 ? "Group 1" : city == City2 ? " Group 2" : city == City3 ? "Group 3" : "Group 4");
	out << left << setw(25) << setfill(' ') << house_price;
	out << left << setw(25) << setfill(' ') << rent_price;
	if (pawned_years != 0) { out << "The house is extended for :" << pawned_years << endl << endl; }
	else { out << "No Pawn" << endl << endl; }
}

void Asset::set_pawned_year(bool reset)
{
	if (reset)pawned_years = 0;
	else pawned_years++;
}



