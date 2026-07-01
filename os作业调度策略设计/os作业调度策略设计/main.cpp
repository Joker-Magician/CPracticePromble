#include "ui.h"

int main() {
	std::vector<Job> jobs;
	int choice = -1;

	while (true) {
		showMenu();

		if (!(std::cin >> choice)) {
			std::cout << "输入错误：请输入数字编号。" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		switch (choice) {
		case 1:
			inputJobs(jobs); break;			
		case 2:
			showOriginalJobs(jobs); break;			
		case 3:
			if (jobs.empty()) std::cout << "当前没有作业信息，请先输入作业。" << std::endl;
			else printResult(FCFS(jobs), "FCFS 先来先服务");
			break;
		case 4:
			if (jobs.empty()) std::cout << "当前没有作业信息，请先输入作业。" << std::endl;
			else printResult(SJF(jobs), "SJF 短作业优先");
			break;
		case 5:
			if (jobs.empty()) std::cout << "当前没有作业信息，请先输入作业。" << std::endl;
			else printResult(HRRN(jobs), "HRRN 最高响应比优先");
			break;
		case 6:
			compareAlgorithms(jobs); break;
		case 0:
			std::cout << "程序已退出。" << std::endl; 
			return 0;
		default:
			std::cout << "输入错误：没有该功能编号，请重新选择。" << std::endl;
			break;
		}
	}

	return 0;
}