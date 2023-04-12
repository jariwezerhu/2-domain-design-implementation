#include "../include/Task.hpp"
using namespace std;

Task::Task() {
    this->requiresForklift = false;
    this->taskStatus = TaskStatus::todo;
}

bool Task::getRequiresForklift() {
    return requiresForklift;
}

void Task::setRequiresForklift(bool requiresForklift) {
    this->requiresForklift = requiresForklift;
}

TaskStatus Task::getTaskStatus() {
    return taskStatus;
}

void Task::setTaskStatus(TaskStatus taskStatus) {
    this->taskStatus = taskStatus;
}

rearrangeShelf::rearrangeShelf(int shelfID) {
    this->shelfID = shelfID;
}

int rearrangeShelf::getShelfID() {
    return shelfID;
}

bool rearrangeShelf::runTask(Employee& employee, std::vector<Shelf>& shelves) {
    this->setRequiresForklift(true);
    int shelfID = this->getShelfID();

    // Check if employee is busy
    if (employee.getBusy()) {
        return false;
    }
    // Check if forklift is required and if employee has a forklift certificate
    if (this->getRequiresForklift() && !employee.getForkliftCertificate()) {
        return false;
    }
    // Check if shelf exists
    if (shelfID > shelves.size()) {
        return false;
    }

    // Check if shelf is empty
    if (shelves[shelfID].isEmpty()) {
        return false;
    }

    // Sort pallets on shelf by item counts in ascending order
    employee.setBusy(true);
    shelves[shelfID].sortPallets();
    employee.setBusy(false);

    return true;
}

pickItems::pickItems(std::string itemName, int itemCount) {
    this->itemName = itemName;
    this->itemCount = itemCount;
}

std::string pickItems::getItemName() {
    return itemName;
}

int pickItems::getItemCount() {
    return itemCount;
}

bool pickItems::runTask(Employee& employee, std::vector<Shelf>& shelves) {
    this->setRequiresForklift(false);
    std::string itemName = this->getItemName();
    int itemCount = this->getItemCount();

    // Check if employee is busy
    if (employee.getBusy()) {
        return false;
    }
    // Check if forklift is required and if employee has a forklift certificate
    if (this->getRequiresForklift() && !employee.getForkliftCertificate()) {
        return false;
    }
    // Check if item count is valid
    if (itemCount <= 0) {
        return false;
    }
    // Check if item exists on any shelf
    bool itemExists = false;
    for (int i = 0; i < shelves.size(); i++) {
        if (shelves[i].hasItem(itemName)) {
            itemExists = true;
            break;
        }
    }
    if (!itemExists) {
        return false;
    }
    
    // Pick items
    employee.setBusy(true);
    int itemsPicked = 0;
    for (int i = 0; i < shelves.size(); i++) {
        if (shelves[i].hasItem(itemName)) {
            // Remove pallet from shelf if it hasItem(itemName) and itemCount == 0
            for (int j = 0; j < 4; j++) {
                if (shelves[i].pallets[j] != nullptr && 
                    shelves[i].pallets[j]->hasItem(itemName) && 
                    !shelves[i].pallets[j]->isEmpty()) 
                {
                    while (itemsPicked < itemCount && !shelves[i].pallets[j]->isEmpty()) {
                        shelves[i].pallets[j]->takeOne();
                        itemsPicked++;
                    }
                }
            }
        }
    }
    employee.setBusy(false);

    // Check if all items were picked
    return itemsPicked == itemCount;
}

// putItems::putItems(string itemName, int itemCount) {
//     this->itemName = itemName;
//     this->itemCount = itemCount;
// }