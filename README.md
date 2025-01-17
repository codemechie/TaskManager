# TaskManager
A simple command line interface (CLI) to track what you need to do, what you have done, and what you are currently working on.
Despite being a simpler approach, this project does not directly create JSON objects. The user enters a description for a task that creates a C++ object with properties: 'Description', 'Status', 'Id', 'createdAt', 'updatedAt'. This C++ object is then converted into a JSON object using a toJson() method that returns a JSON object.
- ![#c5f015](https://placehold.co/15x15/c5f015/c5f015.png) 'json to_json() const {
    return json{ {"description", Description}, {"id", Id}, {"status", Status} };
}'
This method is called inside another function that takes as input the C++ object and the filename. This function writes to the JSON file.
- ![#c5f015](https://placehold.co/15x15/c5f015/c5f015.png) 'void saveTaskToJson(const Task& task, const std::string& filename);'
Finally there is the actual add function that takes as input a string for the task description and creates a C++ object and passes it to the saveTaskToJson function.
- ![#c5f015](https://placehold.co/15x15/c5f015/c5f015.png) 'void add(std::string desc);'
  This layered approaches has two major benefits:
  1. It ensures consistency throughout the JSON file since every JSON object will have the same KEYS. In other words, just by the writing the description for a task, the rest of the fields are populated automatically, by the constructor.
  2. Since the object is created inside the add() function, it means it is created on the stack and is immediately destroyed outside the function scope. This results in a much faster execution time and prevents memory wastage.
