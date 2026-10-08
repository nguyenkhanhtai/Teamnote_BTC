#include <bits/stdc++.h>
  // Use: auto schedule = johnson_schedule({{0,2,3},{1,4,1}});

struct FlowShopJob { int id; int first, second; };
struct FlowShopSchedule { std::vector<int> order; int makespan; };

bool johnson_less(const FlowShopJob& a,const FlowShopJob& b) {
        bool early_a = a.first <= a.second, early_b = b.first <= b.second;
        if (early_a != early_b) return early_a;
        int x = early_a ? a.first : a.second;
        int y = early_b ? b.first : b.second;
        if (x != y) return early_a ? x < y : x > y;
        return a.id < b.id;
    
}

// Nonnegative durations; unique job IDs. O(n log n).
FlowShopSchedule johnson_schedule(std::vector<FlowShopJob> jobs) {
    std::sort(jobs.begin(),jobs.end(),johnson_less);
    FlowShopSchedule result{{}, 0};
    int first_finish = 0;
    for (const auto& job : jobs) {
        result.order.push_back(job.id);
        first_finish += job.first;
        result.makespan = std::max(result.makespan, first_finish) + job.second;
    }
    return result;
}
