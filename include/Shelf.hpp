#pragma once

#include <array>
#include "IContainer.hpp"
#include "Pallet.hpp"

class Shelf : public IContainer {
    public:
        Shelf();
        Pallet* pallets[4];
        std::array<bool, 4> getSlotStatus();
        void sortPallets();
        bool removePallet(int slot);
        bool insertPallet(int slot, Pallet* pallet);
        bool isFull() override;
        bool isEmpty() override;
        bool hasItem(std::string item) override;
        int getItemCount(std::string item);
};
