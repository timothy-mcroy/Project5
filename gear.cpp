

#include GEAR_H
//CONSTRUCTOR
gear::gear(int slot)
{
	if (slot > 5)
	{
	    std::cout<<"slot index is out of range in gear.h"<<std::endl;

    }
	// Default should simply represent the slot.
	std::string slN[5] = {"Headband", "Armor", "Weapon", "Shield", "Boots"};
	std::string stN[5]={ "attack", "attack range", "fortitude", "armor", "swiftness"};
	for (int i =0; i< 5;i++)
	{
		slotName.push_back(slN[i]);
		statNames.push_back(stN[i]);
	}

	for (unsigned i=0; i< statNames.size();i++)
		{
			stat_bonuses.push_back(0);
		}

	name.append(slotName[slot]);
	name.append(" slot");
	bool first = true;

	for (unsigned i =0;i< stat_bonuses.size();i++)
		{
			if (stat_bonuses[i]> 0)
			{
				if (first)
				{
				first = false;
				name.append(statNames[i]);
				}
				else
				{
				name.append(" and " + statNames[i]);
				}
			}
		}
}




//CONSTRUCTOR
gear::gear(int level, int slot)
{
	srand(time(NULL));

	std::string slN[5] = {"Headband", "Armor", "Weapon", "Shield", "Boots"};
	std::string stN[6]={ "attack", "attack range", "hitpoints", "armor", "movement speed", "bonus damage"};
	for (int i =0; i< 5;i++)
	{
		slotName.push_back(slN[i]);
	}
	for (int i= 0; i<6; i++)
	{
		statNames.push_back(stN[i]);
	}



	slot = rand() % slotName.size();
	totalBonuses = rand() % (2*level) + 1;  //2 is relatively arbitrary.  After some playtesting, more accurate numbers would be available.
	for (unsigned i=0; i< statNames.size();i++)
		{
			stat_bonuses.push_back(0);
		}
	for (int i =0;i< totalBonuses;i++)
	{
		stat_bonuses[rand() %stat_bonuses.size()] +=1;

	}
	name.append(slotName[slot]);
	name.append(" of ");
	bool first = true;
	for (unsigned i =0;i< stat_bonuses.size();i++)
		{
			if (stat_bonuses[i]> 0)
			{
				if (first)
				{
				first = false;
				name.append(statNames[i]);
				}
				else
				{
				name.append(" and " + statNames[i]);
				}
			}
		}
	std::cout<<"Finishing level constructor"<<std::endl;
}


std::ostream & operator<<(std::ostream & os, gear & item)
{
	os << item.name << ": ";
	for (unsigned i =0; i<item.stat_bonuses.size(); i++)
	{
		if (item.stat_bonuses[i] !=0)
		{
			os << " +"<< item.stat_bonuses[i] << " "<< item.statNames[i];
		}
	}
	return os;
}
