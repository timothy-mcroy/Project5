
#include <utility>
#include <list>
#include <vector>
#include <string>
#include "mapObject.h"
#include <iomanip>
#ifndef GAMEBOARD_H
#define GAMEBOARD_H


template <typename img>
class gameboard
{
    public:
        gameboard<img>(unsigned width, img terrain);
        gameboard<img>(unsigned width, unsigned height, img terrain);
        //void moveTo(unsigned beforeX, unsigned beforeY, unsigned afterX, unsigned afterY);

        void printMap(unsigned buff=2);

        std::list< std::string > getNames();
        std::pair<unsigned,unsigned> findCoord(std::string iName);
        void placeMember(unsigned x, unsigned y, mapObject<img> &character);
    private:
        void moveTo(mapObject<img> &before, mapObject<img> &after);
        std::vector< std::vector < mapObject<img> > > playmap;
        img m_terrain;
        unsigned m_width;
        unsigned m_height;
};





template <typename img>
gameboard<img>::gameboard(unsigned width, img terrain): m_width(width), m_height(width),playmap(width, std::vector<mapObject<img> > (width)), m_terrain(terrain)
{
	//std::vector< std::vector < mapObject<img> > > playmap(width, std::vector<mapObject<img> > (width));
	for (unsigned i = 0; i < m_width; i++)
		for(unsigned j= 0; j<m_height; j++)
			playmap[i][j] = mapObject<img>(i, j, "terrain", m_terrain);
}

template <typename img>
gameboard<img>::gameboard(unsigned width, unsigned height, img terrain)
: m_width(width), m_height(height),playmap(width, std::vector<mapObject<img> > (height)), m_terrain(terrain)
{
    //std::vector< std::vector < mapObject<img> > > playmap(width, std::vector<mapObject<img> > (height));
	for (unsigned i = 0; i < m_width; i++)
        for(unsigned j = 0; j < m_height; j++)
            playmap[i][j] = mapObject<img>(i, j, "terrain", m_terrain);

    printMap();
}

template <typename img>
void gameboard<img>::printMap(unsigned buff)
{
    std::cout<<std::endl;
	std::cout<<std::setw(buff+2)<<" ";
	for (unsigned i = 0; i < m_height; i++)
        std::cout<<std::setw(buff)<<i;
    std::cout<<std::endl;
	for (unsigned i = 0; i < m_width; i++)
    {
        std::cout<<std::endl<<std::setw(buff+2)<<i;
		for(unsigned j= 0; j<m_height; j++)
        {
            std::cout<<std::setw(buff)<<playmap[i][j].visualRepresentation;
        }
    }
    std::cout<<std::endl;

}

template <typename img>
void gameboard<img>::moveTo(mapObject<img> &before, mapObject<img> &after)
{
    //This will work poorly when moving from different types of impassable terrain.  A more refined implementation would have two layers (one for player location), one for terrain.
    unsigned bx, by, ax, ay;
    if (after.impassable)
    {
        bx=before.xlocation;
        by=before.ylocation;
        ax=after.xlocation;
        ay=after.ylocation;
        before.moveTo(after);
        playmap[bx][by] = mapObject<img>(bx, by, "terrain", m_terrain);
        playmap[ax][ay] = before;

    }
    else
    {
        std::cout<<"Impassable object!"<<std::endl;
    }
}



template <typename img>
std::list<std::string> gameboard<img>::getNames()
{

    //There's clearly room for efficiency improvements by moving the name tracking to be integrated with other operations
    std::list <std::string> objectNames;
    for (unsigned i =0; i< m_height;i++)
        for (unsigned j=0; j< m_width;j++)
        {
            objectNames.push_back(playmap[i][j].itemName);
        }


    objectNames.remove("terrain");
    return objectNames;
}


template <typename img>
std::pair<unsigned, unsigned> gameboard<img>::findCoord(std::string iName)
{

    //A more efficent way would be to keep a hash map of names: coordinates
    for (unsigned i =0; i< m_width;i++)
    {
        for (unsigned j=0; j< m_height;j++)
        {
            if (playmap[i][j].itemName == iName)
            {
                return std::pair<unsigned, unsigned>(i,j);
            }
        }
    }

    return std::pair<unsigned,unsigned>(m_width+1, m_height+1);
}


template <typename img>
void gameboard<img>::placeMember(unsigned x, unsigned y, mapObject<img> &character)
{
    if (!(x<m_width && y < m_height))
    {
        std::cout<<"Out of map range! \n"<<std::endl;
        return;
    }

    std::pair<unsigned,unsigned> alreadyPlaced = findCoord(character.itemName);
    if (alreadyPlaced.first == (m_width+1) && alreadyPlaced.second == (m_height +1))
    {
        character.moveTo(playmap[x][y]);
        playmap[x][y] = character;
    }
    else
    {
        moveTo(character, playmap[x][y]);

    }
}
#endif // GAMEBOARD_H


