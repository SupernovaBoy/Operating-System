#pragma once
#include <string>
#include <iostream>
#define MaxLength 512
using std::cout;
using std::endl;



class SingleArea {
public:
    SingleArea(int address = 0, int size = 0, std::string name = "None", std::string state = "NULL", SingleArea* pre = nullptr, SingleArea* post = nullptr);
    ~SingleArea();
    std::string state;
    std::string JobName;
    int address;
    int size;
    SingleArea* PreArea;
    SingleArea* PostArea;
};