#pragma once
#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
//#include "tasks.json"


static bool isCUD = true;
static std::string status[3] = { "TODO", "In-Progress", "Done" };


using json = nlohmann::json;

enum commandListCUD {
    ADD, UPDATE, REMOVE, INVALID
};
extern commandListCUD CL;

enum commandListREAD {
    LIST_TODO, LIST_IN_PROGRESS, LIST_DONE, LIST_ALL, INVALID
};
extern commandListREAD CR = LIST_TODO;

class Task {
public:
    static int Id;
    std::string Description;
    std::string Status;
public:
    Task(std::string s) {
        Description = s;
        Status = status[0];
    }
    json to_json() const {
        return json{ {"description", Description}, {"id", Id}, {"status", Status} };
    }
};


void add(std::string desc);
void update(int id);
void remove(int id);
void saveTaskToJson(const Task& task, const std::string& filename);
void checkForCUD(std::string command);
void checkForReadCommand(std::string command);


void listAll();
void listTodo();
void listInProgress();
void listDone();

