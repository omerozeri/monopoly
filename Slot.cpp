#include "Slot.h"
int Slot::num_of_slot = 0;
bool Slot::operator==(const Slot& other) const
{
	return (this->name == other.name && this->id_slot == other.id_slot);
}
Slot::Slot(const Slot& other) throw(string) :id_slot(0)
{
	throw ERROR_COPY_CONSTRTUCTOR;
}
Slot::Slot(string name):name(name),id_slot(++num_of_slot)
{}

ostream& operator<<(ostream& out, const Slot& b)
{

	out << left << setw(25) << setfill(' ') << "Slot number:";
	out << left << setw(25) << setfill(' ') << "slot name:" << endl << endl;

	out << left << setw(25) << setfill(' ') << b.id_slot;
	out << left << setw(25) << setfill(' ') << b.name << endl << endl;
	b.print(out);
	return out;
}
