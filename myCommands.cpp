#include <string>
#include <iostream>
#include "tt.h"
#include "color.hpp"
int Task::Id = 1;
std::string filename = "tasks.json";
commandListCUD CL;



//FUNCTION TO WRITE THE TASK TO THE JSON FILE
void saveTaskToJson(const Task& task, const std::string& filename) {
    // Create a JSON object for the new task
    json newTaskJson = task.to_json();

    // Create a JSON array to hold all tasks
    json tasks;

    // Try to open the existing file and read its contents
    std::ifstream inputFile(filename);

    if (inputFile.is_open()) {
        // If the file exists, read the existing tasks
        inputFile >> tasks;
        inputFile.close();
    }
    else {
        // If the file does not exist, initialize an empty array
        tasks = json::array();
    }

    // Append the new task to the tasks array
    tasks.push_back(newTaskJson);

    // Write the updated tasks array back to the file
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << tasks.dump(4); // Write JSON with 4-space indentation
        outputFile.close();
    }
    else {
        std::cerr << "Error opening file for writing." << std::endl;
    }
}

//Checking if the command is a CUD command[ADD< UPDATE< REMOVE/DELETE]
void checkForCUD(std::string command) {
    if (command == "add") {
        CL = commandListCUD::ADD;

    }
    else if (command == "update") {
        CL = commandListCUD::UPDATE;
    }
    else if (command == "remove") {
        CL = commandListCUD::REMOVE;
    }
    else {
        CL = commandListCUD::INVALID;
    }
}

//CHECKING FOR READ COMMANDS[LIST TASKS THAT ARE IN TODO, DONE, IN_PROGRESS STATUS]
void checkForReadCommand() {
    std::cout << "Checking for other commands" << std::endl;
}

//ADD FUNCTION
void add(std::string desc) {
    Task T(desc);
    saveTaskToJson(T, filename);
    ++Task::Id;
    std::cout << dye::blue("Task added successfully ") << dye::green("(Id = 1)") << std::endl;
}



