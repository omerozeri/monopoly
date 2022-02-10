#pragma once
#pragma once
#include <string>
#include <iostream>
#include<algorithm>
#include<iomanip>
#define ERROR_COPY_CONSTRTUCTOR "DONT USE COPY CONSTRUCTOR \n"
using namespace std;
class Slot
{
	const string name;
	const int id_slot;
public:
	virtual bool operator==(const Slot& other)const;
	virtual void print(ostream& out)const = 0;
	Slot(const Slot& other)throw(string);
	Slot& operator=(const Slot& other)throw(string) { throw ERROR_COPY_CONSTRTUCTOR; }
	friend ostream& operator<<(ostream& out, const Slot& b);
	static int num_of_slot;
	Slot(string name);
	string get_name_slot()const { return name; }
	const int get_id_slot()const { return id_slot; }
	virtual ~Slot() {};
};

