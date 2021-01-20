#include "MemoryArea.h"

MemoryArea::MemoryArea() {
    head = new SingleArea(0, MaxLength, "None", "free", nullptr, nullptr);
}
MemoryArea::~MemoryArea() {
    SingleArea* index = this->head;
    while (index->PostArea != nullptr) {
        SingleArea* temp = index;
        index = index->PostArea;
        delete temp;
    }
    delete index;
}


void MemoryArea::AddSingleArea(int address, int size, std::string state) {
    SingleArea* index = this->head;
    while (index != nullptr) {
        if ((index->address + index->size) == address) {
            break;
        }
        index = index->PostArea;
    }
    if (index == nullptr) {
        cout << "�ڴ�����ַΪ" << address << "���ڴ����ʱ����" << endl;
        return;
    }
    SingleArea* NewSingleArea = new SingleArea(address, size, "None", state);
    NewSingleArea->PreArea = index;
    NewSingleArea->PostArea = index->PostArea;
    if (index->PostArea != nullptr) {
        index->PostArea->PreArea = NewSingleArea;
    }
    index->PostArea = NewSingleArea;
}


void MemoryArea::DeleteSingleArea(int address) {
    SingleArea* index = this->head;
    while (index != nullptr) {
        if (index->address == address) {
            break;
        }
        index = index->PostArea;
    }
    if (index == nullptr) {
        cout << "�����ڵ�ַΪ" << address << "���ڴ����" << endl;
        return;
    }
    SingleArea* pre = index->PreArea;
    SingleArea* post = index->PostArea;
    //���￼�Ǳ�ɾ������Ϊͷ�������
    if (address == 0) {
        if (post->state == "free") {
            index->size += post->size;
            index->state = "free";
            index->JobName = "None";
            index->PostArea = post->PostArea;
            post->PostArea->PreArea = index;
            post->PreArea = nullptr;
            post->PostArea = nullptr;
            delete post;
            return;
        }
        else if (post->state == "occupied") {
            index->JobName = "None";
            index->state = "free";
            return;
        }
    }
    //���￼�Ǳ�ɾ������Ϊβ�������
    if (post == nullptr) {
        //ǰһ��Ϊ���з���
        if (pre->state == "free") {
            pre->size += index->size;
            pre->state = "free";
            pre->JobName = "None";
            pre->PostArea = post;
            index->PreArea = nullptr;
            index->PostArea = nullptr;
            delete index;
            return;
        }
        //ǰһ���ѱ�ռ��
        index->JobName = "None";
        index->state = "free";
        return;
    }
    //���￼�Ǳ�ɾ������Ϊ�м�����
    //1. ǰ����ڿ��з������治����
    if (pre->state == "free" && post->state == "occupied") {
        pre->size += index->size;
        pre->PostArea = post;
        post->PreArea = pre;
        index->PreArea = nullptr;
        index->PostArea = nullptr;
        delete index;
        return;
    }
    //2. ������ڿ��з���ǰ�治����
    else if (pre->state == "occupied" && post->state == "free") {
        post->address = index->address;
        post->size += index->size;
        pre->PostArea = post;
        post->PreArea = pre;
        index->PreArea = nullptr;
        index->PostArea = nullptr;
        delete index;
        return;
    }
    //3. ǰ�󶼴��ڿ��з���
    else if (pre->state == "free" && post->state == "free") {
        pre->size = pre->size + index->size + post->size;
        pre->PostArea = post->PostArea;
        if (post->PostArea != nullptr) {
            post->PostArea->PreArea = pre;
        }
        index->PreArea = nullptr;
        index->PostArea = nullptr;
        post->PreArea = nullptr;
        post->PostArea = nullptr;
        delete index;
        delete post;
        return;
    }
    else if (pre->state == "occupied" && post->state == "occupied") {
        index->JobName = "None";
        index->state = "free";
        return;
    }
}

