#include "IContainer.hpp"
#include array
#include "Pallet.hpp"
using namespace std;

class Shelf : public IContainer {
    public:
        Shelf();
        array<bool, 4> getSlotStatus();
        bool removePallet(int slot);
        bool insertPallet(int slot, Pallet* pallet);
};
