// include libraries here
#include <iostream>
#include <string>
#include "graph.h"

int main()
{

    // your code goes here...

    Graph theGraph;

    while (!std::cin.eof())
    {
        std::string command;
        getline(std::cin, command);
        if (command[0] == 'i')
        {
            int sourceCounter = 0;
            for (auto character : command.substr(7))
            {
                if (character == ' ')
                {
                    break;
                }
                sourceCounter++;
            }
            int source = std::stoi(command.substr(7, sourceCounter));

            int targetCounter = 0;
            for (auto character : command.substr(8 + sourceCounter))
            {
                if (character == ' ')
                {
                    break;
                }
                targetCounter++;
            }
            int target = std::stoi(command.substr(8 + sourceCounter, targetCounter));

            int distanceCounter = 0;
            for (auto character : command.substr(9 + sourceCounter + targetCounter))
            {
                if (character == ' ')
                {
                    break;
                }
                distanceCounter++;
            }
            double distance = std::stod(command.substr(9 + sourceCounter + targetCounter, distanceCounter));

            int speedCounter = 0;
            for (auto character : command.substr(10 + sourceCounter + targetCounter + distanceCounter))
            {
                if (character == ' ')
                {
                    break;
                }
                speedCounter++;
            }
            double speed = std::stod(command.substr(10 + sourceCounter + targetCounter + distanceCounter, speedCounter));

            theGraph.insertE(source, target, distance, speed, 1);
            std::cout << "success" << std::endl;
        }
        if (command[0] == 'l' && command[2] == 'a')
        {
            std::string file = command.substr(5);
            theGraph.load(file);
            std::cout << "success" << std::endl;
        }
        if (command[0] == 't')
        {
            int sourceCounter = 0;
            for (auto character : command.substr(8))
            {
                if (character == ' ')
                {
                    break;
                }
                sourceCounter++;
            }
            int source = std::stoi(command.substr(8, sourceCounter));

            int targetCounter = 0;
            for (auto character : command.substr(9 + sourceCounter))
            {
                if (character == ' ')
                {
                    break;
                }
                targetCounter++;
            }
            int target = std::stoi(command.substr(9 + sourceCounter, targetCounter));

            int aCounter = 0;
            for (auto character : command.substr(10 + sourceCounter + targetCounter))
            {
                if (character == ' ')
                {
                    break;
                }
                aCounter++;
            }
            double a = std::stod(command.substr(10 + sourceCounter + targetCounter, aCounter));

            if (theGraph.updateA(source, target, a))
            {
                std::cout << "success" << std::endl;
            }
            else
            {
                std::cout << "failure" << std::endl;
            }
        }
        if (command[0] == 'u')
        {
            std::string file = command.substr(7);
            theGraph.updateF(file);
        }
        if (command[0] == 'p' && command[1] == 'r')
        {
            theGraph.printAdjV(std::stoi(command.substr(6)));
        }
        if (command[0] == 'd')
        {
            theGraph.deleteV(std::stoi(command.substr(7)));
        }
        if (command[0] == 'p' && command[1] == 'a')
        {
            int sourceCounter = 0;
            for (auto character : command.substr(5))
            {
                if (character == ' ')
                {
                    break;
                }
                sourceCounter++;
            }
            int source = std::stoi(command.substr(5, sourceCounter));

            int targetCounter = 0;
            for (auto character : command.substr(6 + sourceCounter))
            {
                if (character == ' ')
                {
                    break;
                }
                targetCounter++;
            }
            int target = std::stoi(command.substr(6 + sourceCounter, targetCounter));

            if (theGraph.vertexExists(source) && theGraph.vertexExists(target))
            {
                std::vector<int> path = theGraph.path(source, target);
                if (!path.empty())
                {

                    for (int i = 0; i < path.size(); ++i)
                    {
                        std::cout << path[i];
                        if (i < path.size() - 1)
                        {
                            std::cout << ' ';
                        }
                    }
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << "failure" << std::endl;
                }
            }
            else
            {
                std::cout << "failure" << std::endl;
            }
        }
        if (command[0] == 'l' && command[2] == 'w')
        {
            int sourceCounter = 0;
            for (auto character : command.substr(7))
            {
                if (character == ' ')
                {
                    break;
                }
                sourceCounter++;
            }
            int source = std::stoi(command.substr(7, sourceCounter));

            int targetCounter = 0;
            for (auto character : command.substr(8 + sourceCounter))
            {
                if (character == ' ')
                {
                    break;
                }
                targetCounter++;
            }
            int target = std::stoi(command.substr(8 + sourceCounter, targetCounter));
            // std::cout<<theGraph.lowest(source, target)<<std::endl;
            if (theGraph.vertexExists(source) && theGraph.vertexExists(target))
            {
                if (theGraph.lowest(source, target) != -1.0)
                {
                    std::cout << theGraph.lowest(source, target) << std::endl;
                }
                else
                {
                    std::cout << "failure" << std::endl;
                }
            }
            else
            {
                std::cout << "failure" << std::endl;
            }
        }
        if (command[0] == 'e')
        {
            return 0;
        }
    }
}
