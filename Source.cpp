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
	
    std::ifstream execfile;

    execfile.open("tiny.txt");

    std::string command_line;

    std::getline(execfile, command_line);

    while (command_line.substr(5, 3) != "ZZZ")
	{
        if (command_line.substr(0, 4) == "    ")
		{
            if (command_line.substr(5, 3) == "INP")
			{
				std::cin >> symbols[0].second;
			}

            else if (command_line.substr(5, 3) == "OUT")
			{
				std::cout << symbols[0].second;
			}

            else if (command_line.substr(5, 3) == "COP")
			{
				size_t index[2];				

				for (int i = 0; i < symSize; i++)
				{
                    size_t found = command_line.substr(9, command_line.size() - 8).find(symbols[i].first);

					if (found != std::string::npos)
					{
						if (found == 9)
						{
                            index[0] = command_line.substr(9, command_line.size() - 8).find(symbols[i].first);
						}

						else
						{
                            index[1] = command_line.substr(9, command_line.size() - 8).find(symbols[i].first);
						}
					}
				}

				symbols[index[1]].second = symbols[index[0]].second;
			}

            else if (command_line.substr(5, 3) == "ADD")
			{
                for (int i = 0; i < symSize; i++)
                {
                    if (symbols[i].first == command_line.substr(9, 3))
                    {
                        symbols[1].second += symbols[i].second;
                    }
                }
			}

            else if (command_line.substr(5, 3) == "SUB")
            {
                for (int i = 0; i < symSize; i++)
                {
                    if (symbols[i].first == command_line.substr(9, 3))
                    {
                        symbols[1].second -= symbols[i].second;
                    }
                }
            }

            else if (command_line.substr(5, 3) == "MUL")
            {
                for (int i = 0; i < symSize; i++)
                {
                    if (symbols[i].first == command_line.substr(9, 3))
                    {
                        symbols[1].second *= symbols[i].second;
                    }
                }
            }

            else if (command_line.substr(5, 3) == "DIV")
            {
                for (int i = 0; i < symSize; i++)
                {
                    if (symbols[i].first == command_line.substr(9, 3))
                    {
                        symbols[1].second /= symbols[i].second;
                    }
                }
            }

            else if (command_line.substr(5, 3) == "HLT")
            {
                std::cout << "Program finished successfully!";
                exit(EXIT_SUCCESS);
            }
		}

        getline(execfile, command_line);
	}	

	return 0;
}





