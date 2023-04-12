#pragma once

#include <string>
#include <vector>
#include "Employee.hpp"
#include "Shelf.hpp"
#include "Task.hpp"

class Warehouse {
    public:
        Warehouse();
        std::vector<Employee*> employees;
        std::vector<Task*> tasks;
        std::vector<Shelf*> shelves;
        TaskStatus getTotalTaskStatus();
        void performOneTask(int taskID);
        void performAllTasks();
        void addEmployee(Employee* employee);
        void addTask(Task* task);
        void addShelf(Shelf* shelf);
};
