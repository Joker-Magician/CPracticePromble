#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>

#include "scheduler.h"

// 显示与输入输出
void showMenu();
void inputJobs(std::vector<Job>& jobs);
void showOriginalJobs(const std::vector<Job>& jobs);

// 结果输出
void printGanttChart(const std::vector<Job>& result);
void printResult(const std::vector<Job>& result, const std::string& algorithmName);
void compareAlgorithms(const std::vector<Job>& jobs);