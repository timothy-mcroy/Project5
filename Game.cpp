/*
 Game.cpp



*/
#include "Game.h"

Game::Game():Player("", 'P'), GameMap(5, '_'), experience(0)
{
	introduction(); //collects information on character.  Starts game
}


unsigned Game::getXP()
{
	return experience;
}

void Game::play()
{

	bool continue_playing = true;
	bool alive = true;
	while(continue_playing)
		{
		alive = create_encounter();
		if (alive)
			{
			std::cout<<"You have surived another round.  Do you dare continue this insane backyard-game?\n";
			continue_playing = yesno();
			}
		continue_playing = continue_playing && alive;
		}
	std::cout<<"Thank you for playing! \n";

}




bool Game::yesno()
{
    std::string answer;
    std::vector <std::string> valid;
	//valid.resize(8);
	valid.push_back("yes"); valid.push_back("Yes"); valid.push_back("y");valid.push_back("Y");
	valid.push_back("n");  valid.push_back("N");valid.push_back("No"); valid.push_back("no");
    unsigned yn;
    yn  = input<std::string>(answer, valid);
    return (yn < valid.size()/2);
}
void Game::introduction()
{
	srand(time(NULL));
	unsigned yn;
	std::cout<<"Welcome to Plains and Pastures!  The Game game with a little sunlight! \n";
	std::cout<<"What is your name? \n";
	input<std::string>(Player.itemName);
	std::cout<<"What a terrible name.  I am so sorry. \n \n \n";
	std::cout<<"Have you played this game before? \n";
	yn =yesno();

	if ( !yn)  //Answer was no
	{
		std::cout<<"Would you like to run through a tutorial? \n";
		yn = yesno();
		if (yn)
        {
            //tutorial();
            std::cout<<"Tutorial coming soon.  Please use the README for now. \n";
        }

	}

    std::cout<<"Alright then.  I suppose you'd like to get to the action! \n";

	play();

}

void Game::level_up()
{
	Player.level_up();
}

void Game::Monster_turn(characterClass<char> &Monster)
{
	bool go_right;
	bool go_up;
	for (unsigned i = 0; i<Monster.get_moveSpeed(); i++)
		{
			if ( Monster.get_attack_range()>=Monster.distance(Player))
				{
					break;
				}
			else
			{
				int shift1=0;
				int shift2=0;
				go_up  = Player.ylocation < Monster.ylocation;
				go_right = Player.xlocation< Monster.xlocation;
				if (go_up && go_right)              //Go North
					shift1 = -1;
				else if (!go_up && go_right)        //Go East
					shift2 = 1;
				else if (go_up && !go_right)        //Go West
					shift2 = -1;
				else                                //Go South
					shift1 = 1;

				GameMap.placeMember(Monster.xlocation+shift1, Monster.ylocation+shift2, Monster);
				wait (1);

			}

		}
		if (Monster.get_attack_range()>=Monster.distance(Player))
        {
            std::cout<<Monster.itemName<<" is attacking you!\n";
            Monster.attack(Player);
        }



}

void Game::addGear(unsigned const & p_level)
{
	gear g = gear(p_level, rand()%5); //randomizing the slot bonus
	std::cout<<"You found a "<<g<<'\n';
	std::cout<<"In comparison, you have a "<<Player.equipped[g.slot];
	if (yesno())//yes is true, no is false
			Player.equip(g);
	else
		std::cout<<"You abandoned the "<<g<<"!\n";
}


void Game::Player_turn(std::vector<characterClass<char> > & monsters)
{
	std::string choice;

	std::vector<std::string> turnOptions;
	turnOptions.push_back("Attack");turnOptions.push_back( "Move"); turnOptions.push_back("Potion");
	std::string symbol1;
	for ( unsigned i =0; i <3;i++)
	{
		std::cout<<i+1<<". )"<<turnOptions[i]<<std::endl;
        symbol1 = static_cast<std::ostringstream*>(&(std::ostringstream()<<(i+1) ) )->str();
		turnOptions.push_back(symbol1);
	}

	input<std::string> (choice, turnOptions);
	bool pmove;
	if (choice == "Attack" || choice == "1" )
		{
		//Attack code
		if (player_Attack(monsters))
        {
            std::cout<<"Would you like to move as well? \n";
            pmove = yesno();
            if(pmove)
                {
                player_Move();
                }
            else
                {
                player_Potion();
                }
            }
        }


	else if (choice == "Move" || choice == "2")
    {
        //Move code
		player_Move();
		std::cout<<"Would you like to attack?";
		pmove = yesno();
		if (pmove)
			player_Attack(monsters);
		else
			player_Potion();
    }

	else
    {
		//Potion code
		//Offer move code
		player_Potion();
		std::cout<<"Would you like to attack as well? \n";
		pmove = yesno();
		if (pmove)
			player_Attack(monsters);
		else
			{
			std::cout<<"Would you like to move? \n";
			pmove = yesno();
			if (pmove)
                player_Move();
			}
    }



}

bool Game::create_encounter()
{
	std::vector<characterClass< char> > monsters;
	unsigned enemies = rand() % (Player.get_Level()) +1;
	//unsigned level_adj = 3-enemies;
	unsigned i;
	char symbol;
	std::string symbol1;
	for (i = 0; i< enemies; i++)
    {
        symbol = (char)(((int)'0')+(i+1));
        symbol1 = static_cast<std::ostringstream*>(&(std::ostringstream()<<(i+1) ) )->str();
        //http://www.cplusplus.com/articles/D9j2Nwbp/
		monsters.push_back(characterClass<char>(symbol1,
                                           Player.get_Level(),
                                          symbol));
    }
	unsigned w  =rand() %10 +11;
	unsigned h   =rand() %10 +11;
	GameMap = gameboard<char>(h, w, '_');
	GameMap.placeMember(w/2, h/2, Player);
    GameMap.printMap();
	unsigned w0;
	unsigned h1;

	for ( i=0; i< monsters.size(); i++)
		{
			do
			{
			w0 = rand() %w ;
			h1 = rand() %h;
			}
			while (w0 == w/2 && h1 == h/2);


			GameMap.placeMember(h1, w0, monsters[i]);

		}

	while(!monsters.empty())
		{
            GameMap.printMap();
			Player_turn(monsters);
			for (i= 0;i< monsters.size();i++)
				{
				    Monster_turn(monsters[i]);
					if (Player.get_currentHP() < 1)
						{
							std::cout<<"Unfortunately, you are dead.  Sorry about that. \n";
							return false;
						}
				}
		}
		std::cout<<"Congratulations!  You beat the encounter!"<<std::endl;
		addXP(75);
		addGear(Player.get_Level());
		return true;


}


void Game::addXP(unsigned xp)
{
	experience += xp;
	while (experience >99)
		{
			experience -=100;
			Player.level_up();

		}
}




bool Game::player_Attack(std::vector<characterClass<char> > &monsters)
	{


		std::string choice;
		std::vector <characterClass<char> > available_enemies;
		std::vector <std::string> enemy_names;
        for (unsigned i= 0; i< monsters.size();i++)
			{
				if(Player.distance(monsters[i]) <= Player.get_attack_range())
				{

					available_enemies.push_back(monsters[i]);
					enemy_names.push_back((monsters[i]).itemName);

				}
			}

		if (enemy_names.empty())
        {
            std::cout<<"No enemies within your attack range. \n";
            return false;
        }
		else
		{
		    std::cout<<"Who do you attack? \n";
		    for(std::vector<std::string>::iterator it = enemy_names.begin();it !=enemy_names.end();++it)
            {
                std::cout<< " " << *it;
            }
            std::cout<<std::endl;
			input(choice, enemy_names);
			unsigned i;
			for ( i = 0; i < monsters.size();i++)
				{
					if (monsters[i].itemName == choice)
						break;
				}
			Player.attack(monsters[i]);
			if(monsters[i].get_currentHP()<0)
			{
			    unsigned x =monsters[i].xlocation+0;
			    unsigned y =monsters[i].ylocation+0;
			    mapObject<char> deadBody = mapObject<char>(x,y,monsters[i].itemName, 'X');
			    GameMap.placeMember(x,y, deadBody);
			    monsters.erase(monsters.begin()+i);
			    std::cout<<"You scored a kill!\n";
			}

			return true;

		}
		//gather choice from Player
		//Player.attack(enemy)


	}

void Game::player_Move()
{
    std::cout<<"Entering player_Move() \n";
	char dirs [] = "NnEeWwSs";
	std::vector< char > directions(dirs, dirs+8);
	char choice;
	unsigned i;
	for (i = 0; i < Player.get_moveSpeed(); i++)
	{
	    std::cout<<"You have "<<Player.get_moveSpeed()-i<<" squares of movement remaining. \n";
		std::cout<<"What direction would you like to move?\n";
		std::cout<<"Options are N, E, W, S \n";
		input <char>(choice, directions);
		int shift1,shift2;
		shift1 = shift2= 0;

		if (choice == 'N' || choice == 'n')
			shift1 =-1;
		else if (choice == 'E' || choice == 'e' )
			shift2 =1;
		else if (choice == 'W'|| choice == 'w')
			shift2 = -1;
		else
			shift1 = 1;
		GameMap.placeMember(Player.xlocation + shift1, Player.ylocation + shift2, Player);
		GameMap.printMap();

	}

}

bool Game::player_Potion()
{
    std::cout<<"You drink a potion, hoping to heal some hitpoints. \n";
	Player.heal(3*Player.get_Level());
	std::cout<<"You are at "<<Player.get_currentHP()<<std::endl;

}




void Game::wait (int seconds)
{
	clock_t beginning = clock() * CLOCKS_PER_SEC;
	clock_t ending    = beginning  +seconds*CLOCKS_PER_SEC;
	while (beginning < ending )
		{
			beginning = clock() * CLOCKS_PER_SEC;
		}
}































