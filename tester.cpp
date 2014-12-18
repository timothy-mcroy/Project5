#include <utility>
#include <iomanip>
#include "characterClass.h"
#include "gameboard.h"
#include "Game.h"
#include "Game.cpp"
int main()
{
    mapObject<char> bean = mapObject<char>(3,5);
    mapObject<char> sprout = mapObject<char>(5,5,"sprout",'X');

	mapObject <char> peanut = mapObject<char>( 3,4);
	mapObject <char>  creepything = mapObject<char>(5,6,"Creepything", '_');
	std::cout<<peanut.itemName<<std::endl;
	std::cout<< creepything.itemName<<std::endl;
	std::cout<< creepything.distance(peanut)<<std::endl;



    gameboard<char> eightbynine = gameboard<char>(10,10,creepything.visualRepresentation);
    eightbynine.placeMember(5,5,sprout);
    std::cout<<"\n\nFinished playmap[5][5] assignment\n"<<std::endl;
    eightbynine.printMap(2);
    //eightbynine.moveTo(5,5,3,3);
    //std::cout<<eightbynine.playmap[5][5].itemName<<std::endl;
    eightbynine.printMap(2);
    std::cout<<std::endl;




    //std::cout<<gear(2)<<"\n";

    characterClass<char> jordan =characterClass<char>("jordan",5, 'J');
    characterClass<char> mike =characterClass<char>("mike",4, 'M');
    std::cout<<jordan.itemName<<std::endl;
    eightbynine.placeMember( 8,2, jordan);
    jordan.displayGear();

    std::list<std::string> names = eightbynine.getNames();
    for (std::list<std::string>::iterator it=names.begin(); it != names.end(); ++it)
        std::cout << ' ' << *it;
    eightbynine.placeMember(5,4, mike);
    std::cout<<"Mikes damage is " <<mike.get_damage()<<"\n";
    mike.displayGear();
    std::cout<<"Jordan has "<<jordan.get_currentHP()<<" hp our of "<<jordan.get_maxHP()<<std::endl;
    std::cout<<"Mike has" <<mike.get_currentHP() << " hp out of "<<mike.get_maxHP()<<std::endl;
    mike.attack(jordan);

    std::cout<<"Jordan has "<<jordan.get_currentHP()<<" hp our of "<<jordan.get_maxHP()<<std::endl;
    std::cout<<"Mike has" <<mike.get_currentHP() << " hp out of "<<mike.get_maxHP()<<std::endl;
    mike.attack(jordan);
    std::cout<<"Jordan has "<<jordan.get_currentHP()<<" hp out of "<<jordan.get_maxHP()<<std::endl;
    std::cout<<"Mike has" <<mike.get_currentHP() << " hp out of "<<mike.get_maxHP()<<std::endl;
    //std::pair<unsigned,unsigned> stuffFinder = eightbynine.findCoord("stuff");
    //std::cout<<stuffFinder.first<<" , "<<stuffFinder.second<<std::endl;
    std::cout<<"Mike rolls initiative at "<<mike.roll_initiative()<<std::endl;


    names = eightbynine.getNames();
    for (std::list<std::string>::iterator it=names.begin(); it != names.end(); ++it)
            std::cout << ' ' << *it;
    Game first;
    return 0;
}
