#include <bits/stdc++.h>

// n,k >= 1; survivor is zero-indexed. O(n), O(1) space.
uint64_t josephus_linear(uint64_t n, uint64_t k) {
    uint64_t result = 0;
    for (uint64_t size = 1; size < n; ++size)
        result = static_cast<uint64_t>((__uint128_t(result) + k) % (size + 1));
    return result;
}

// Batch elimination, small k: O(k log n); O(n) fallback for k>n.
// Iterative stack avoids deep recursion; n <= INT64_MAX.
uint64_t josephus_fast(uint64_t n, uint64_t k) {
    assert(n && k && n <= uint64_t(INT64_MAX));
    if (k == 1) return n - 1;
    std::vector<uint64_t> sizes;
    uint64_t reduced = n;
    while (reduced >= k) {
        sizes.push_back(reduced);
        reduced -= reduced / k;
    }
    uint64_t result = josephus_linear(reduced, k);
    while (!sizes.empty()) {
        uint64_t size = sizes.back(); sizes.pop_back();
        if (result < size % k) result += size - size % k;
        else { result -= size % k; result += result / (k - 1); }
    }
    return result;
}
