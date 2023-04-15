#include "../include/Pallet.hpp"
#include "../include/Shelf.hpp"
#include "../include/Employee.hpp"
#include "../include/Task.hpp"

#include <iostream>
#include <array>
using namespace std;

int main() {
    // Create a few random items
    vector<string> items;
    for (int i = 0; i < 10; i++) {
        items.push_back("Item" + to_string(i));
    }

    // Create shelves
    vector<Shelf> shelves;
    for (int i = 0; i < 10; i++) {
        shelves.push_back(Shelf());
    }
    // Fill shelves with pallets
    for (int i = 0; i < shelves.size(); i++) {
        for (int j = 0; j < 4; j++) {
            // Randomly choose an item from the list
            string item = items[rand() % items.size()];
            // Randomly choose a capacity between 0 and 10
            int capacity = rand() % 11;
            // Randomly choose a count between 0 and the capacity
            int count = rand() % (capacity + 1);
            // Create a pallet with the item, capacity, and count
            Pallet* pallet = new Pallet(item, capacity, count);
            // Insert the pallet into the shelf
            shelves[i].insertPallet(j, pallet);
        }
    }

    // Create some employees
    vector<Employee> employees;
    for (int i = 0; i < 10; i++) {
        string name = "Employee" + to_string(i);
        Employee employee = Employee(i, name, rand() % 2);
        employees.push_back(employee);
    }

    // Print employee information
    cout << "Employees:" << endl;
    for (int i = 0; i < employees.size(); i++) {
        cout << "ID: " << employees[i].getID() << endl;
        cout << "Name: " << employees[i].getName() << endl;
        cout << "Forklift Certificate: " << employees[i].getForkliftCertificate() << endl;
        cout << endl;
    }

    // Create pickItem task
    pickItems pickItemsTask = pickItems("Item2", 10);

    // Run pickItems task
    bool success = pickItemsTask.runTask(employees[0], shelves);
    if (success) {
        cout << "Task completed successfully!" << endl;
    } else {
        cout << "Task failed!" << endl;
    }
}