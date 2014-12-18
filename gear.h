
#ifndef GEAR_H
#define GEAR_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

struct gear
{
	gear(unsigned  slot); //constructs "unequipped" gear piece.
	gear(unsigned level, unsigned slot); //makes gear based on level

    gear(const gear& other); //Copy constructor
    std::string name;
	std::vector<std::string> slotName;
	int totalBonuses;
	std::vector<int> stat_bonuses ; //[attack, attack_range, max_hp, armor, moveSpeed]
	std::vector<std::string> statNames;
	int slot; //determines slotName.

	friend std::ostream & operator<<(std::ostream & os, const gear & item);
};

#include "gear.cpp"
#endif

















