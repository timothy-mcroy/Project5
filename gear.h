
#ifndef GEAR_H
#define GEAR_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
struct gear
{
	gear(int slot); //constructs "unequipped" gear piece.
	gear(int level, int slot); //makes gear based on level
	std::string name;


	std::vector<std::string> slotName;
	int totalBonuses;
	std::vector<int> stat_bonuses ; //[attack, attack_range, max_hp, armor, moveSpeed]
	std::vector<std::string> statNames;
	int slot; //determines slotName.

	friend std::ostream & operator<<(std::ostream & os, gear & item);
};

#endif
/*
int main()
{
	gear rock= gear(2);
	gear potato = gear(8, 2);
	std::cout<<rock<<std::endl;

	std::cout<<potato<<std::endl;

}
*/
















