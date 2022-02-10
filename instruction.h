#pragma once
#include "Slot.h"
#include "Player.h"

enum instruction_type{jail=1,start,Get_Ticket};
class instruction :public Slot
{
	
	instruction_type type;

public:
	
	instruction(string type, string name);
	instruction(Slot& other)throw(string) :Slot(other){throw ERROR_COPY_CONSTRTUCTOR; }
	instruction& operator=(const instruction& other)throw(string) { throw ERROR_COPY_CONSTRTUCTOR; }
	virtual void print(ostream& out)const;
	void go_for_jail(Player& player);
	virtual~instruction(){}
	
};

