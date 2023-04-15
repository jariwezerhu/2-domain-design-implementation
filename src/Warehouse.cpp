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
    Task* task = this->tasks[taskID];
    TaskStatus taskStatus = task->getTaskStatus();
    if (taskStatus == TaskStatus::todo) {
        for (int i = 0; i < this->employees.size(); i++) {
            Employee* employee = this->employees[i];
            if (!employee->getBusy()) {
                bool taskSuccess = task->runTask(*employee, this->shelves);
                if (taskSuccess) {
                    task->setTaskStatus(TaskStatus::finished);
                    return;
                } else {
                    task->setTaskStatus(TaskStatus::failed);
                    return;
                };
            };
        };
    };
    if (taskStatus == TaskStatus::failed) {
        task->setTaskStatus(TaskStatus::todo);
    };
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