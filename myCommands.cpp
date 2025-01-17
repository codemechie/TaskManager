#include <string>
#include <iostream>
#include "tt.h"
#include "color.hpp"
int Task::Id = 1;
std::string filename = "tasks.json";
commandListCUD CL;
commandListREAD CR;



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

void updateFromJson(int id, std::string desc) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    json tasks;
    inputFile >> tasks;
    inputFile.close();

    // Update the object with the specified id
    bool found = false;
    for (auto& item : tasks) {
        if (item["id"] == id) {
            item["description"] = desc;  // Update description
            std::cout << dye::green("Updated task successfully") << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No object with id " << id << " found." << std::endl;
        return;
    }

    // Write the updated JSON data back to the file
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the file for writing." << std::endl;
        return;
    }

    outputFile << tasks.dump(4);  // Dump with 4 spaces for pretty printing
    outputFile.close();
}

void removeFromJson(int id) {
    // Open the JSON file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    // Parse the JSON data
    json tasks;
    inputFile >> tasks;
    inputFile.close();

    // Remove the object with the specified id
    bool found = false;
    for (auto it = tasks.begin(); it != tasks.end(); ) {
        if (it->contains("id") && (*it)["id"] == id) {
            it = tasks.erase(it);  // Remove the object and get the next iterator
            found = true;
        }
        else {
            ++it;  // Move to the next item
        }
    }

    if (!found) {
        std::cout << "No object with id " << id << " found." << std::endl;
        return;
    }

    // Write the updated JSON data back to the file
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the file for writing." << std::endl;
        return;
    }

    outputFile << tasks.dump(4);  // Dump with 4 spaces for pretty printing
    outputFile.close();
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
void checkForReadCommand(std::string command) {

    if (command == "list-all") {
        CR = commandListREAD::LIST_ALL;

    }
    else if (command == "list-in-progress") {
        CR = commandListREAD::LIST_IN_PROGRESS;
    }
    else if (command == "list-done") {
        CR = commandListREAD::LIST_DONE;
    }
    else if(command == "list-todo"){
        CR = commandListREAD::LIST_TODO;
    }
}



//ADD FUNCTION
void add(std::string desc) {
    Task T(desc);
    saveTaskToJson(T, filename);
    ++Task::Id;
    std::cout << dye::blue("Task added successfully ") << dye::green("(Id = 1)") << std::endl;
}

void update(int id) {
    std::cout << "Enter the updated task:" << std::endl;
    std::string newDesc;
    std::getline(std::cin, newDesc);
    updateFromJson(id, newDesc);
}

void remove(int id) {
    removeFromJson(id);
    std::cout << dye::red("Task removed successfully") << std::endl;
}

void listAll() {
    // Open the JSON file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    // Parse the JSON data
    json jsonData;
    inputFile >> jsonData;
    inputFile.close();

    // List all task descriptions
    std::cout << "Task Descriptions:" << std::endl;
    int count = 1;
    for (const auto& item : jsonData) {
        if (item.contains("description")) {
            std::cout << count++ << ". " << item["description"].get<std::string>() << std::endl;
        }
    }
}
void listTodo() {
    // Open the JSON file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    // Parse the JSON data
    json jsonData;
    inputFile >> jsonData;
    inputFile.close();

    // List all tasks with status "TODO"
    std::cout << "TODO Tasks:" << std::endl;
    int count = 1;
    for (const auto& item : jsonData) {
        if (item.contains("status") && item["status"] == "TODO") {
            if (item.contains("description")) {
                std::cout << count++ << ". " << item["description"].get<std::string>() << std::endl;
            }
        }
    }

    if (count == 1) {
        std::cout << "No TODO tasks found." << std::endl;
    }
}
void listInProgress() {
    // Open the JSON file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    // Parse the JSON data
    json jsonData;
    inputFile >> jsonData;
    inputFile.close();

    // List all tasks with status "TODO"
    std::cout << "TODO Tasks:" << std::endl;
    int count = 1;
    for (const auto& item : jsonData) {
        if (item.contains("status") && item["status"] == "In-Progress") {
            if (item.contains("description")) {
                std::cout << count++ << ". " << item["description"].get<std::string>() << std::endl;
            }
        }
    }

    if (count == 1) {
        std::cout << "No TODO tasks found." << std::endl;
    }
}
void listDone() {
    // Open the JSON file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    // Parse the JSON data
    json jsonData;
    inputFile >> jsonData;
    inputFile.close();

    // List all tasks with status "TODO"
    std::cout << "TODO Tasks:" << std::endl;
    int count = 1;
    for (const auto& item : jsonData) {
        if (item.contains("status") && item["status"] == "Done") {
            if (item.contains("description")) {
                std::cout << count++ << ". " << item["description"].get<std::string>() << std::endl;
            }
        }
    }

    if (count == 1) {
        std::cout << "No TODO tasks found." << std::endl;
    }
}




