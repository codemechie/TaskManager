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

        break;
    case 2:
        std::cout << "Execute remove command" << std::endl;

        break;
    case 3:
        checkForReadCommand(command);
        break;
    }
    switch (CR) {
        {
    case 0:
        listTodo();
        break;
    case 1:
        listInProgress();

        break;
    case 2:
        listDone();

        break;
    case 3:
        listAll();
        break;
        }
    }
}




