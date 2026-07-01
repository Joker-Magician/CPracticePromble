#include "scheduler.h"
#include <cmath>
#include <limits>
#include <algorithm>


Job::Job() : arriveTime(0), serviceTime(0), startTime(0), finishTime(0), waitTime(0),
turnaroundTime(0), weightedTurnaroundTime(0), finished(0), inputOrder(0)
{}

namespace {
    // 重置算法计算后留下的结果
    void resetJobs(std::vector<Job>& jobs) {
        for (std::size_t i = 0; i < jobs.size(); i++) {
            jobs[i].startTime = 0;
            jobs[i].finishTime = 0;
            jobs[i].waitTime = 0;
            jobs[i].turnaroundTime = 0;
            jobs[i].weightedTurnaroundTime = 0;
            jobs[i].finished = 0;
        }
    }

    // 根据当前时间计算某个作业的调度结果
    void calculateJobTime(Job& job, int curr) {
        job.startTime = curr;
        job.finishTime = job.startTime + job.serviceTime;
        job.waitTime = job.startTime - job.arriveTime;
        job.turnaroundTime = job.finishTime - job.arriveTime;
        job.weightedTurnaroundTime = static_cast<double>(job.turnaroundTime) / job.serviceTime;
        job.finished = true;
    }

    // 当CPU空闲时，查找未完成作业中最早的到达时间
    int findNextArriveTime(const std::vector<Job>& jobs) {
        int nextTime = std::numeric_limits<int>::max();

        for (std::size_t i = 0; i < jobs.size(); i++) {
            if (!jobs[i].finished && jobs[i].arriveTime < nextTime) {
                nextTime = jobs[i].arriveTime;
            }
        }

        return nextTime;
    }

    // SJF算法比较两个候选作业的优先级
    // 服务时间短者优先；服务时间相同，到达时间早者优先；仍相同，输入顺序早者优先
    bool isBetterForSJF(const Job& candidate, const Job& currentBest) {
        if (candidate.serviceTime != currentBest.serviceTime) {
            return candidate.serviceTime < currentBest.serviceTime;
        }
        if (candidate.arriveTime != currentBest.arriveTime) {
            return candidate.arriveTime < currentBest.arriveTime;
        }
        return candidate.inputOrder < currentBest.inputOrder;
    }

    // HRRN算法比较两个候选作业的优先级
    // 到达时间早者优先；服务时间短者优先；输入顺序早者优先
    bool isBetterForHRRNTie(const Job& candidate, const Job& currentBest) {
        if (candidate.arriveTime != currentBest.arriveTime) {
            return candidate.arriveTime < currentBest.arriveTime;
        }
        if (candidate.serviceTime != currentBest.serviceTime) {
            return candidate.serviceTime < currentBest.serviceTime;
        }
        return candidate.inputOrder < currentBest.inputOrder;
    }
}

// 先来先服务调度算法(First Come First Served，FCFS)
// 按照作业到达时间从早到晚执行。
std::vector<Job> FCFS(std::vector<Job> jobs)
{
    resetJobs(jobs);

    std::stable_sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        if (a.arriveTime != b.arriveTime) return a.arriveTime < b.arriveTime;
        return a.inputOrder < b.inputOrder;
        });

    std::vector<Job> result;
    int currentTime = 0;

    for (std::size_t i = 0; i < jobs.size(); i++) {
        if (currentTime < jobs[i].arriveTime) {// 如果当前时间早于作业到达时间，说明 CPU 需要空闲等待
            currentTime = jobs[i].arriveTime;
        }

        calculateJobTime(jobs[i], currentTime);
        currentTime = jobs[i].finishTime;
        result.push_back(jobs[i]);
    }

    return result;
}

// 短作业优先调度算法(Shortest Job First, SJF),非抢占式
// 每次从已经到达且未完成的作业中，选择服务时间最短的作业执行
std::vector<Job> SJF(std::vector<Job> jobs)
{
    resetJobs(jobs);

    std::vector<Job> result;
    int currentTime = 0;
    int finishedCount = 0;
    const int totalCount = static_cast<int>(jobs.size());

    while (finishedCount < totalCount) {
        int selectedIndex = -1;

        for (std::size_t i = 0; i < jobs.size(); i++) {
            if (!jobs[i].finished && jobs[i].arriveTime <= currentTime) {
                if (selectedIndex == -1 || isBetterForSJF(jobs[i], jobs[selectedIndex])) {
                    selectedIndex = static_cast<int>(i);
                }
            }
        }

        // 当前时刻没有作业到达，CPU 空闲，跳转到下一个作业到达时间
        if (selectedIndex == -1) {
            currentTime = findNextArriveTime(jobs);
            continue;
        }

        calculateJobTime(jobs[selectedIndex], currentTime);
        currentTime = jobs[selectedIndex].finishTime;
        result.push_back(jobs[selectedIndex]);
        finishedCount++;
    }

    return result;
}

// 最高响应比优先调度算法(Highest Response Ratio Next, HRRN), 非抢占式
// 响应比公式：响应比 = (等待时间 + 服务时间) / 服务时间
// 每次从已经到达且未完成的作业中，选择响应比最高的作业执行
std::vector<Job> HRRN(std::vector<Job> jobs)
{
    resetJobs(jobs);

    std::vector<Job> result;
    int currentTime = 0;
    int finishedCount = 0;
    const int totalCount = static_cast<int>(jobs.size());

    while (finishedCount < totalCount) {
        int selectedIndex = -1;
        double bestResponseRatio = -1.0;

        for (std::size_t i = 0; i < jobs.size(); i++) {
            if (!jobs[i].finished && jobs[i].arriveTime <= currentTime) {
                const int waitTime = currentTime - jobs[i].arriveTime;
                const double responseRatio = static_cast<double>(waitTime + jobs[i].serviceTime) / jobs[i].serviceTime;

                if (selectedIndex == -1 || responseRatio > bestResponseRatio + 1e-9
                    || (std::fabs(responseRatio - bestResponseRatio) <= 1e-9 &&
                        isBetterForHRRNTie(jobs[i], jobs[selectedIndex]))) {
                    selectedIndex = static_cast<int>(i);
                    bestResponseRatio = responseRatio;
                }
            }
        }

        // 当前时刻没有作业到达，CPU 空闲，跳转到下一个作业到达时间
        if (selectedIndex == -1) {
            currentTime = findNextArriveTime(jobs);
            continue;
        }

        calculateJobTime(jobs[selectedIndex], currentTime);
        currentTime = jobs[selectedIndex].finishTime;
        result.push_back(jobs[selectedIndex]);
        finishedCount++;
    }

    return result;
}