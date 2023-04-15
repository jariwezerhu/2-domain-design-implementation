#include "../include/Pallet.hpp"
#include "../include/Shelf.hpp"
#include "../include/Employee.hpp"
#include "../include/Task.hpp"
#include "../include/Warehouse.hpp"

#include <iostream>
#include <array>
using namespace std;

int main() {
    Warehouse warehouse = Warehouse();

    // Create a few random items names
    vector<string> items;
    for (int i = 0; i < 10; i++) {
        items.push_back("Item" + to_string(i));
    }

    // Create shelves
    for (int i = 0; i < 10; i++) {
        Shelf* shelf = new Shelf();
        warehouse.addShelf(shelf);
    }
    // Fill shelves with pallets
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            string item = items[rand() % items.size()];
            int capacity = rand() % 11;
            int count = rand() % (capacity + 1);
            Pallet* pallet = new Pallet(item, capacity, count);
            warehouse.shelves[i]->insertPallet(j, pallet);
        }
    }

    // Print shelf information
    cout << "Shelves:" << endl;
    for (int i = 0; i < warehouse.shelves.size(); i++) {
        cout << "Shelf " << i << ":" << endl;
        array<bool, 4> slotStatus = warehouse.shelves[i]->getSlotStatus();
        for (int j = 0; j < 4; j++) {
            cout << "Slot " << j << ": " << slotStatus[j] << endl;
        }
        cout << endl;
    }

    // Create some employees
    for (int i = 0; i < 10; i++) {
        string name = "Employee" + to_string(i);
        Employee* employee = new Employee(i, name, rand() % 2);
        warehouse.addEmployee(employee);
    }

    // Print employee information
    cout << "Employees:" << endl;
    for (int i = 0; i < warehouse.employees.size(); i++) {
        cout << "Employee " << i << ":" << endl;
        cout << "ID: " << warehouse.employees[i]->getID() << endl;
        cout << "Name: " << warehouse.employees[i]->getName() << endl;
        cout << endl;
    }

    // Create some pickitems tasks
    pickItems pickItemsTask = pickItems(0, "Item2", 10, true);
    pickItems pickItemsTask2 = pickItems(1, "Item3", 5, false);
    pickItems pickItemsTask3 = pickItems(2, "Item2", 3, true);
    pickItems pickItemsTask4 = pickItems(3, "Item6", 2, false);

    // Create some rearrange tasks
    rearrangeShelf rearrangeTask = rearrangeShelf(4, 0, false);
    rearrangeShelf rearrangeTask2 = rearrangeShelf(5, 3, true);
    rearrangeShelf rearrangeTask3 = rearrangeShelf(6, 6, false);
    rearrangeShelf rearrangeTask4 = rearrangeShelf(7, 2, true);

    // Add tasks to warehouse
    warehouse.addTask(&pickItemsTask);
    warehouse.addTask(&pickItemsTask2);
    warehouse.addTask(&pickItemsTask3);
    warehouse.addTask(&pickItemsTask4);
    warehouse.addTask(&rearrangeTask);
    warehouse.addTask(&rearrangeTask2);
    warehouse.addTask(&rearrangeTask3);
    warehouse.addTask(&rearrangeTask4);

    // Run all tasks
    warehouse.performAllTasks();

    // Print success of tasks
    cout << "Tasks:" << endl;
    for (int i = 0; i < warehouse.tasks.size(); i++) {
        TaskStatus status = warehouse.tasks[i]->getTaskStatus();
        string statusString;
        if (status == TaskStatus::todo) {
            statusString = "todo";
        } else if (status == TaskStatus::finished) {
            statusString = "finished";
        } else if (status == TaskStatus::failed) {
            statusString = "failed";
        } 
        cout << "Task " << i << ":" << endl;
        cout << "Success: " << statusString << endl;
        cout << endl;
    }

    warehouse.performAllTasks();

    // Print success of tasks
    cout << "Tasks:" << endl;
    for (int i = 0; i < warehouse.tasks.size(); i++) {
        TaskStatus status = warehouse.tasks[i]->getTaskStatus();
        string statusString;
        if (status == TaskStatus::todo) {
            statusString = "todo";
        } else if (status == TaskStatus::finished) {
            statusString = "finished";
        } else if (status == TaskStatus::failed) {
            statusString = "failed";
        } 
        cout << "Task " << i << ":" << endl;
        cout << "Success: " << statusString << endl;
        cout << endl;
    }

    std::cout << "Press enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}