#include <iostream>
#include<fstream>
#include <string>
#include <cstring>

int main() 
{
	std::ifstream infile;
	infile.open("tiny.txt");

	int PC =0;
	int symSize = 0;

	std::string line;
	std::string syName[990];

	int symAddress[990];
	
	getline(infile, line);
	
	while (line.substr(5, 3) != "ZZZ") 
	{
		if (line.substr(0, 4) != "    ") 
		{
			syName[symSize] = line.substr(0, 4);
			symAddress[symSize] = PC;
			symSize++;
			
		}

		std::getline(infile, line);
		PC++;
		
	}

	std::cout << "name" << " " << "adress" << std::endl;
	
	for (int i = 0; i < symSize; i++)
	{
		std::cout << syName[i] << " " << symAddress[i] << std::endl;
	}
	
	infile.close();
	
	return 0;
}





