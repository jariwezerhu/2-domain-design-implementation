#pragma once

#include "IContainer.hpp"
#include <string>

class Pallet : public IContainer {
    public:
        Pallet(std::string itemName, int itemCapacity, int itemCount);
        std::string getItemName();
        int getItemCount();
        int getRemainingSpace();
        bool reallocateEmptyPallet(std::string itemName, int itemCapacity, int itemCount);
        bool takeOne();
        bool putOne();
        bool isFull() override;
        bool isEmpty() override;
        bool hasItem(std::string item) override;
    private:
        int itemCount; // only mutable with putOne() and takeOne()
        std::string itemName; // only mutable if pallet is empty
        int itemCapacity; // only mutable if pallet is empty
};
