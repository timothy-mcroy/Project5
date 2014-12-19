#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "characterClass.h"
#include "gameboard.h"
#include "input.h"
#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game();
	//Game( filename);  // when we want to load a saved game.
    characterClass<char> Player;
    unsigned getXP();
    void play();
	void encounter(unsigned level);

private:

    bool yesno();
	void introduction();
	gameboard<char> GameMap;
    bool create_encounter();
    void level_up();
    void Monster_turn(characterClass<char> &Monster);
    void Player_turn(std::vector<characterClass<char> > & monsters);
    unsigned experience;
    void addXP(unsigned xp); //checks xp to see if leveling is needed.
    void wait (int seconds);
    void addGear(const unsigned & level);
    void player_Move();
    bool player_Potion();
    bool player_Attack(std::vector<characterClass<char> > & monsters);

};

#endif
