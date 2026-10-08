#include <bits/stdc++.h>
using namespace std;

const int BITS = 20;

int a[1 << BITS];
int dpUp[1 << BITS];
int dpDown[1 << BITS];
int exists[1 << BITS];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        exists[a[i]] = 1;
    }

    for (int mask = 0; mask < (1 << BITS); ++mask) {
        dpUp[mask] = -BITS;
        if (exists[mask]) dpUp[mask] = __builtin_popcount(mask);

        for (int i = 0; i < BITS; ++i) {
            if ((1 << i) & mask) {
                dpUp[mask] = max(dpUp[mask], dpUp[mask ^ (1 << i)]);
            }
        }
    }

    for (int mask = (1 << BITS) - 1; mask >= 0; --mask) {

        dpDown[mask] = dpUp[mask];

        for (int i = 0; i < BITS; ++i) {
            if ((1 << i) & mask) continue;
            dpDown[mask] = max(dpDown[mask], dpDown[mask | (1 << i)] - 2);
        }
    }

    for (int i = 0; i < n; ++i) {
        int complement = ((1 << BITS) - 1) ^ a[i];
        cout << __builtin_popcount(a[i]) + dpDown[complement];

        cout << (i == n - 1 ? '\n' : ' ');
    }
}
