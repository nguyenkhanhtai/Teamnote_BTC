#include <bits/stdc++.h>
  // Use: for_each_submask(13,onMask); for_each_k_subset(5,2,onMask);
  //      void onMask(int mask)

// Nonnegative masks. Calls visit(submask), including zero, in descending order.
void for_each_submask(int mask,std::function<void(int)> visit) {
    assert(mask >= 0);
    int sub = mask;
    for (;;) {
        visit(sub);
        if (sub == 0) break;
        sub = (sub - 1) & mask;
    }
}

// Gosper: n<=63 with #define int long long; k<=n.
void for_each_k_subset(int n,int k,std::function<void(int)> visit) {
    const int BITS = std::numeric_limits<int>::digits;
    assert(0 <= k && k <= n && n <= BITS);
    if (k == 0) { visit(0); return; }
    __int128 limit = (__int128)1 << n;
    int mask = ((__int128)1 << k) - 1;
    for (;;) {
        visit(mask);
        int low = mask & -mask;
        __int128 next = (__int128)mask + low;
        if (next >= limit) break;
        mask = next | (((next ^ mask) >> 2) / low);
    }
}

// Count bits in the full int storage width; zero has no set bit.
int trailing_zeros(int x) {
    return x ? __builtin_ctzll(x) : sizeof(int) * CHAR_BIT;
}
int leading_zeros(int x) {
    return x ? __builtin_clzll(x) - (sizeof(long long)-sizeof(int))*CHAR_BIT
             : sizeof(int) * CHAR_BIT;
}
int popcount(int x) { return __builtin_popcountll(x); }
int lowest_bit(int x) { assert(x >= 0); return x & -x; }
// Permutation/matching DP: next position = popcount(mask), no extra step state.
