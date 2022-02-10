#include "instruction.h"


instruction::instruction(string type, string name):Slot(name)
{
	type == "J" ? this->type = jail : type == "S" ? this->type = start : this->type = Get_Ticket;
}

void instruction::print(ostream& out) const
{
#ifdef DEBUG
	/*cout << "print for DEBUG INSTRUCTION :\n";*/
#endif // DEBUG
	out << "instruction type: "<<(type == jail ? " jail " : type == start ? " start " : " Get Ticket ")<<endl;
	cout << left << setfill('-') << setw(115) << "-" << endl;
}

void instruction::go_for_jail(Player& player)
{
	cout << "you are landed on a jail slot GO FOR JAIL!" << endl;
	player.go_for_jail();
}



