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

void Task::setTaskID(int taskID) {
    this->taskID = taskID;
}

int Task::getTaskID() {
    return taskID;
}

rearrangeShelf::rearrangeShelf(int taskID, int shelfID, bool requiresForklift = true) {
    this->setRequiresForklift(requiresForklift);
    this->shelfID = shelfID;
    this->setTaskID(taskID);
}

int rearrangeShelf::getShelfID() {
    return shelfID;
}

bool rearrangeShelf::runTask(Employee& employee, std::vector<Shelf>& shelves) {
    int shelfID = this->getShelfID();

    // Check if employee is busy
    if (employee.getBusy()) {
        setTaskStatus(TaskStatus::failed);
        return false;
    }
    // Check if forklift is required and if employee has a forklift certificate
    if (this->getRequiresForklift() && !employee.getForkliftCertificate()) {
        setTaskStatus(TaskStatus::failed);
        return false;
    }
    // Check if shelf exists
    if (shelfID > shelves.size()) {
        setTaskStatus(TaskStatus::failed);
        return false;
    }

    // Check if shelf is empty
    if (shelves[shelfID].isEmpty()) {
        setTaskStatus(TaskStatus::failed);
        return false;
    }

    // Sort pallets on shelf by item counts in ascending order
    employee.setBusy(true);
    shelves[shelfID].sortPallets();
    employee.setBusy(false);

    setTaskStatus(TaskStatus::finished);
    return true;
}

pickItems::pickItems(int taskID, std::string itemName, int itemCount, bool requiresForklift = false) {
    this->itemName = itemName;
    this->itemCount = itemCount;
    this->setRequiresForklift(requiresForklift);
}

std::string pickItems::getItemName() {
    return itemName;
}

int pickItems::getItemCount() {
    return itemCount;
}

bool pickItems::runTask(Employee& employee, std::vector<Shelf>& shelves) {
    std::string itemName = this->getItemName();
    int itemCount = this->getItemCount();

    // Check if employee is busy
    if (employee.getBusy()) {
        setTaskStatus(TaskStatus::failed);
        return false;
    }
    // Check if forklift is required and if employee has a forklift certificate
    if (this->getRequiresForklift() && !employee.getForkliftCertificate()) {
        setTaskStatus(TaskStatus::failed);
        return false;
    }
    // Check if item count is valid
    if (itemCount <= 0) {
        setTaskStatus(TaskStatus::failed);
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
        setTaskStatus(TaskStatus::failed);
        return false;
    }
    
    // Pick items
    employee.setBusy(true);
    
    // Check on which shelves the item exists
    vector<int> shelfIDs;
    for (int i = 0; i < shelves.size(); i++) {
        if (shelves[i].hasItem(itemName)) {
            shelfIDs.push_back(i);
        }
    }

    // Count how many items are on the shelves
    int itemsOnShelves = 0;
    for (int i = 0; i < shelfIDs.size(); i++) {
        itemsOnShelves += shelves[shelfIDs[i]].getItemCount(itemName);
    }

    // Check if there are enough items on the shelves
    if (itemsOnShelves < itemCount) {
        setTaskStatus(TaskStatus::failed);
        return false;
    }

    // If there are enough items, pick them
    int itemsPicked = 0;
    for (int i = 0; i < shelfIDs.size(); i++) {
        int id = shelfIDs[i];
        // Iterate through all pallets on the shelf
        for (int j = 0; j < 4; j++) {
            // Check if pallet exists, has the item and is not empty
            if (shelves[id].pallets[j] == nullptr || !shelves[id].pallets[j]->hasItem(itemName) || shelves[id].pallets[j]->isEmpty()) {
                continue;
            }
            // Take items from the pallet until it is empty or the required amount of items is picked
            while(!shelves[id].pallets[j]->isEmpty() && itemsPicked < itemCount) {
                shelves[id].pallets[j]->takeOne();
                itemsPicked++;
            }
            // If enough items were picked, break the loop
            if (itemsPicked == itemCount) {
                break;
            }
        }
        if (itemsPicked == itemCount) {
            break;
        }
    }

    employee.setBusy(false);

    // Check if all items were picked
    if (itemsPicked == itemCount) {
        setTaskStatus(TaskStatus::finished);
        return true;
    }
    
    setTaskStatus(TaskStatus::failed);
    return false;
}
