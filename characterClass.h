/*
Timothy McRoy
characterClass.h

*/




#include "gear.h"
#include <vector>
#include <iostream>
#include "input.h"
#include "mapObject.h"
#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H


template <typename img>
class characterClass:  public mapObject <img>
{
	private:


		unsigned   moveSpeed, level, initiative, attack_range, armor, attack_bonus, damage;
		int max_hp, current_hp;
		std::string attack_dialogue;

	public:
		//CONSTRUCTORS
		std::vector<gear> equipped; //Head, Weapon, Shield, Armor, Shoes
		characterClass(std::string characterName, img Fig);
		characterClass(std::string characterName, unsigned lvl, img Fig);
        virtual ~characterClass();
        virtual void level_up();
		void equip( gear  g);

		//virtual std::string turn();
		unsigned get_attack_range()  const;
		unsigned get_armor()  const;
		unsigned get_moveSpeed()  const;
		unsigned get_maxHP() const;
		int get_currentHP() const;
		unsigned get_Level()  const;
		unsigned get_damage() const;
		void heal(int hp);
		void defend(unsigned attack_val, unsigned damage);
        void unequip(unsigned index);//index of equipped
		virtual int roll_initiative()  const;

		void displayGear() const;
		virtual void attack(characterClass<img> &enemy) const;
};

//CONSTRUCTOR
template <typename img>
characterClass<img> ::characterClass(std::string characterName, img Fig):
max_hp(6),
current_hp(max_hp),
moveSpeed(6),
level(1),
initiative(0),
attack_range(1),
armor(10),
attack_bonus(0),
damage(4)
{
    srand(time(NULL));
    mapObject<img>::impassable              = true;
    mapObject<img>::visualRepresentation    = Fig;
    mapObject<img>::itemName                = characterName;
    attack_dialogue                         = mapObject<img>::itemName + " punches.";
    std::cout<<"in characterClass Constructor.  About to enter, what I suspect, is the break in code"<<std::endl;
    for (unsigned i= 0; i<5; i++) //assuming 5 gear slots
    {
        equipped.push_back(gear(i));
        //std::cout<<"The item should have just printed."<<std::endl;
    }
    for (unsigned i=0; i<5;i++)
    {
        equip(equipped[i]);
    }

}

//CONSTRUCTOR
template <typename img>
characterClass<img> ::characterClass(std::string characterName, unsigned lvl, img Fig):
max_hp(5*lvl),
current_hp(max_hp),
moveSpeed(6),
level(lvl),
initiative(lvl),
attack_range(1),
armor(10+lvl),
attack_bonus(lvl),
damage (4)
{
    srand(time(NULL));
    mapObject<img>::visualRepresentation    = Fig;
    mapObject<img>::itemName                = characterName;
    attack_dialogue                         = mapObject<img>::itemName + " punches.";
    for (unsigned i= 0; i<5; i++)  //assuming 5 gear slots
    {

        equipped.push_back(gear(i));
    }
    for (unsigned i=0; i<5;i++)
    {
        equip(equipped[i]);
    }

}


//DESTRUCTOR
template <typename img>
characterClass<img>::~characterClass()
{

}

//ACCESS FUNCTIONS
template <typename img>
unsigned characterClass<img> :: get_armor() const
{
	return armor;
}

template <typename img>
unsigned characterClass<img>::get_moveSpeed() const
{
	return moveSpeed;
}

template <typename img>
unsigned characterClass<img>::get_maxHP() const
{
	return max_hp;
}

template <typename img>
int characterClass<img>::get_currentHP() const
{
	return current_hp;
}

template <typename img>
unsigned characterClass<img>::get_Level() const
{
	return level;
}

template <typename img>
unsigned characterClass<img>::get_damage() const
{
    return damage;
}

template <typename img>
void characterClass<img>::displayGear() const
{
    std::cout<<"You have a ";
	for (unsigned i =0; i< equipped.size()-1;i++)
        {
            std::cout<<equipped[i]<<", ";
            if (i%2 ==0)
                std::cout<<std::endl;
        }
    std::cout<< "and a "<<equipped[equipped.size()-1]<<"."<<std::endl;
}

//END ACCESS FUNCTIONS


template <typename img>
void characterClass<img>::heal(int hp)
{
	//healing never goes over max_hp
	std::cout<<max_hp-std::min(current_hp+hp, max_hp)<< "hp healed.";
	current_hp = std::min(current_hp+hp, max_hp);
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


/*
template <typename img>
std::string characterClass<img> ::turn()
{
	std::string record;
	int choice;
	std::vector<int> menuOptions;
	std::cout<< "What would you like to do? "<<std::endl;
	for (unsigned i = 0; i < turnOptions.size();i++)
		{
			std::cout<<i+1<<". )"<<turnOptions[i]<<std::endl;
			menuOptions.push_back(i+1);
		}

	input ( choice, menuOptions);
	turnOptions[choice]();
}
*/


template <typename img>
void characterClass<img>::unequip(unsigned index)
{

	gear g 			 = equipped[index];


	attack_bonus	-= g.stat_bonuses[0];

	attack_range 	-= g.stat_bonuses[1];
	current_hp		-= g.stat_bonuses[2];
	max_hp 			-= g.stat_bonuses[2];
	armor 			-= g.stat_bonuses[3];
	moveSpeed		-= g.stat_bonuses[4];
	damage 			-= g.stat_bonuses[5];
	equipped[index]  = gear(g.slot);
}


template <typename img>
void characterClass<img>::equip( gear  g)
{
	unequip(g.slot);
	attack_bonus		+= g.stat_bonuses[0];
	attack_range 		+= g.stat_bonuses[1];
	current_hp			+= g.stat_bonuses[2];
	max_hp 			    += g.stat_bonuses[2];
	armor 				+= g.stat_bonuses[3];
	moveSpeed 		    += g.stat_bonuses[4];
	damage				+= g.stat_bonuses[5];
	equipped[g.slot] 	 = g;
}

template <typename img>
void characterClass<img>::attack(characterClass<img> &enemy) const
{
	if (mapObject<img>::distance(enemy) > moveSpeed)
	{
		std::cout<<"Enemy out of range"<<std::endl;
	}
	else
	{

		unsigned die = rand()% 20 +1;
		std::cout<<"The die shows a "<<die<<"\n";
		enemy.defend(attack_bonus + die, damage);
	}
}


template <typename img>
void characterClass<img>::level_up()
{
    level+=1;
	std::cout<<"Congratulations! You have leveled up! You are now level "<<level<<"."<<std::endl;

	max_hp += 5;
	heal(5);
	damage +=1;
	std::cout<<"You have gained 5 hp and 1 damage!"<<std::endl;
}


#endif























