#include <string>
using namespace std;

class Employee {
    public:
        Employee(string name, bool forkLiftCertificate);
        string getName();
        bool getBusy();
        void setBusy(bool busy);
        bool getForkLiftCertificate();
        void setForkLiftCertificate(bool forkLiftCertificate);
    private:
        string name;
        bool busy;
        bool forkLiftCertificate;
};