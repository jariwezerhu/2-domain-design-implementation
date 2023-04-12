#include "../include/Employee.hpp"
#include <string>
using namespace std;

Employee::Employee(int id, string name, bool forkliftCertificate) {
    this->id = id;
    this->name = name;
    this->forkliftCertificate = forkliftCertificate;
    this->busy = false;
}

string Employee::getName() {
    return this->name;
}

bool Employee::getBusy() {
    return this->busy;
}

void Employee::setBusy(bool busy) {
    this->busy = busy;
}

bool Employee::getForkliftCertificate() {
    return this->forkliftCertificate;
}

void Employee::setForkliftCertificate(bool forkliftCertificate) {
    this->forkliftCertificate = forkliftCertificate;
}

int Employee::getID() {
    return this->id;
}

void Employee::setID(int id) {
    this->id = id;
}