#pragma once
#include <string>
#include <vector>

struct Job {
	std::string name;				// 作业名
	int arriveTime;					// 到达时间
	int serviceTime;				// 服务时间

	int startTime;					// 开始执行时间
	int finishTime;					// 完成时间
	int waitTime;					// 等待时间
	int turnaroundTime;				// 周转时间
	double weightedTurnaroundTime;	//带权周转时间

	bool finished;					// 是否完成调度
	int inputOrder;					// 输入顺序

	Job();
};

std::vector<Job> FCFS(std::vector<Job> jobs);
std::vector<Job> SJF(std::vector<Job> jobs);
std::vector<Job> HRRN(std::vector<Job> jobs);