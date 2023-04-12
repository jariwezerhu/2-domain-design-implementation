#include "../include/Pallet.hpp"
#include <string>
using namespace std;

Pallet::Pallet(string itemName, int itemCapacity, int itemCount) {
    this->itemName = itemName;
    this->itemCapacity = itemCapacity;
    this->itemCount = itemCount;
}

string Pallet::getItemName() {
    return this->itemName;
}

int Pallet::getItemCount() {
    return this->itemCount;
}

int Pallet::getRemainingSpace() {
    return this->itemCapacity - this->itemCount;
}

bool Pallet::reallocateEmptyPallet(string itemName, int itemCapacity, int itemCount) {
    if (this->isEmpty()) {
        this->itemName = itemName;
        this->itemCapacity = itemCapacity;
        this->itemCount = itemCount;
        return true;
    }
    return false;
}

bool Pallet::takeOne() {
    if (this->isEmpty()) {
        return false;
    }
    this->itemCount--;
    return true;
}

bool Pallet::putOne() {
    if (this->isFull()) {
        return false;
    }
    this->itemCount++;
    return true;
}

bool Pallet::isFull() {
    return this->itemCount == this->itemCapacity;
}

bool Pallet::isEmpty() {
    return this->itemCount == 0;
}

bool Pallet::hasItem(string item) {
    return this->itemName == item;
}