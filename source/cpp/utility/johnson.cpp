#include <bits/stdc++.h>

struct FlowShopJob { int id; long long first, second; };
struct FlowShopSchedule { std::vector<int> order; long long makespan; };

// Nonnegative durations; unique job IDs. O(n log n).
FlowShopSchedule johnson_schedule(std::vector<FlowShopJob> jobs) {
    std::sort(jobs.begin(), jobs.end(), [](const auto& a, const auto& b) {
        bool early_a = a.first <= a.second, early_b = b.first <= b.second;
        if (early_a != early_b) return early_a;
        long long x = early_a ? a.first : a.second;
        long long y = early_b ? b.first : b.second;
        if (x != y) return early_a ? x < y : x > y;
        return a.id < b.id;
    });
    FlowShopSchedule result{{}, 0};
    long long first_finish = 0;
    for (const auto& job : jobs) {
        result.order.push_back(job.id);
        first_finish += job.first;
        result.makespan = std::max(result.makespan, first_finish) + job.second;
    }
    return result;
}
