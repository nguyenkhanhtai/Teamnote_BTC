#include <bits/stdc++.h>

// Protocol adapter: supply serialization and invalid-reply rules for the task.
template<class Reply>
class InteractiveSession {
    std::istream& input;
    std::ostream& output;
    size_t limit, used = 0;
public:
    InteractiveSession(std::istream& in, std::ostream& out, size_t budget)
        : input(in), output(out), limit(budget) {}
    size_t queries() const { return used; }
    template<class Write, class Valid>
    Reply ask(Write write, Valid valid) {
        if (used == limit) throw std::runtime_error("query budget exhausted");
        write(output); output << '\n' << std::flush; ++used;
        Reply reply;
        if (!(input >> reply) || !valid(reply))
            throw std::runtime_error("invalid judge reply");
        return reply;
    }
    template<class Write>
    void answer(Write write) { write(output); output << '\n' << std::flush; }
};

// Monotone predicate: test(lo)=false, test(hi)=true; known endpoints not queried.
template<class Test>
long long first_true(long long lo, long long hi, Test test) {
    assert(lo < hi);
    while (__int128(hi) - lo > 1) {
        long long mid = static_cast<long long>(__int128(lo) + (__int128(hi) - lo) / 2);
        if (test(mid)) hi = mid; else lo = mid;
    }
    return hi;
}

// Adjacent values differ by 1; read(lo)<=target<=read(hi), lo<hi.
template<class Read>
long long find_unit_step_value(long long lo, long long hi, long long target, Read read) {
    while (__int128(hi) - lo > 1) {
        long long mid = static_cast<long long>(__int128(lo) + (__int128(hi) - lo) / 2);
        auto value = read(mid);
        if (value == target) return mid;
        if (value < target) lo = mid; else hi = mid;
    }
    return read(lo) == target ? lo : hi;
}

// Distinct values, n>=2; better(i,j) returns true iff value[i]>value[j].
// Returns {maximum index, second-maximum index}; balanced tournament.
template<class Better>
std::pair<int, int> top_two(int n, Better better) {
    assert(n >= 2);
    std::vector<std::vector<int>> defeated(n);
    std::vector<int> round(n);
    std::iota(round.begin(), round.end(), 0);
    while (round.size() > 1) {
        std::vector<int> next;
        for (size_t i = 0; i < round.size(); i += 2) {
            int winner = round[i];
            if (i + 1 < round.size()) {
                int loser = round[i + 1];
                if (!better(winner, loser)) std::swap(winner, loser);
                defeated[winner].push_back(loser);
            }
            next.push_back(winner);
        }
        round.swap(next);
    }
    int best = round[0], second = defeated[best][0];
    for (size_t i = 1; i < defeated[best].size(); ++i)
        if (better(defeated[best][i], second)) second = defeated[best][i];
    return {best, second};
}
