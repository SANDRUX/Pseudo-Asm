#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

int main() 
{
	std::ifstream infile;

	infile.open("tiny.txt");

	int PC = 0;
	int symSize = 2;

	std::string line;
	std::string syName[990];

	std::vector<std::pair<std::string, int>> symbols(992);

	int symAddress[992];
	
	std::getline(infile, line);

	//initialize register values
	symbols[0].first = "R1";
	symbols[0].second = 0;

	symbols[1].first = "R2";
	symbols[1].second = 0;
	
	while (line.substr(5, 3) != "ZZZ") 
	{
		if (line.substr(0, 4) != "    ") 
		{
			symbols[symSize].first = line.substr(0, 4);
			symbols[symSize].second = (line.substr(9, 1))[0] - '0';
			symAddress[symSize] = PC;
			symSize++;		
		}

		std::getline(infile, line);
		
		PC++;
	}

	std::cout << "name" << " " << "value" << std::endl;
	
	for (int i = 0; i < symSize; i++)
	{
		std::cout << symbols[i].first << " " << symbols[i].second << std::endl;
	}
	
	infile.close();
	
	std::fstream execfile;

	execfile.open("tiny.txt");

	std::getline(execfile, line);

	while (line.substr(5, 3) != "ZZZ") 
	{
		if (line.substr(0, 4) == "    ") 
		{
			switch (line.substr(5, 3))
			{
				case "INP":

					std::cin >> symbols[0].second;
					break;
				
				case "OUT":

					std::cout << symbols[0].second;
					break;

				case "COP":

					std::string args[2];				

					for (int i = 0; i < symSize; i++)
					{
						size_t found = std::find(line.substr(9, line.size() - 8));

						if (found != std::string::npos)
						{
							if (found == 9)
							{
								args[0] = std::find(line.substr(9, line.size() - 8));
							}

							else
							{
								args[1] = std::find(line.substr(9, line.size() - 8));
							}
						}
					}

					int index[2];

					for (int i = 0; i < symSize; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							if (symbols[i].first == args[j])
							{
								index[j] = i;
							}
						}
					}

					symbols[index[1]].second = symbols[index[0]].second;

					break;

				case "ADD":
					//TODO
					break;

				case "SUB":
					//TODO
					break;

				case "MUL":
					//TODO
					break;

				case "DIV":
					//TODO
					break;

				case "HLT":
					//TODO
					break;
			}
		}

		std::getline(infile, line);
	}	

	return 0;
}





