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

    std::string line = "long string";
	std::string syName[990];

	std::vector<std::pair<std::string, int>> symbols(992);

	int symAddress[992];

	//initialize register values
	symbols[0].first = "R1";
	symbols[0].second = 0;

	symbols[1].first = "R2";
	symbols[1].second = 0;
	
    std::getline(infile, line);

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
			if (line.substr(5, 3) == "INP")
			{
				std::cin >> symbols[0].second;
			}

			else if (line.substr(5, 3) == "OUT")
			{
				std::cout << symbols[0].second;
			}

			else if (line.substr(5, 3) == "COP")
			{
				size_t index[2];				

				for (int i = 0; i < symSize; i++)
				{
					size_t found = line.substr(9, line.size() - 8).find(symbols[i].first);

					if (found != std::string::npos)
					{
						if (found == 9)
						{
							index[0] = line.substr(9, line.size() - 8).find(symbols[i].first);
						}

						else
						{
							index[1] = line.substr(9, line.size() - 8).find(symbols[i].first);
						}
					}
				}

				symbols[index[1]].second = symbols[index[0]].second;
			}

			else if (line.substr(5, 3) == "ADD")
			{
				//TODO
			}
		}
		std::getline(infile, line);
	}	

	return 0;
}





