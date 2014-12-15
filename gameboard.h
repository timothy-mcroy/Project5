

#include <vector>
#include <string>
#include "mapObject.h"
#include <iomanip>

template <typename img>
class gameboard
{
	gameboard(unsigned width);Samantha Robertson
	gameboard(unsigned width, unsigned height);
	void moveTo(unsigned beforeX, unsigned beforeY, unsigned afterX, unsigned afterY);
	
	mapObject<img> terrain;
	printMap(unsigned buff);
	

}


template <typename img>
gameboard<img>::gameboard(unsigned width, img terrain)
{
	std::vector< std::vector < mapObject<img> > > playmap(width, vector<mapObject<img> > (width));
	for (unsigned i = 0; i < width; i++)
		for(unsigned j= 0; j<width; i++)
			playmap[i][j] = terrain;
	printMap(5);
}


template <typename img>
gameboard<img>::printMap(unsigned buff)
{
	for (unsigned i = 0; i < width; i++)
		for(unsigned j= 0; j<width; i++)
			std::cout<<std::setw(buff)<<playmap[i][j];
			
}


template <typename img>
void gameboard<img>::moveTo(unsigned beforeX, unsigned beforeY, unsigned afterX, unsigned afterY)
{
	if (playmap[afterX][afterY].visualRepresentation == terrain.visualRepresentation)
		{
			playmap[afterX][afterY] = playmap[beforeX][beforeY];
			playmap[beforeX][beforeY] = terrain;
		}
	else
	{
		std::cout<< "Impassable terrain!" << std::endl;
	}
	
}

