// Followed Catch2 tutorial: https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top

#define CATCH_CONFIG_MAIN
#include "../include/catch_amalgamated.hpp"
#include "../include/Employee.hpp"
#include "../include/Shelf.hpp"
#include "../include/Task.hpp"
#include "../include/Pallet.hpp"
#include "../include/Warehouse.hpp"

TEST_CASE("Employee class tests", "[employee]") {
    SECTION("Creating an Employee object") {
        Employee employee(1, "Jan Lul", true);

        REQUIRE(employee.getID() == 1);
        REQUIRE(employee.getName() == "Jan Lul");
        REQUIRE(employee.getForkliftCertificate() == true);
        REQUIRE(employee.getBusy() == false);
    }

    SECTION("Updating Employee attributes") {
        Employee employee(1, "Joe Mama", false);

        employee.setID(2);
        employee.setForkliftCertificate(true);
        employee.setBusy(true);

        REQUIRE(employee.getID() == 2);
        REQUIRE(employee.getName() == "Joe Mama");
        REQUIRE(employee.getForkliftCertificate() == true);
        REQUIRE(employee.getBusy() == true);
    }
}

TEST_CASE("Pallet class initialization and basic functions", "[Pallet]") {
    Pallet pallet("Appelflappie", 10, 5);

    SECTION("Pallet initialization") {
        REQUIRE(pallet.getItemName() == "Appelflappie");
        REQUIRE(pallet.getItemCount() == 5);
        REQUIRE(pallet.getRemainingSpace() == 5);
        REQUIRE_FALSE(pallet.isFull());
        REQUIRE_FALSE(pallet.isEmpty());
    }

    SECTION("Taking one item from the pallet") {
        REQUIRE(pallet.takeOne() == true);
        REQUIRE(pallet.getItemCount() == 4);
        REQUIRE(pallet.getRemainingSpace() == 6);
    }

    SECTION("Adding one item to the pallet") {
        REQUIRE(pallet.putOne() == true);
        REQUIRE(pallet.getItemCount() == 6);
        REQUIRE(pallet.getRemainingSpace() == 4);
    }

    SECTION("Pallet reaching full capacity") {
        pallet.putOne(); // 5 -> 6
        pallet.putOne(); // 6 -> 7
        pallet.putOne(); // 7 -> 8
        pallet.putOne(); // 8 -> 9
        pallet.putOne(); // 9 -> 10
        REQUIRE(pallet.isFull());
        REQUIRE_FALSE(pallet.putOne());
    }

    SECTION("Pallet reaching empty state") {
        pallet.takeOne(); // 5 -> 4
        pallet.takeOne(); // 4 -> 3
        pallet.takeOne(); // 3 -> 2
        pallet.takeOne(); // 2 -> 1
        pallet.takeOne(); // 1 -> 0
        REQUIRE(pallet.isEmpty());
        REQUIRE_FALSE(pallet.takeOne());
    }

    SECTION("Reallocation of an empty pallet") {
        Pallet emptyPallet("Empty", 5, 0);
        REQUIRE(emptyPallet.reallocateEmptyPallet("Perensappie", 10, 3));
        REQUIRE(emptyPallet.getItemName() == "Perensappie");
        REQUIRE(emptyPallet.getItemCount() == 3);
        REQUIRE(emptyPallet.getRemainingSpace() == 7);
    }

    SECTION("Reallocation of a non-empty pallet") {
        REQUIRE_FALSE(pallet.reallocateEmptyPallet("Perensappie", 10, 3));
    }

    SECTION("Checking if the pallet has the specified item") {
        REQUIRE(pallet.hasItem("Appelflappie"));
        REQUIRE_FALSE(pallet.hasItem("ItemB"));
    }
}

TEST_CASE("Shelf class initialization and basic functions", "[Shelf]") {
    Shelf shelf;
    Pallet palletA("Appelflappie", 10, 5);
    Pallet palletB("ItemB", 10, 5);

    SECTION("Shelf initialization") {
        REQUIRE(shelf.isEmpty());
        REQUIRE_FALSE(shelf.isFull());
        REQUIRE_FALSE(shelf.hasItem("Appelflappie"));
        REQUIRE(shelf.getItemCount("Appelflappie") == 0);
    }

    SECTION("Inserting and removing pallets") {
        REQUIRE(shelf.insertPallet(0, &palletA));
        REQUIRE_FALSE(shelf.isEmpty());
        REQUIRE(shelf.hasItem("Appelflappie"));
        REQUIRE(shelf.getItemCount("Appelflappie") == 5);
        REQUIRE(shelf.removePallet(0));
        REQUIRE(shelf.isEmpty());
        REQUIRE_FALSE(shelf.hasItem("Appelflappie"));
        REQUIRE(shelf.getItemCount("Appelflappie") == 0);
    }

    SECTION("Shelf reaching full capacity") {
        shelf.insertPallet(0, &palletA);
        shelf.insertPallet(1, &palletB);
        shelf.insertPallet(2, &palletA);
        shelf.insertPallet(3, &palletB);
        REQUIRE(shelf.isFull());
        REQUIRE_FALSE(shelf.insertPallet(0, &palletA));
    }

    SECTION("Getting slot status") {
        shelf.insertPallet(0, &palletA);
        shelf.insertPallet(1, &palletB);
        std::array<bool, 4> slotStatus = shelf.getSlotStatus();
        REQUIRE(slotStatus[0] == true);
        REQUIRE(slotStatus[1] == true);
        REQUIRE(slotStatus[2] == false);
        REQUIRE(slotStatus[3] == false);
    }

    SECTION("Sorting pallets") {
        Pallet palletC("Sinasappie", 10, 1);
        Pallet palletD("Mangopappie", 10, 9);
        shelf.insertPallet(0, &palletD);
        shelf.insertPallet(1, &palletA);
        shelf.insertPallet(2, &palletC);
        shelf.insertPallet(3, &palletB);
        shelf.sortPallets();
        REQUIRE(shelf.pallets[0]->getItemCount() == 1);
        REQUIRE(shelf.pallets[1]->getItemCount() == 5);
        REQUIRE(shelf.pallets[2]->getItemCount() == 5);
        REQUIRE(shelf.pallets[3]->getItemCount() == 9);
    }
}

TEST_CASE("Task: rearrangeShelf") {
    Employee employee1(0, "Jan Lul", true);
    std::vector<Shelf*> shelves;
    Shelf shelf1 = Shelf();
    Shelf shelf2 = Shelf();
    shelves.push_back(&shelf1);
    shelves.push_back(&shelf2);
    Pallet* pallet1 = new Pallet("Appelflappie", 10, 5);
    Pallet* pallet2 = new Pallet("Perensappie", 10, 3);
    shelf1.insertPallet(0, pallet1);
    shelf1.insertPallet(1, pallet2);

    rearrangeShelf task1 = rearrangeShelf(0, 0, true);

    SECTION("Return true if task is run successfully") {
        REQUIRE(task1.runTask(employee1, shelves) == true);
    }

    SECTION("Test if shelf is sorted") {
        task1.runTask(employee1, shelves);
        REQUIRE(shelf1.pallets[0]->getItemName() == "Perensappie");
        REQUIRE(shelf1.pallets[1]->getItemName() == "Appelflappie");
    }

    SECTION("Return false if employee is busy") {
        employee1.setBusy(true);
        REQUIRE(task1.runTask(employee1, shelves) == false);
    }

    SECTION("Return false if employee does not have a forklift certificate") {
        employee1.setForkliftCertificate(false);
        REQUIRE(task1.runTask(employee1, shelves) == false);
    }

    SECTION("Return false if shelf does not exist") {
        rearrangeShelf task2 = rearrangeShelf(0, 2, true);
        REQUIRE(task2.runTask(employee1, shelves) == false);
    }
}

TEST_CASE("Task: pickItems") {
    Employee employee1(0, "Jan Lul", false);
    std::vector<Shelf*> shelves;
    Shelf shelf1 = Shelf();
    shelves.push_back(&shelf1);
    Pallet* pallet1 = new Pallet("Appelflappie", 10, 5);
    shelf1.insertPallet(0, pallet1);

    pickItems task1(1, "Appelflappie", 10, false);

    SECTION("Return false if employee is busy") {
        employee1.setBusy(true);
        REQUIRE(task1.runTask(employee1, shelves) == false);
    }

    SECTION("Return false if forklift is required and employee does not have a forklift certificate") {
        task1.setRequiresForklift(true);
        employee1.setForkliftCertificate(false);
        REQUIRE(task1.runTask(employee1, shelves) == false);
    }

    SECTION("Return false if item count is not valid") {
        pickItems task2 = pickItems(0, "Appelflappie", 0, false);
        REQUIRE(task2.runTask(employee1, shelves) == false);
    }

    SECTION("Return false if item does not exist on any shelf") {
        pickItems task2 = pickItems(1, "Mangopappie", 10, false);
        REQUIRE(task2.runTask(employee1, shelves) == false);
    }

    SECTION("Return false if there are not enough items on the shelves") {
        pickItems task2 = pickItems(1, "Appelflappie", 30, false);
        REQUIRE(task2.runTask(employee1, shelves) == false);
    }

    SECTION("Return true if task is successful") {
        shelf1.removePallet(0);
        Pallet* pallet1 = new Pallet("Appelflappie", 15, 11);
        shelf1.insertPallet(0, pallet1);
        REQUIRE(task1.runTask(employee1, shelves) == true);
    }
}

TEST_CASE("Warehouse class tests", "[warehouse]") {
    Warehouse warehouse = Warehouse();
    Employee* employee1 = new Employee(0, "Jan Lul", true);
    Employee* employee2 = new Employee(1, "Joe Mama", false);
    Shelf* shelf1 = new Shelf();
    Pallet* pallet1 = new Pallet("Appelflappie", 10, 5);
    Pallet* pallet2 = new Pallet("Bananendrappie", 10, 2);
    rearrangeShelf* rearrangeShelfTask = new rearrangeShelf(0, 0, 1);
    pickItems* pickItemsTask = new pickItems(1, "Appelflappie", 3, false);
    shelf1->insertPallet(0, pallet1);
    shelf1->insertPallet(1, pallet2);
    warehouse.addShelf(shelf1);
    warehouse.addEmployee(employee1);
    warehouse.addEmployee(employee2);
    warehouse.addTask(rearrangeShelfTask);
    warehouse.addTask(pickItemsTask);

    SECTION("Test getTotalTaskStatus") {
        REQUIRE(warehouse.getTotalTaskStatus() == TaskStatus::todo);
    }

    SECTION("Test false if no suitable employee is found") {
        employee1->setBusy(true);
        warehouse.performOneTask(0);
        REQUIRE(warehouse.getTotalTaskStatus() == TaskStatus::failed);
    }

    SECTION("Test false if suitable employee is found") {
        warehouse.performOneTask(0);
        warehouse.performOneTask(1);
        REQUIRE(warehouse.getTotalTaskStatus() == TaskStatus::finished);
    }

    SECTION("Test run all tasks successfully") {
        warehouse.performAllTasks();
        REQUIRE(warehouse.getTotalTaskStatus() == TaskStatus::finished);
    }

    SECTION("Test unsuccessful run all tasks") {
        employee1->setBusy(true);
        warehouse.performAllTasks();
        REQUIRE(warehouse.getTotalTaskStatus() == TaskStatus::failed);
    }

    SECTION("Test if rearrangeShelf task is run successfully") {
        warehouse.performOneTask(0);
        REQUIRE(shelf1->pallets[0]->getItemName() == "Bananendrappie");
        REQUIRE(shelf1->pallets[1]->getItemName() == "Appelflappie");
    }

    SECTION("Test if pickItems task is run successfully") {
        warehouse.performOneTask(1);
        REQUIRE(shelf1->pallets[0]->getItemCount() == 2);
    }
}