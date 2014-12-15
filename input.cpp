
#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <vector>
template <typename T>
void input( T &data) ;  //type validation only

template <typename T>
void input( T &data, const std::vector<T>&validInput);  //type and set validation



template <typename T>
void input ( T &data)
{
	do
	{
		std::cin >>data;
        if(std::cin.fail())
        {
            std::cout<< "Invalid input.  Please try again."<<std::endl;
            std::cin.clear();
            std::cin.ignore(100000,'\n');
        }
        else
        {
            break;
        }
	}
	while (!std::cin.fail());
}

template <typename T>
void input( T & data, const std::vector<T> & validInput )
{
	bool valid= false;
	input( data );
	for( int i = 0; i < validInput.size();i++)
		{
			valid = valid || (validInput[i] ==data);
		}
	if (!valid)
	{
        std::cout<<"That was not a valid option.  Sorry!"<<std::endl;
        input( data, validInput );
	}
}


#endif
/*
int main()

{
    int g;
    input (g);
    std::vector <int> potato;
    potato.push_back(5);
    potato.push_back(7);
    potato.push_back(3);
    std::cout<<g<<std::endl;
    input(g, potato);

    return 0;
}
*/
