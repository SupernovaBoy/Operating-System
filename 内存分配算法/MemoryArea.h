#pragma once
#include "SingleArea.h"


class MemoryArea {
public:
    MemoryArea();
    ~MemoryArea();
    void AddSingleArea(int address, int size, std::string state);
    void DeleteSingleArea(int address = 0);
    SingleArea* head;
};