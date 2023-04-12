#include "../include/Pallet.hpp"
#include "../include/Shelf.hpp"
#include "../include/Employee.hpp"
#include "../include/Task.hpp"

#include <iostream>
#include <array>
using namespace std;

int main() {
    // Test if sort pallets works
    Shelf shelf;
    Pallet* pallet1 = new Pallet("item1", 10, 2);
    Pallet* pallet2 = new Pallet("item2", 10, 7);
    Pallet* pallet3 = new Pallet("item3", 10, 3);
    Pallet* pallet4 = new Pallet("item4", 10, 4);

    shelf.insertPallet(0, pallet1);
    shelf.insertPallet(1, pallet2);
    shelf.insertPallet(2, pallet3);
    shelf.insertPallet(3, pallet4);

    array<bool, 4> slotStatus = shelf.getSlotStatus();
    for (int i = 0; i < 4; i++) {
        if (slotStatus[i]) {
            cout << "Pallet " << i << " item count: " << shelf.pallets[i]->getItemCount() << endl;
        }
    }

    shelf.sortPallets();

    // Test if pallets are sorted
    slotStatus = shelf.getSlotStatus();
    for (int i = 0; i < 4; i++) {
        if (slotStatus[i]) {
            cout << "Pallet " << i << " item count: " << shelf.pallets[i]->getItemCount() << endl;
        }
    }

}