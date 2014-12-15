#include <string>
#include <iostream>

template  < typename img>
class mapObject
{
	public:
		mapObject( int x, int y );
		mapObject(int x, int y, std::string name, img rep);
		int xlocation;
		int ylocation;
		bool impassable;
		img visualRepresentation;
		std::string itemName;
		unsigned distance(const mapObject & other);
};


//CONSTRUCTOR
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

template <typename img>
unsigned mapObject<img>::distance(const mapObject & other)
{
	unsigned xdist = std::max(xlocation, other.xlocation) - std::min(xlocation,other.xlocation);
	unsigned ydist = std::max(ylocation, other.ylocation) - std::min(ylocation,other.ylocation);
	return xdist + ydist;
}

int main()
	{
	mapObject <char> peanut = mapObject<char>( 3,4);
	mapObject <char>  creepything = mapObject<char>(5,6,"Creepything", 'D');
	std::cout<<peanut.itemName<<std::endl;
	std::cout<< creepything.itemName<<std::endl;
	std::cout<< creepything.distance(peanut)<<std::endl;
	return 0;
	}