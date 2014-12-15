

#include <vector>
#include <string>
#include "mapObject.h"
#include <iomanip>
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

template <typename img>
class gameboard
{
	gameboard(unsigned width);
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
			playmap[i][j] = mapObject(i, j, "terrain", terrain.visualRepresentation);

	printMap(5);
}


template <typename img>
gameboard<img>::printMap(unsigned buff)
{
	for (unsigned i = 0; i < width; i++)
		for(unsigned j= 0; j<width; i++)
			std::cout<<std::setw(buff)<<playmap[i][j].visualRepresentation;

}


template <typename img>
void gameboard<img>::moveTo(unsigned beforeX, unsigned beforeY, unsigned afterX, unsigned afterY)
{
	if (playmap[afterX][afterY].visualRepresentation == terrain.visualRepresentation)
		{
			playmap[afterX][afterY] = playmap[beforeX][beforeY];
			playmap[afterX][afterY].moveTo(afterX, afterY);
			playmap[beforeX][beforeY] = terrain;
		}
	else
	{
		std::cout<< "Impassable terrain!" << std::endl;
	}
}
#endif // GAMEBOARD_H


int main ()
{

}
