#include "VisitQueue.hpp"
#include <vector>


void input(vector<string>& page_queue);
void LRU(vector<string>& page_queue, size_t size, size_t data_block);
void FIFO(vector<string>& page_queue, size_t size, size_t data_block);
void print(string name, VisitQueue& visit_queue, string out_name);


int main() {
	size_t data_block = 0;
	cout << "请输入物理块的数量.\n>>> ";
	cin >> data_block;
	vector<string> page_queue;
	input(page_queue);
	LRU(page_queue, page_queue.size() - 1, data_block);
	cout << endl << endl << endl;
	FIFO(page_queue, page_queue.size() - 1, data_block);
	system("pause");
	return 0;
}


void input(vector<string> &page_queue) {
	string page_temp = "None";
	cout << "请输入访问页面队列, 用空格隔开，直至输入-1结束.\n>>>";
	while (page_temp != "-1") {
		cin >> page_temp;
		page_queue.push_back(page_temp);
	}
}


void print(string name, VisitQueue &visit_queue, string out_name) {
	Page* index = visit_queue.head->post;
	cout << "  " << name << "    |    ";
	for (size_t i = 0; i < visit_queue.size; i++) {
		cout << index->name << "    ";
		index = index->post;
	}
	cout << "-> " << out_name;
	cout << endl;
	cout << "       |" << endl;
}


void LRU(vector<string>& page_queue, size_t size, size_t data_block) {
	VisitQueue visit_queue;
	size_t page_fault_num = 1;
	double page_faule_rate;
	cout << "________________" << endl;
	cout << "当前执行LRU算法：" << endl << endl << endl;
	for (size_t i = 0; i < size; i++) {
		string out_name;
		if (visit_queue.is_in_queue(page_queue[i])) {
			Page* new_page = new Page(page_queue[i]);
			visit_queue.delete_page(page_queue[i]);
			visit_queue.set_head(new_page);
			//continue;
		}
		else {
			Page* new_page = new Page(page_queue[i]);
			visit_queue.add_page_from_head(new_page);
			if (visit_queue.size > data_block) {
				out_name = visit_queue.pop();
			}
			if (visit_queue.size < data_block) {
				page_fault_num += 1;
			}
		}
		print(page_queue[i], visit_queue, out_name);
		if (out_name != "") {
			page_fault_num += 1;
		}
	}
	page_faule_rate = (page_fault_num * 1.0) / size;
	cout << "\n\t缺页率为  " << page_faule_rate << endl;
}


void FIFO(vector<string>& page_queue, size_t size, size_t data_block) {
	VisitQueue visit_queue;
	size_t page_fault_num = 1;
	double page_faule_rate;
	cout << "________________" << endl;
	cout << "当前执行FIFO算法：" << endl << endl << endl;
	for (size_t i = 0; i < size; i++) {
		string out_name;
		if (visit_queue.is_in_queue(page_queue[i])) {
			//continue;
		}
		else {
			Page* new_page = new Page(page_queue[i]);
			visit_queue.add_page(new_page);
			if (visit_queue.size > data_block) {
				out_name = visit_queue.delete_head();
			}
			if (visit_queue.size < data_block) {
				page_fault_num += 1;
			}
		}
		print(page_queue[i], visit_queue, out_name);
		if (out_name != "") {
			page_fault_num += 1;
		}
	}
	page_faule_rate = (page_fault_num * 1.0) / size;
	cout << "\n\t缺页率为  " << page_faule_rate << endl;
}

/*
4
1 2 3 4 2 1 5 6 2 1 2 3 7 6 3 2 1 2 3 6 -1


2
1 2 3 4 5 1 2 3 -1
*/
