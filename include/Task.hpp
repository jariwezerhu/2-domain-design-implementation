#pragma once

#include <vector>
#include "Employee.hpp"
#include "Shelf.hpp"

enum class TaskStatus {
    todo,
    finished,
    failed
};

class Task {
    public:
        Task();
        bool getRequiresForklift();
        void setRequiresForklift(bool requiresForklift);
        TaskStatus getTaskStatus();
        void setTaskStatus(TaskStatus taskStatus);
        virtual bool runTask(Employee& employee, std::vector<Shelf>& shelves) = 0;
        void setTaskID(int taskID);
        int getTaskID();
    private:
        TaskStatus taskStatus;
        bool requiresForklift;
        int taskID;
};

class rearrangeShelf : public Task {
    public:
        rearrangeShelf(int taskID, int shelfID, bool requiresForklift);
        int getShelfID();
        bool runTask(Employee& employee, std::vector<Shelf>& shelves) override;
    private:
        int shelfID;
};

class pickItems : public Task {
    public:
        pickItems(int taskID, std::string itemName, int itemCount, bool requiresForklift);
        std::string getItemName();
        int getItemCount();
        bool runTask(Employee& employee, std::vector<Shelf>& shelves) override;
    private:
        std::string itemName;
        int itemCount;
};
