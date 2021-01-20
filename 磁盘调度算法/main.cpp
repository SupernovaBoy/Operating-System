#include <iostream>
#include <vector>
using namespace std;


void input_array(vector<int>& request_queue, int& number_of_track);
void print_result(const vector<int>& final_queue);
void SCAN(vector<int>& request_queue,const int& number_of_track);
void SSTF(vector<int>& request_queue,const int& number_of_track);


int main() {
	int number_of_track;
	vector<int> request_queue;
	input_array(request_queue, number_of_track);
	SSTF(request_queue, number_of_track);
	SCAN(request_queue, number_of_track);
	system("pause");
	return 0;
}


void input_array(vector<int>& request_queue, int& number_of_track) {
	cout << "请输入磁盘的磁道数:\n>>> ";
	cin >> number_of_track;
	cout << "请输入磁盘的磁道请求队列, 以 -1 为结束标志:\n>>> ";
	int temp_request;
	while (cin >> temp_request) {
		if ((temp_request > number_of_track || temp_request < 0) && temp_request != -1) {
			cout << "请求号 " << temp_request << " 非法，已自动忽略" << endl;
			continue;
		}
		if (temp_request == -1) {
			break;
		}
		request_queue.push_back(temp_request);
	}
}


void print_result(const vector<int>& final_queue) {
	cout << "\n\t磁道号\t移动磁道数\n";
	cout << "\t" << final_queue[0] << "\t0\n";
	int sum = 0;
	for (size_t i = 1; i < final_queue.size(); i++) {
		int move_size = abs(final_queue[i] - final_queue[i - 1]);
		cout << "\t" << final_queue[i] << "\t" << move_size << "\n";
		sum += move_size;
	}
	cout << "\n总移动磁道数:" << sum << "    平均移动磁道数:" << sum * (1.0) / final_queue.size();
	cout << "\n\n\n";
}

//最短寻路算法
void SSTF(vector<int>& request_queue,const int& number_of_track) {
	cout << "________________________\n当前执行 SSTF 算法：\n\n";
	int sum = 0;
	int min = number_of_track;
	int move_size = 0;
	int index = 0;
	int current_number = request_queue[0];
	vector<int> final_queue;
	vector<int> flag_queue;
	for (size_t i = 0; i < request_queue.size(); i++) {
		flag_queue.push_back(0);
	}
	for (size_t i = 0; i < request_queue.size(); i++) {
		min = number_of_track;
		for (size_t j = 0; j < request_queue.size(); j++) {
			if (flag_queue[j] == 0) {
				move_size = abs(current_number - request_queue[j]);
				if (move_size < min) {
					min = move_size;
					index = j;
				}
			}
		}
		sum += min;
		flag_queue[index] = 1;
		final_queue.push_back(request_queue[index]);
		current_number = request_queue[index];
	}
	print_result(final_queue);
}

//电梯扫描算法
void SCAN(vector<int>& request_queue,const int& number_of_track) {
	cout << "________________________\n当前执行 SCAN 算法：\n\n";
	string direction;
	vector<int> final_queue;
	int first_number = request_queue[0];
	cout << "请输入初始的移动方向(high/low):\n>>> ";
	while (true) {
		cin >> direction;
		if (direction == "high" || direction == "low") {
			break;
		}
		cout << "输入错误，请重新输入\n>>> ";
	}
	//给原始请求队列先从小到大排序
	for (size_t i = 0; i < request_queue.size(); i++) {
		int min = request_queue[i];
		for (size_t j = i + 1; j < request_queue.size(); j++) {
			if (request_queue[j] < min) {
				min = request_queue[j];
				int temp = request_queue[i];
				request_queue[i] = request_queue[j];
				request_queue[j] = temp;
			}
		}
	}
	//假如初始方向向往高处走
	if (direction == "high") {
		bool flag = false;
		int index = 0;
		for (size_t i = 0; i < request_queue.size(); i++) {
			if (request_queue[i] == first_number) {
				index = i;
				flag = true;
			}
			if (flag) {
				final_queue.push_back(request_queue[i]);
			}
		}
		for (int i = index - 1; i >= 0; i--) {
			final_queue.push_back(request_queue[i]);
		}
	}
	//假如初始方向向往低处走
	else {
		bool flag = false;
		int index = 0;
		for (size_t i = 0; i < request_queue.size(); i++) {
			if (request_queue[i] == first_number) {
				index = i;
				break;
			}
		}
		for (int i = index; i >= 0; i--) {
			final_queue.push_back(request_queue[i]);
		}
		for (size_t i = index + 1; i < request_queue.size(); i++) {
			final_queue.push_back(request_queue[i]);
		}
	}
	print_result(final_queue);
}



