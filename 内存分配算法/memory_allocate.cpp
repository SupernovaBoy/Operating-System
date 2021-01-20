#include <iostream>
#include <vector>
#include "MemoryArea.h"
#include "Job.h"
using namespace std;

void PrintArea(SingleArea* head);
void FirstFit(Job* JobArray, int JobNum, int choice);
void BestFit(Job* JobArray, int JobNum, int choice);
void WorstFit(Job* JobArray, int JobNum, int choice);
int GetAddress(SingleArea* head, string name);
int GetBestAddress(SingleArea* head, int size);
int GetWorstAddress(SingleArea* head, int size);


int main() {
    int JobNum;
    int choice;
    cout << "请输入作业的个数\n>>> ";
    cin >> JobNum;
    Job* JobArray = new Job[JobNum];
    for (int i = 0; i < JobNum; i++) {
        cout << "请输入第 " << i + 1 << " 个作业的名称、大小、分配“req”或者释放“rel”\n>>> ";
        cin >> JobArray[i].name;
        cin >> JobArray[i].size;
        cin >> JobArray[i].action;
    }
    cout << "是否仅显示内存分配结果？(1/0)\n>>> ";
    cin >> choice;
    FirstFit(JobArray, JobNum, choice);
    cout << endl << endl << endl;
    BestFit(JobArray, JobNum, choice);
    cout << endl << endl << endl;
    WorstFit(JobArray, JobNum, choice);
    delete[] JobArray;
    system("pause");
    return 0;
}


void PrintArea(SingleArea *head) {
    SingleArea* index = head;
    int count = 1;
    cout << "\t已分配的空间" << endl;
    cout << "\t\t作业名\t地址\t大小" << endl;
    while (index != nullptr) {
        if (index->state == "occupied") {
            
            cout << "\tNo." << count << "\t" << index->JobName << "\t" << index->address << "\t" << index->size << "\t" << endl;
            count++;
        }
        index = index->PostArea;
    }
    cout << endl;
    count = 1;
    index = head;
    cout << "\t空闲空间" << endl;
    cout << "\t\t地址\t大小" << endl;
    while (index != nullptr) {
        if (index->state == "free") {
            
            cout << "\tNo." << count << "\t" << index->address << "\t" << index->size << endl;
            count++;
        }
        index = index->PostArea;
    }
}


void FirstFit(Job* JobArray, int JobNum, int choice) {
    cout << "————————————————————————————————————————————————————————" << endl;
    cout << "当前执行FF算法" << endl;
    MemoryArea* Memory = new MemoryArea;
    for (int i = 0; i < JobNum; i++) {
        if (JobArray[i].action == "req") {
            SingleArea* index = Memory->head;
            while (index != nullptr) {
                if (index->state == "free" && index->size >= JobArray[i].size) {
                    break;
                }
                index = index->PostArea;
            }
            if (index == nullptr) {
                cout << "FF算法中不满足符合作业" << JobArray[i].name << "条件的分区, 请重新输入作业队列" << endl;
                delete index;
                delete Memory;
                return;
            }
            int TempSize = index->size;
            index->JobName = JobArray[i].name;
            index->size = JobArray[i].size;
            index->state = "occupied";
            Memory->AddSingleArea(index->address + index->size, TempSize - JobArray[i].size, "free");
        }
        else if (JobArray[i].action == "rel") {
            SingleArea* index = Memory->head;
            Memory->DeleteSingleArea(GetAddress(index, JobArray[i].name));
        }
        else {
            cout << "作业 " << JobArray[i].name << " 的请求动作错误" << endl;
            delete Memory;
            return;
        }
        if (choice == 0) {
            cout << "执行作业 " << JobArray[i].name << " 大小为 " << JobArray[i].size << " 的 " << JobArray[i].action << " 任务" << "后的内存分区情况：" << endl << endl;
            PrintArea(Memory->head);
            cout << endl << endl << endl << endl;
        }
    }
    if (choice != 0) {
        PrintArea(Memory->head);
        cout << endl << endl;
    }
    delete Memory;
}



void BestFit(Job* JobArray, int JobNum, int choice) {
    cout << "————————————————————————————————————————————————————————" << endl;
    cout << "当前执行BF算法" << endl;
    MemoryArea* Memory = new MemoryArea;
    for (int i = 0; i < JobNum; i++) {
        if (JobArray[i].action == "req") {
            SingleArea* index = Memory->head;
            int address = GetBestAddress(index, JobArray[i].size);
            while (index != nullptr) {
                if (index->address == address) {
                    break;
                }
                index = index->PostArea;
            }
            if (index == nullptr) {
                cout << "BF算法中不满足符合作业" << JobArray[i].name << "条件的分区, 请重新输入作业队列" << endl;
                delete index;
                delete Memory;
                return;
            }
            int TempSize = index->size;
            index->JobName = JobArray[i].name;
            index->size = JobArray[i].size;
            index->state = "occupied";
            Memory->AddSingleArea(index->address + index->size, TempSize - JobArray[i].size, "free");
        }
        else if (JobArray[i].action == "rel") {
            SingleArea* index = Memory->head;
            Memory->DeleteSingleArea(GetAddress(index, JobArray[i].name));
        }
        else {
            cout << "作业 " << JobArray[i].name << " 的请求动作错误" << endl;
            delete Memory;
            return;
        }
        if (choice == 0) {
            cout << "执行作业 " << JobArray[i].name << " 大小为 " << JobArray[i].size << " 的 " << JobArray[i].action << " 任务" << "后的内存分区情况：" << endl << endl;
            PrintArea(Memory->head);
            cout << endl << endl << endl << endl;
        }
    }
    if (choice != 0) {
        PrintArea(Memory->head);
        cout << endl << endl;
    }
    delete Memory;
}


void WorstFit(Job* JobArray, int JobNum, int choice) {
    cout << "————————————————————————————————————————————————————————" << endl;
    cout << "当前执行WF算法" << endl;
    MemoryArea* Memory = new MemoryArea;
    for (int i = 0; i < JobNum; i++) {
        if (JobArray[i].action == "req") {
            SingleArea* index = Memory->head;
            int address = GetWorstAddress(index, JobArray[i].size);
            while (index != nullptr) {
                if (index->address == address) {
                    break;
                }
                index = index->PostArea;
            }
            if (index == nullptr) {
                cout << "WF算法中不满足符合作业" << JobArray[i].name << "条件的分区, 请重新输入作业队列" << endl;
                delete index;
                delete Memory;
                return;
            }
            int TempSize = index->size;
            index->JobName = JobArray[i].name;
            index->size = JobArray[i].size;
            index->state = "occupied";
            Memory->AddSingleArea(index->address + index->size, TempSize - JobArray[i].size, "free");
        }
        else if (JobArray[i].action == "rel") {
            SingleArea* index = Memory->head;
            Memory->DeleteSingleArea(GetAddress(index, JobArray[i].name));
        }
        else {
            cout << "作业 " << JobArray[i].name << " 的请求动作错误" << endl;
            delete Memory;
            return;
        }
        if (choice == 0) {
            cout << "执行作业 " << JobArray[i].name << " 大小为 " << JobArray[i].size << " 的 " << JobArray[i].action << " 任务" << "后的内存分区情况：" << endl << endl;
            PrintArea(Memory->head);
            cout << endl << endl << endl << endl;
        }
    }
    if (choice != 0) {
        PrintArea(Memory->head);
        cout << endl << endl;
    }
    delete Memory;
}


int GetBestAddress(SingleArea* head, int size) {
    SingleArea* index = head;
    vector<size_t> AbsValue;
    size_t IndexNum;
    size_t count = 0;
    while (index != nullptr) {
        if (index->state == "occupied") {
            AbsValue.push_back(MaxLength);
        }
        else {
            AbsValue.push_back(index->size - size);
        }
        index = index->PostArea;
    }
    index = head;
    size_t MinValue = AbsValue[0];
    for (size_t i = 1; i < AbsValue.size(); i++) {
        if (AbsValue[i] < MinValue) {
            MinValue = AbsValue[i];
        }
    }
    for (IndexNum = 0; IndexNum < AbsValue.size(); IndexNum++) {
        if (AbsValue[IndexNum] == MinValue) {
            break;
        }
    }
    while (index != nullptr) {
        if (count == IndexNum) {
            break;
        }
        count++;
        index = index->PostArea;
    }
    if (index == nullptr) {
        return -1;
    }
    else if (AbsValue[IndexNum] > MaxLength) {
        return -1;
    }
    return index->address;
}


int GetWorstAddress(SingleArea* head, int size) {
    SingleArea* index = head;
    vector<int> AbsValue;
    int IndexNum;
    int count = 0;
    while (index != nullptr) {
        if (index->state == "occupied") {
            AbsValue.push_back(-1);
        }
        else {
            AbsValue.push_back(index->size - size);
        }
        index = index->PostArea;
    }
    index = head;
    int MaxValue = AbsValue[0];
    for (int i = 1; i < AbsValue.size(); i++) {
        if (AbsValue[i] > MaxValue) {
            MaxValue = AbsValue[i];
        }
    }
    for (IndexNum = 0; IndexNum < AbsValue.size(); IndexNum++) {
        if (AbsValue[IndexNum] == MaxValue) {
            break;
        }
    }
    while (index != nullptr) {
        if (count == IndexNum) {
            break;
        }
        count++;
        index = index->PostArea;
    }
    if (index == nullptr) {
        return -1;
    }
    else if (AbsValue[IndexNum] < 0) {
        return -1;
    }
    return index->address;
}


int GetAddress(SingleArea* head, string name) {
    while (head != nullptr) {
        if (head->JobName == name) {
            return head->address;
            break;
        }
        head = head->PostArea;
    }
    if (head == nullptr) {
        cout << "不存在 " << name << " 作业." << endl;
    }
    return 0;
}


/*
8
1 300 req
2 100 req
1 300 rel
3 150 req
4 30 req
5 40 req
6 60 req
4 30 rel
1
*/
