#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() function
#include "../include/catch_amalgamated.hpp"
#include "../include/Employee.hpp"

TEST_CASE("Employee class tests", "[employee]") {
    SECTION("Creating an Employee object") {
        Employee employee(1, "John Doe", true);

        REQUIRE(employee.getID() == 1);
        REQUIRE(employee.getName() == "John Doe");
        REQUIRE(employee.getForkliftCertificate() == true);
        REQUIRE(employee.getBusy() == false);
    }

    SECTION("Updating Employee attributes") {
        Employee employee(1, "Jane Doe", false);

        employee.setID(2);
        employee.setForkliftCertificate(true);
        employee.setBusy(true);

        REQUIRE(employee.getID() == 2);
        REQUIRE(employee.getName() == "Jane Doe");
        REQUIRE(employee.getForkliftCertificate() == true);
        REQUIRE(employee.getBusy() == true);
    }
}