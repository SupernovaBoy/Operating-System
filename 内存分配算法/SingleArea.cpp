#include "SingleArea.h"


SingleArea::SingleArea(int address, int size, std::string name, std::string state, SingleArea* pre, SingleArea* post) {
    this->address = address;
    this->size = size;
    this->PreArea = pre;
    this->PostArea = post;
    this->state = state;
    this->JobName = name;
}
SingleArea::~SingleArea() {
    this->address = 0;
    this->size = 0;
    this->PreArea = nullptr;
    this->PostArea = nullptr;
    this->state = "NULL";
}