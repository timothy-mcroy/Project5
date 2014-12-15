
#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <vector>
template <typename T>
void input( T &data) ;  //type validation only

template <typename T>
void input( T &data, const std::vector<T>);  //type and set validation



template <typename T> 
void input ( T &data)
{
	do
	{
		std::cin >>data;
	}
	while ( !cin.fail() )
	{
		std::cout<< "Invalid input.  Please try again."<<std::endl;
		std::cin.clear();
		cin.ignore(100000,'\n');
	}
} 

template <typename T>
void input( T & data, const std::vector<T> & validInput ) 
{
	bool valid= false;
	input( data );
	for( int i = 0; i < validInput.size();i++)
		{
			valid = valid || validInput[i] ==data;
		}
	if (!valid)
	{
		input( T & data, validInput );
	}
}


#endif