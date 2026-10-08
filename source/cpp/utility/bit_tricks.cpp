#include <bits/stdc++.h>
  // Use: for_each_submask(13,onMask); for_each_k_subset(5,2,onMask);
  //      void onMask(uint64_t mask)

// Calls visit(submask), including zero, in descending order.
void for_each_submask(uint64_t mask,std::function<void(uint64_t)> visit) {
    uint64_t sub = mask;
    for (;;) {
        visit(sub);
        if (sub == 0) break;
        sub = (sub - 1) & mask;
    }
}

// Gosper: n<=64, k<=n. Calls visit(mask) for every k-element subset.
void for_each_k_subset(unsigned n,unsigned k,std::function<void(uint64_t)> visit) {
    assert(k <= n && n <= 64);
    if (k == 0) { visit(uint64_t(0)); return; }
    if (k == 64) { visit(UINT64_MAX); return; }
    uint64_t mask = (uint64_t(1) << k) - 1;
    while (n == 64 || mask < (uint64_t(1) << n)) {
        visit(mask);
        uint64_t low = mask & (uint64_t(0) - mask), next = mask + low;
        if (next == 0) break;
        mask = next | (((next ^ mask) >> 2) / low);
    }
}

// Return 64 for zero; avoid undefined __builtin_ctzll(0).
unsigned trailing_zeros(uint64_t x) { return x ? __builtin_ctzll(x) : 64; }
unsigned leading_zeros(uint64_t x) { return x ? __builtin_clzll(x) : 64; }
unsigned popcount(uint64_t x) { return __builtin_popcountll(x); }
uint64_t lowest_bit(uint64_t x) { return x & (uint64_t(0) - x); }
// Permutation/matching DP: next position = popcount(mask), no extra step state.
