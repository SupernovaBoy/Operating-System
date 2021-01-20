#include <iostream>
#include <queue>
using namespace std;

class Process {
public:
	Process() {
		string name = "None";
		create_time = 0;
		execute_time = 0;
		complete_time = 0;
		turnover_time = 0;
		weighted_turnover_time = 0;
	}
	~Process() {
		string name = "None";
		create_time = 0;
		execute_time = 0;
		complete_time = 0;
		turnover_time = 0;
		weighted_turnover_time = 0;
	}
	int create_time;
	int execute_time;
	int complete_time;
	int turnover_time;
	double weighted_turnover_time;
	string name;
};


void input_process(Process* process_array, int process_num) {
	for (int i = 0; i < process_num; i++) {
		cout << "请输入进程 " << i + 1 << " 的进程名、进程创建时间、进程要求执行时间, 使用空格隔开\n>>> ";
		cin >> process_array[i].name;
		cin >> process_array[i].create_time;
		cin >> process_array[i].execute_time;
	}
}


void print_process(Process* process_array, int process_num) {
	double average_turnover_time = 0;
	double average_weighted_turnover_time = 0;
	double turnover_time_sum = 0;
	double weighted_turnover_time_sum = 0;
	for (int i = 0; i < process_num; i++) {
		turnover_time_sum += process_array[i].turnover_time;
		weighted_turnover_time_sum += process_array[i].weighted_turnover_time;
	}
	average_turnover_time = turnover_time_sum * (1.0) / process_num;
	average_weighted_turnover_time = weighted_turnover_time_sum * (1.0) / process_num;
	for (int i = 0; i < process_num; i++) {
		int min = process_array[i].create_time;
		for (int j = i + 1; j < process_num; j++) {
			if (process_array[j].create_time < min) {
				Process temp = process_array[i];
				process_array[i] = process_array[j];
				process_array[j] = temp;
			}
		}
	}
	
	cout << "进程名       创建时间       运行时间       完成时间       周转时间       带权周转时间" << endl;
	for (int i = 0; i < process_num; i++) {
		cout << "  "<< process_array[i].name << "\t\t" \
			<< process_array[i].create_time << "\t\t" \
			<< process_array[i].execute_time << "\t\t"\
			<< process_array[i].complete_time << "\t\t" \
			<< process_array[i].turnover_time << "\t\t" \
			<< process_array[i].weighted_turnover_time;
		cout << endl;
	}
	cout << endl;
	cout << "周转时间总和:\t" << turnover_time_sum \
		<< "\t带权周转时间总和:\t" << weighted_turnover_time_sum << endl;
	cout << "平均周转时间:\t" << average_turnover_time \
		<< "\t平均带权周转时间:\t" << average_weighted_turnover_time << endl;
	cout << endl;
}



void FCFS(Process *process_array, int process_num) {
	for (int i = 0; i < process_num; i++) {
		int min = process_array[i].create_time;
		for (int j = i+1; j < process_num; j++) {
			if (process_array[j].create_time < min) {
				Process temp = process_array[i];
				process_array[i] = process_array[j];
				process_array[j] = temp;
			}
		}
	}
	for (int i = 0; i < process_num; i++) {
		int execute_time_sum = 0;
		for (int j = 0; j < i; j++) {
			execute_time_sum += process_array[j].execute_time;
		}
		process_array[i].complete_time = \
			execute_time_sum + process_array[i].execute_time;
		process_array[i].turnover_time = \
			process_array[i].complete_time - process_array[i].create_time;
		process_array[i].weighted_turnover_time = \
			(process_array[i].turnover_time) * (1.0) / process_array[i].execute_time;
	}
	cout << endl;
	cout << "FCFS: ";
	for (int i = 0; i < process_num; i++)
		for (int j = 0; j < process_array[i].execute_time; j++)
			cout << process_array[i].name << " ";
	cout << endl;
	print_process(process_array, process_num);
	cout << endl;
}







void SJF(Process* process_array, int process_num) {
	for (int i = 0; i < process_num; i++) {
		int min = process_array[i].create_time;
		for (int j = i + 1; j < process_num; j++) {
			if (process_array[j].create_time < min) {
				Process temp = process_array[i];
				process_array[i] = process_array[j];
				process_array[j] = temp;
			}
		}
	}
	process_array[0].complete_time = process_array[0].execute_time;
	process_array[0].turnover_time = \
		process_array[0].complete_time - process_array[0].create_time;
	process_array[0].weighted_turnover_time = \
		(process_array[0].turnover_time) * (1.0) / process_array[0].execute_time;

	for (int i = 1, execute_time_sum = process_array[0].execute_time; i < process_num; i++) {
		for (int j = i + 1; j < process_num; j++) {
			if (process_array[j].create_time < process_array[i].complete_time \
				&& process_array[j].execute_time < process_array[i].execute_time ) {
				Process temp = process_array[i];
				process_array[i] = process_array[j];
				process_array[j] = temp;
			}
		}
		process_array[i].complete_time = \
			execute_time_sum + process_array[i].execute_time;
		process_array[i].turnover_time = \
			process_array[i].complete_time - process_array[i].create_time;
		process_array[i].weighted_turnover_time = \
			(process_array[i].turnover_time) * (1.0) / process_array[i].execute_time;
		execute_time_sum += process_array[i].execute_time;
	}
	
	cout << "SJF: ";
	for (int i = 0; i < process_num; i++)
		for (int j = 0; j < process_array[i].execute_time; j++)
			cout << process_array[i].name << " ";
	cout << endl;
	print_process(process_array, process_num);
}






void RR(Process* process_array, int process_num, int time_slice) {
	vector<string> final_queue;
	queue<Process> process_queue;
	int i = 1;
	int current_time;
	int temp_time;
	bool first = true;
	for (int i = 0; i < process_num; i++) {
		int min = process_array[i].create_time;
		for (int j = i + 1; j < process_num; j++) {
			if (process_array[j].create_time < min) {
				Process temp = process_array[i];
				process_array[i] = process_array[j];
				process_array[j] = temp;
			}
		}
	}
	process_queue.push(process_array[0]);
	if (process_queue.front().execute_time >= time_slice)
		current_time = time_slice;
	else
		current_time = process_queue.front().execute_time;
	while (!process_queue.empty()) {
		for (int j = i; j < process_num; j++)
			if (process_array[j].create_time <= current_time) {
				process_queue.push(process_array[j]);
				i++;
			}
		if (process_queue.front().execute_time >= time_slice)
			temp_time = time_slice;
		else
			temp_time = process_queue.front().execute_time;

		process_queue.front().execute_time -= temp_time;
		final_queue.push_back(process_queue.front().name);

		if (process_queue.front().execute_time <= 0) {
			for (int temp = 0; temp < process_num; temp++) {
				if (process_array[temp].name == process_queue.front().name && first == false)
					process_array[temp].complete_time = current_time + temp_time;
				else if (process_array[temp].name == process_queue.front().name)
					process_array[temp].complete_time = current_time;	
			}
			process_queue.pop();
		}
		else {
			process_queue.push(process_queue.front());
			process_queue.pop();
		}
		if (!first) {
			current_time += temp_time;
		}
		first = false;
	}
	for (int i = 0; i < process_num; i++) {
		process_array[i].turnover_time = \
			process_array[i].complete_time - process_array[i].create_time;
		process_array[i].weighted_turnover_time = \
			(process_array[i].turnover_time) * (1.0) / process_array[i].execute_time;
	}
	cout << endl;
	cout << "RR: ";
	int queue_size = final_queue.size();
	for (int i = 0; i < queue_size; i++)
		cout << final_queue[i] << " ";
	cout << endl;
	print_process(process_array, process_num);
}








int main() {
	int process_num;
	int time_slice;
	cout << "请输入进程数目\n>>> ";
	cin >> process_num;
	cout << "请输入时间片大小\n>>> ";
	cin >> time_slice;
	Process* process_array = new Process[process_num];
	input_process(process_array, process_num);
	FCFS(process_array, process_num);
	SJF(process_array, process_num);
	RR(process_array, process_num, time_slice);
	delete[] process_array;
	return 0;
}


