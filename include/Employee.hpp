#pragma once

#include <string>

class Employee {
    public:
        Employee(int id, std::string name, bool forkliftCertificate);
        std::string getName();
        bool getBusy();
        void setBusy(bool busy);
        bool getForkliftCertificate();
        void setForkliftCertificate(bool forkliftCertificate);
        int getID();
        void setID(int id);
    private:
        std::string name;
        bool busy;
        bool forkliftCertificate;
        int id;
};
