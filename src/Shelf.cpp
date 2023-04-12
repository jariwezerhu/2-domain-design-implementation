#include "../include/Shelf.hpp"
using namespace std;

Shelf::Shelf() {
    // Initialize pallets as nullptr
    for (int i = 0; i < 4; i++) {
        pallets[i] = nullptr;
    }
}

array<bool, 4> Shelf::getSlotStatus() {
    array<bool, 4> slotStatus;
    for (int i = 0; i < 4; i++) {
        if (pallets[i] == nullptr) {
            slotStatus[i] = false;
        } else {
            slotStatus[i] = true;
        }
    }
    return slotStatus;
}

void Shelf::sortPallets() {
    // Remove all pallets from shelf
    Pallet* tempPallets[4];
    for (int i = 0; i < 4; i++) {
        tempPallets[i] = pallets[i];
        pallets[i] = nullptr;
    }

    // Sort pallets by item count in ascending order using bubble sort
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (tempPallets[j] != nullptr && tempPallets[j + 1] != nullptr) {
                if (tempPallets[j]->getItemCount() > tempPallets[j + 1]->getItemCount()) {
                    Pallet* tempPallet = tempPallets[j];
                    tempPallets[j] = tempPallets[j + 1];
                    tempPallets[j + 1] = tempPallet;
                }
            }
        }
    }

    // Insert pallets back into shelf
    for (int i = 0; i < 4; i++) {
        pallets[i] = tempPallets[i];
    }
}

bool Shelf::removePallet(int slot) {
    if (pallets[slot] == nullptr) {
        return false;
    } else {
        pallets[slot] = nullptr;
        return true;
    }
}

bool Shelf::insertPallet(int slot, Pallet* pallet) {
    if (pallets[slot] == nullptr) {
        pallets[slot] = pallet;
        return true;
    } else {
        return false;
    }
}

bool Shelf::isFull() {
    for (int i = 0; i < 4; i++) {
        if (pallets[i] == nullptr) {
            return false;
        }
    }
    return true;
}

bool Shelf::isEmpty() {
    for (int i = 0; i < 4; i++) {
        if (pallets[i] != nullptr) {
            return false;
        }
    }
    return true;
}

bool Shelf::hasItem(string item) {
    for (int i = 0; i < 4; i++) {
        if (pallets[i] != nullptr) {
            if (pallets[i]->hasItem(item)) {
                return true;
            }
        }
    }
    return false;
}