#include "IContainer.hpp"
#include <string>
using namespace std;

class Pallet : public IContainer {
    public:
        Pallet(string itemName, int itemCapacity, int itemCount);
        string getItemName();
        int getItemCount();
        int getRemainingSpace();
        bool reallocateEmptyPallet(string itemName, int itemCapacity, int itemCount);
        bool takeOne();
        bool putOne();
    private:
        int itemCount;
        string itemName;
        int itemCapacity;
};