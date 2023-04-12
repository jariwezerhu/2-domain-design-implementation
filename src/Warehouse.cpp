#include "../include/Warehouse.hpp"

Warehouse::Warehouse() {

}

TaskStatus Warehouse::getTotalTaskStatus() {
    bool totalTaskStatus = true;
    for (int i = 0; i < this->tasks.size(); i++) {
        TaskStatus taskStatus = this->tasks[i]->getTaskStatus();
        if (taskStatus == TaskStatus::failed) {
            return TaskStatus::failed;
        } else if (taskStatus == TaskStatus::todo) {
            totalTaskStatus = false;
        };
    };
    return totalTaskStatus ? TaskStatus::finished : TaskStatus::todo;        
};

void Warehouse::performOneTask(int taskID) {
    // for (int i = 0; i < this->tasks.size(); i++) {
    //     if (i == taskID) {
    //         this->tasks[i]->runTask(*this->employees[0], this->shelves);
    //     };
    // };
};

void Warehouse::performAllTasks() {
    for (int i = 0; i < this->tasks.size(); i++) {
        this->performOneTask(i);
    };
};

void Warehouse::addEmployee(Employee* employee) {
    this->employees.push_back(employee);
};

void Warehouse::addTask(Task* task) {
    this->tasks.push_back(task);
};

void Warehouse::addShelf(Shelf* shelf) {
    this->shelves.push_back(shelf);
};