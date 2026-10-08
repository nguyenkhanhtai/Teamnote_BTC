#include <bits/stdc++.h>
  // Use: auto survivor = josephus_fast(10,3); // zero-based

// n,k >= 1; survivor is zero-indexed. O(n), O(1) space.
int josephus_linear(int n, int k) {
    assert(n >= 1 && k >= 1);
    int result = 0;
    for (int size = 1; size < n; ++size)
        result = static_cast<int>((__int128(result) + k) % (size + 1));
    return result;
}

// Batch elimination, small k: O(k log n); O(n) fallback for k>n.
// Iterative stack avoids deep recursion; n fits int.
int josephus_fast(int n, int k) {
    assert(n >= 1 && k >= 1);
    if (k == 1) return n - 1;
    std::vector<int> sizes;
    int reduced = n;
    while (reduced >= k) {
        sizes.push_back(reduced);
        reduced -= reduced / k;
    }
    int result = josephus_linear(reduced, k);
    while (!sizes.empty()) {
        int size = sizes.back(); sizes.pop_back();
        if (result < size % k) result += size - size % k;
        else { result -= size % k; result += result / (k - 1); }
    }
    return result;
}
