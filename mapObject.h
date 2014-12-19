
#include <string>
#include <iostream>
#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include <cmath>

template  < typename img>
class mapObject
{
	public:
	    mapObject();
		mapObject( int x, int y );
		mapObject(int x, int y, std::string name, img rep);
		virtual ~mapObject();
		int xlocation;
		int ylocation;
		bool impassable;
		virtual void moveTo( mapObject<img> &target );
		img visualRepresentation;
		std::string itemName;
		unsigned distance(const mapObject & other) const;
		friend std::ostream &operator<<(std::ostream & os, mapObject<img> & mapobject)
		{
		    os <<mapobject.itemName<<" at "<<mapobject.xlocation<<" ,"<<mapobject.ylocation;
		    return os;
		}
};



//CONSTRUCTOR
template < typename img >
mapObject<img>::mapObject(): impassable(false)
{

}

template < typename img >
mapObject<img>::mapObject( int x, int y )
: xlocation(x), ylocation(y), itemName(" Default mapObject name ")
{

}

template <typename img >
mapObject<img>::mapObject(int x, int y, std::string name, img rep)
:xlocation(x), ylocation(y), visualRepresentation(rep), itemName(name)
{

}
//End constructors


//Destructor
template <typename img>
mapObject<img>::~mapObject()
{

}


template <typename img>
void mapObject<img>::moveTo(mapObject<img> &target)
{
    xlocation= target.xlocation;
    ylocation= target.ylocation;
}


template <typename img>
unsigned mapObject<img>::distance(const mapObject & other) const
{

	unsigned xdist = std::abs(other.xlocation-xlocation);
	unsigned ydist = std::abs(other.ylocation-ylocation);
	return xdist + ydist;
}
#endif
