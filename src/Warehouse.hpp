#include <string>
#include "Employee.hpp"
#include "Shelf.hpp"
using namespace std;

class Warehouse {
    public:
        Warehouse();
        void addEmployee(Employee* employee);
        void addShelf(Shelf* shelf);
        bool rearrangeShelf(Shelf& shelf);
        bool pickItems(string itemName, int itemCount);
}