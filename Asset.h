#pragma once
#pragma once
#include "Slot.h" 
using namespace std;
class Player ;
#define INTEREST 20//2000%
enum city_group
{City1 = 1, City2, City3, City4 };
class Asset : public Slot
{
    city_group city;
    const int house_price;
    int rent_price;
    Player* ownership;
    int pawned_years;
public:
    Asset(string name_slot, string city, int house_price, int rent_price);//constructor
    Asset(const Slot& other)throw(string);
    bool operator==(const Slot& other);
    Asset& operator=(const Asset& other)throw(string) { throw ERROR_COPY_CONSTRTUCTOR; }
    const int get_house_price()const{return house_price; }
    Player* get_ownership() const { return ownership; }
    void set_ownership(Player& owner) { this->ownership = &owner;}
    int get_pawned_years() const { return pawned_years; }
    int get_rent_price() const { return rent_price; }
    operator int() const { return pawned_years * house_price * INTEREST;}// caasting to Revenue
    virtual void print(ostream& out)const;
    void remove_ownership() { this->ownership = NULL; pawned_years = 0; }
    void set_pawned_year(bool reset = false);
   virtual ~Asset(){};

};
