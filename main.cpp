#include <iostream>
#include <string>
#include "tt.h"





int main()
{


    std::string command;
    std::string taskDesc;
    std::cin >> command;
    std::getline(std::cin, taskDesc);
    if (isCUD) {
        checkForCUD(command);
    }
    switch (CL)
    {
    case 0:
        add(taskDesc);
        break;
    case 1:
        std::cout << "Execute update command" << std::endl;

        break;
    case 2:
        std::cout << "Execute remove command" << std::endl;

        break;
    case 3:
        checkForReadCommand();
        break;
    }
}




