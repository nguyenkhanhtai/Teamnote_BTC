// Olaf Targowski
// Time: O((n+q) log n); Memory: O(n+q).
// Intended solution.
#include <bits/stdc++.h>
using namespace std;
// Segment tree for finding the position of the largest element in an interval.
struct stmax {
    vector<int> t, pos;
    int comp;
    stmax(const int n, const vector<int> &v) {
        comp = bit_ceil(unsigned(n));
        t.resize(comp << 1, -1);
        pos.resize(comp << 1, -1);
        for (int i = 0; i < n; ++i) {
            t[i + comp] = v[i];
            pos[i + comp] = i;
        }
        for (int i = comp - 1; i; --i) {
            t[i] = max(t[i << 1], t[(i << 1) | 1]);
            pos[i] = t[i] == t[i << 1] ? pos[i << 1] : pos[(i << 1) | 1];
        }
    }
    int query(int l, int r) {
        int res = -1, respos = -1;
        for (l += comp, r += comp + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                if (t[l] > res)
                    res = t[l], respos = pos[l];
                ++l;
            }
            if (r & 1) {
                --r;
                if (t[r] > res)
                    res = t[r], respos = pos[r];
            }
        }
        assert(respos > -1);
        return respos;
    }
};
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> ai(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &ai[i]);
    stmax st(n, ai);
    const int cap = *max_element(ai.begin(), ai.end());
    struct q_t {
        int i, s, e;
    };
    vector<vector<q_t>> qbuckets(n);
    vector<int> qmax(q), ans(q, 1);
    for (int i = 0; i < q; ++i) {
        int s, e;
        scanf("%d%d", &s, &e);
        --s, --e;
        qmax[i] = st.query(s, e);
        qbuckets[qmax[i]].emplace_back(i, s, e);
    }
    for (int reverse_merges : {0, 1}) {
        struct interval {
            int s, e;
            bool operator<(const interval &i) const {
                return s < i.s;
            }
            bool neighbours(const interval &i) const {
                return s == i.e + 1 || e + 1 == i.s;
            }
        };
        // hhs[start of interval] = height.
        vector<int> hhs = ai, hhe = ai;
        // hbuckets[height] contain data about (perhaps merged) numbers with
        // given height/exponent.
        vector<vector<interval>> hbuckets(cap + 1);
        for (int i = 0; i < n; ++i)
            hbuckets[ai[i]].emplace_back(i, i);
        for (int height = 0; height <= cap; ++height) {
            auto &hb = hbuckets[height];
            if (hb.empty())
                continue;
            sort(hb.begin(), hb.end());
            // Handle queries:
            for (int i = 0; i < ssize(hb); ++i)
                if (ai[hb[i].s] == height)
                    for (auto &[qi, s, e] : qbuckets[hb[i].s]) {
                        // We want to find the interval in hb that
                        // contains s/e.
                        const int target = reverse_merges ? s : e;
                        auto itr = upper_bound(hb.begin(), hb.end(),
                                               interval(target, 0));
                        assert(itr != hb.begin());
                        --itr;
                        const int l = int(distance(hb.begin(), itr)) - i;
                        ans[qi] += reverse_merges ? -l : l;
                    }
            // Now merge/lift:
            if (reverse_merges)
                reverse(hb.begin(), hb.end());
            // We don't need to handle the resulting edge cases.
            if (height == cap)
                continue;
            for (int i = 0; i < ssize(hb); ++i) {
                // We can merge.
                if (i + 1 < ssize(hb) && hb[i].neighbours(hb[i + 1])) {
                    const int s = min(hb[i].s, hb[i + 1].s);
                    const int e = max(hb[i].e, hb[i + 1].e);
                    hhs[s] = height + 1;
                    hhe[e] = height + 1;
                    hbuckets[height + 1].emplace_back(s, e);
                    ++i;
                }
                // We can only lift, as our neighbour(s) are higher than us.
                else {
                    const int inf = 1e9;
                    int lower = hb[i].e == n - 1 ? inf : hhs[hb[i].e + 1];
                    if (hb[i].s)
                        lower = min(lower, hhe[hb[i].s - 1]);
                    assert(lower < inf && lower > height);
                    hbuckets[lower].emplace_back(hb[i]);
                    hhs[hb[i].s] = lower;
                    hhe[hb[i].e] = lower;
                }
            }
            hb = {};
        }
        assert(ssize(hbuckets[cap]) >= 1);
    }
    for (int i = 0; i < q; ++i) {
        assert(ans[i] >= 1);
        int res = ai[qmax[i]];
        while (ans[i] > 1) {
            ans[i] = (ans[i] + 1) / 2;
            ++res;
        }
        printf("%d\n", res);
    }
}
