/*
Timothy McRoy 
characterClass.h

*/



#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include "mapObject.h"
#include "gear.h"
#include <vector>
#include <iostream>
#include "input.h"
#include "gear.h"
template <typename img>
class characterClass:  protected mapObject <img>
{
	private:
		std::vector<gear> equipped; //Head, Weapon, Shield, Shoes, Amulet
		unsigned current_hp;
		unsigned max_hp;
		unsigned moveSpeed;
		unsigned level;
		unsigned initiative;
		unsigned attack_range;
		unsigned armor;
		unsigned attack;
		unsigned damage;
		std::vector<action> turnOptions;
	protected:
		virtual void level_up();
		virtual action attack();
		int get_attack_range()  const;
		std::string attack_dialogue;
	
	public:
		//CONSTRUCTORS
		characterClass();
		characterClass(int lvl);
		
		
		void equip( gear & g);
		
		virtual std::string turn();
		int get_armor()  const;
		int get_moveSpeed()  const;
		int get_maxHP() const;
		int get_currentHP() const;
		int get_Level()  const;
		void heal(unsigned hp);
		void defend(unsigned attack_val, unsigned damage);
		
		virtual int roll_initiative()  const;
		
		void moveTo( mapObject target );
		
		void displayGear() const;
		virtual void attack() const;
}

//CONSTRUCTOR
template <typename img> 
characterClass<img> ::characterClass(): max_hp(6), moveSpeed(6), level(1), 
attack_range(1), armor(10), current_hp(max_hp), initiative(0), attack_dialogue(itemName + " punches ")
{
	
}

//CONSTRUCTOR
template <typename img> 
characterClass<img> ::characterClass(int lvl):
level(lvl), max_hp(6*lvl), moveSpeed(6), armor(10+lvl), current_hp(max_hp), initiative(lvl), attack_dialogue(itemName + " punches ")
{

}


template <typename img> 
std::string characterClass<img> ::turn()
{
	std::string record;
	int choice;
	std::vector<int> menuOptions;
	std::cout<< "What would you like to do? "<<std::endl;
	for (std::vector<action>::size_type i = 0; i !=turnOptions.size();i++)
		{
			std::cout<<i+1<<". )"<<turnOptions[i]<<std::endl;
			menuOptions.push_back(i+1);
		}
		
	input ( choice, menuOptions);
	turnOptions[i]();
}



//ACCESS FUNCTIONS
template <typename img>
int characterClass<img> :: get_armor() const
{
	return armor;
}

template <typename img>
int characterClass<img>::get_moveSpeed() const
{
	return moveSpeed;	
}

template <typename img>
int characterClass<img>::get_maxHP() const
{
	return max_HP;
}

template <typename img>
int characterClass<img>::get_currentHP() const
{
	return current_hp;
}

template <typename img>
int characterClass<img>::get_Level() const
{
	return level;
}

template <typename img>
std::string displayGear() const
{
	for (unsigned i =0; i< std::sizeof(equipped)
}

//END ACCESS FUNCTIONS


template <typename img>
void characterClass<img>::heal(unsigned hp)
{
	//healing never goes over max_hp
	current_hp = std::min(current_hp+hp, max_HP);	
}

template <typename img>
void characterClass<img>::defend(unsigned attack_val, unsigned damage)
{
	if (attack_val < armor)
	{
		std::cout<<"The attack misses!"<<std::endl;
		return;
	}
	else
	{
		std::cout<<"The attack hits for "<<damage<<" damage!"<<std::endl;
		current_hp -=damage;
	}
}

template <typename img>
int characterClass<img>::roll_initiative() const
{
	return (rand() % 20 +1) + initiative;
}

template <typename img>
void characterClass<img>::moveTo( mapObject target )
{
	
	
	xlocation = target.xlocation;
	ylocation = target.ylocation;
	std::cout<<"You've call a function that doesn't work like it should. You should finish this when you are done with the map implementation"<<std::endl;
}


template <typename img>
void characterClass<img>::displayGear() const
{
	std::string result = string();
	for (std::vector<gear>::iterator it = equipped.begin(); it != equipped.end(); ++it)
	{
		std::cout<< *it<<std::endl;	
	}
	
	return;
}


template <typename img>
void characterClass<img>::unequip(unsigned index)
{
	gear g 				 = equipped[index];
	attack 				-= g.stat_bonuses[0];
	attack_range 		-= g.stat_bonuses[1];
	current_hp			-= g.stat_bonuses[2];
	max_HP 			-= g.stat_bonuses[2];
	armor 				-= g.stat_bonuses[3];
	moveSpeed		-= g.stat_bonuses[4];
	damage 			-= g.stat_bonuses[5];
	equipped[index]   = gear(g.slot);	
}


template <typename img> 
void characterClass<img>::equip( gear & g)
{
	unequip(g.slot);
	attack 				+= g.stat_bonuses[0];
	attack_range 		+= g.stat_bonuses[1];
	current_hp			+= g.stat_bonuses[2];
	max_HP 			+= g.stat_bonuses[2];
	armor 				+= g.stat_bonuses[3];
	moveSpeed 		+= g.stat_bonuses[4];
	damage				+= g.stat_bonuses[5];
	equipped[index] 	  = g;
}

template <typename img>
void characterClass<img>::attack(characterClass enemy) const
{
	if (distance > moveSpeed)
	{
		std::cout<<"Enemy out of range"<<std::endl;
	}
	else
	{
		srand(time(NULL));
		unsigned die = rand()% 20 +1;
		enemy.defend(die+attack, damage);
	}
}


template <typename img>
void characterClass<img>::level_up()
{
	std::cout<<"Congratulations! You have leveled up! You are now level "<<level<<"."<<std::endl;
	
	current_hp += 5
	max_HP += 5
	damage +=1
	std::cout<<"You have gained 5 hp and 1 damage!"<<std::endl;
}

#endif
























