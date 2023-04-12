#pragma once
#include <string>

class IContainer {
    public:
        virtual bool isFull() = 0;
        virtual bool isEmpty() = 0;
        virtual bool hasItem(std::string item) = 0;
};