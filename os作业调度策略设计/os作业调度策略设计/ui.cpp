#include "ui.h"


namespace {
    void clearInputBuffer() { //清理错误输入
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // 判断作业名是否重复
    bool isDuplicateName(const std::vector<Job>& jobs, const std::string& name) {
        for (std::size_t i = 0; i < jobs.size(); i++) {
            if (jobs[i].name == name) {
                return true;
            }
        }
        return false;
    }

    // 计算调度结果的平均等待时间、平均周转时间和平均带权周转时间。
    struct Summary {
        double avgWaitTime;
        double avgTurnaroundTime;
        double avgWeightedTurnaroundTime;
    };

    Summary calculateSummary(const std::vector<Job>& result) {
        Summary summary = { 0.0,0.0,0.0 };
        
        if (result.empty()) {
            return summary;
        }

        for (std::size_t i = 0; i < result.size(); i++) {
            summary.avgWaitTime += result[i].waitTime;
            summary.avgTurnaroundTime += result[i].turnaroundTime;
            summary.avgWeightedTurnaroundTime += result[i].weightedTurnaroundTime;
        }
        summary.avgWaitTime /= result.size();
        summary.avgTurnaroundTime /= result.size();
        summary.avgWeightedTurnaroundTime /= result.size();
        
        return summary;
    }
}

void showMenu()
{
    std::cout << "\n========== 作业调度策略设计 ==========" << std::endl;
    std::cout << "1. 输入作业信息" << std::endl;
    std::cout << "2. 显示原始作业信息" << std::endl;
    std::cout << "3. FCFS 先来先服务调度" << std::endl;
    std::cout << "4. SJF 短作业优先调度" << std::endl;
    std::cout << "5. HRRN 最高响应比优先调度" << std::endl;
    std::cout << "6. 三种算法性能对比" << std::endl;
    std::cout << "0. 退出系统" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "请输入功能编号：";
}

// 输入作业信息
void inputJobs(std::vector<Job>& jobs)
{
    jobs.clear();

    int count = 0;
    while (true) {
        std::cout << "请输入作业数量: ";
        if (std::cin >> count && count > 0) break;
        
        std::cout << "输入错误:作业数量须是正整数" << std::endl;
        clearInputBuffer();
    }

    for (int i = 0; i < count; i++) {
        Job job;
        job.inputOrder = i;
        while (true) {
            std::cout << "请输入第 " << i + 1 << " 个作业名: ";
            std::cin >> job.name;

            if (!isDuplicateName(jobs, job.name)) break;
            std::cout << "输入错误: 作业名重复，请重新输入。" << std::endl;
        }

        while (true) {
            std::cout << "请输入作业 " << job.name << " 的到达时间：";
            if (std::cin >> job.arriveTime && job.arriveTime >= 0) {
                break;
            }

            std::cout << "输入错误：到达时间不能为负数。" << std::endl;
            clearInputBuffer();
        }

        while (true) {
            std::cout << "请输入作业 " << job.name << " 的服务时间：";
            if (std::cin >> job.serviceTime && job.serviceTime > 0) {
                break;
            }

            std::cout << "输入错误：服务时间必须大于0。" << std::endl;
            clearInputBuffer();
        }

        jobs.push_back(job);
    }
    std::cout << "作业信息输入完成！" << std::endl;
}

void showOriginalJobs(const std::vector<Job>& jobs)
{
    if (jobs.empty()) {
        std::cout << "当前没有作业信息，请先输入作业。" << std::endl;
        return;
    }

    std::cout << "\n========== 原始作业信息 ==========" << std::endl;
    std::cout << std::left << std::setw(12) << "作业名"
              << std::setw(12) << "到达时间"
              << std::setw(12) << "服务时间" << std::endl;
    for (std::size_t i = 0; i < jobs.size(); i++) {
        std::cout << std::left << std::setw(12) << jobs[i].name
                  << std::setw(12) << jobs[i].arriveTime
                  << std::setw(12) << jobs[i].serviceTime << std::endl;
    }
}


void printGanttChart(const std::vector<Job>& result)
{
    if (result.empty()) return;

    std::cout << "\n甘特图: " << std::endl;

    int currentTime = 0;
    std::cout << currentTime;

    for (std::size_t i = 0; i < result.size(); i++) {
        if (result[i].startTime > currentTime)
            std::cout << " --空闲-- " << result[i].startTime;

        std::cout << " --" << result[i].name << "-- " << result[i].finishTime;
        currentTime = result[i].finishTime;
    }

    std::cout << std::endl;
}

// 输出调度算法调度顺序、甘特图、结果表格和平均指标等结果
void printResult(const std::vector<Job>& result, const std::string& algorithmName)
{
    if (result.empty()) {
        std::cout << "当前没有可输出的调度结果。" << std::endl;
        return;
    }

    Summary summary = calculateSummary(result);
    std::cout << "\n========== " << algorithmName << " 调度结果 ==========" << std::endl;

    std::cout << "调度顺序：";
    for (std::size_t i = 0; i < result.size(); i++) {
        std::cout << result[i].name;
        if(i+1 < result.size())  std::cout << " -> ";
    }
    std::cout << std::endl;

    printGanttChart(result);
    std::cout << "\n";
    std::cout << std::left << std::setw(12) << "作业名"
              << std::setw(12) << "到达时间"
              << std::setw(12) << "服务时间"
              << std::setw(12) << "开始时间"
              << std::setw(12) << "完成时间"
              << std::setw(12) << "等待时间"
              << std::setw(12) << "周转时间"
              << std::setw(16) << "带权周转时间" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    for (std::size_t i = 0; i < result.size(); i++) {
        std::cout << std::left << std::setw(12) << result[i].name
            << std::setw(12) << result[i].arriveTime
            << std::setw(12) << result[i].serviceTime
            << std::setw(12) << result[i].startTime
            << std::setw(12) << result[i].finishTime
            << std::setw(12) << result[i].waitTime
            << std::setw(12) << result[i].turnaroundTime
            << std::setw(16) << result[i].weightedTurnaroundTime << std::endl;
    }

    std::cout << "\n平均等待时间：" << summary.avgWaitTime << std::endl;
    std::cout << "平均周转时间：" << summary.avgTurnaroundTime << std::endl;
    std::cout << "平均带权周转时间：" << summary.avgWeightedTurnaroundTime << std::endl;
}

// 对比三种调度算法的平均性能指标
void compareAlgorithms(const std::vector<Job>& jobs)
{
    if (jobs.empty()) {
        std::cout << "当前没有作业信息，请先输入作业。" << std::endl;
        return;
    }

    std::vector<Job> fcfsResult = FCFS(jobs);
    std::vector<Job> sjfResult = SJF(jobs);
    std::vector<Job> hrrnResult = HRRN(jobs);

    Summary fcfsSummary = calculateSummary(fcfsResult);
    Summary sjfSummary = calculateSummary(sjfResult);
    Summary hrrnSummary = calculateSummary(hrrnResult);

    std::cout << "\n========== 三种算法性能对比 ==========" << std::endl;
    std::cout << std::left << std::setw(24) << "算法"
        << std::setw(16) << "平均等待时间"
        << std::setw(16) << "平均周转时间"
        << std::setw(20) << "平均带权周转时间" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    std::cout << std::left << std::setw(24) << "FCFS 先来先服务"
        << std::setw(16) << fcfsSummary.avgWaitTime
        << std::setw(16) << fcfsSummary.avgTurnaroundTime
        << std::setw(20) << fcfsSummary.avgWeightedTurnaroundTime << std::endl;

    std::cout << std::left << std::setw(24) << "SJF 短作业优先"
        << std::setw(16) << sjfSummary.avgWaitTime
        << std::setw(16) << sjfSummary.avgTurnaroundTime
        << std::setw(20) << sjfSummary.avgWeightedTurnaroundTime << std::endl;

    std::cout << std::left << std::setw(24) << "HRRN 最高响应比优先"
        << std::setw(16) << hrrnSummary.avgWaitTime
        << std::setw(16) << hrrnSummary.avgTurnaroundTime
        << std::setw(20) << hrrnSummary.avgWeightedTurnaroundTime << std::endl;
}
