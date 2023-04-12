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
    private:
        TaskStatus taskStatus;
        bool requiresForklift;
};

class rearrangeShelf : public Task {
    public:
        rearrangeShelf(int shelfID);
        int getShelfID();
        bool runTask(Employee& employee, std::vector<Shelf>& shelves) override;
    private:
        int shelfID;
};

class pickItems : public Task {
    public:
        pickItems(std::string itemName, int itemCount);
        std::string getItemName();
        int getItemCount();
        bool runTask(Employee& employee, std::vector<Shelf>& shelves) override;
    private:
        std::string itemName;
        int itemCount;
};

// class putItems : public Task {
//     public:
//         putItems(string itemName, int itemCount);
//         string getItemName();
//         int getItemCount();
//         bool runTask(Employee& employee, vector<Shelf>& shelves);
//     private:
//         string itemName;
//         int itemCount;
// };