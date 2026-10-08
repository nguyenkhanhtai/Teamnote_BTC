#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int fenwick[1 << 18];
int sz = 0;

void init(int n) {
    sz = 1;
    while (sz < n) sz *= 2;
    memset(fenwick, 0, sizeof fenwick);
}

int query_sum(int i) {
    int s = 0;
    while (i >= 0) {
        s += fenwick[i];
        i &= i + 1;
        --i;
    }
    
    return s;
}

void point_add(int i, int v) {
    while (i < sz) {
        fenwick[i] += v;
        i |= i + 1;
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> x(n);
    vector<pair<int, int>> y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        y[i] = {x[i], i};
    }    
    sort(y.begin(), y.end());
    for (int i = 0; i < n; ++i) x[y[i].second] = i;
    vector<int> wrong(n+1, 0);
    for (int i = 0; i < n; ++i)
        wrong[i+1] = wrong[i] + (x[i] != i);
    
    vector<pair<int, int>> que(q);
    vector<array<int, 3>> pq(2*q), sq(2*q);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        b = n-b;
        
        que[i] = {a, b};
        pq[2*i] = {a, a, 4*i};
        sq[2*i] = {b, a, 4*i+1};
        pq[2*i+1] = {a, b, 4*i+2};
        sq[2*i+1] = {b, b, 4*i+3};
    }
    
    sort(pq.begin(), pq.end());
    sort(sq.begin(), sq.end());
    init(n+1);
    
    vector<int> ans(4*q);
    
    int j = 0, k = 0;
    for (int i = 0; i <= n; ++i) {
        while (j < 2*q && pq[j][0] == i) {
            ans[pq[j][2]] = pq[j][1] - query_sum(pq[j][1]);
            ++j;
        }
        while (k < 2*q && sq[k][0] == i) {
            ans[sq[k][2]] = i - query_sum(sq[k][1]);
            ++k;
        }
        if (i < n) point_add(y[i].second+1, 1);
    }
    
    for (int i = 0; i < q; ++i) {
        auto [a, b] = que[i];
        int len = a - b;
        if (wrong[n] == 0)
            cout << "0\n";
        else if (wrong[b] == 0 || wrong[n] - wrong[a] == 0)
            cout << "1\n";
        else if (len <= 0)
            cout << (wrong[b] - wrong[a] == 0
                    && ans[4*i+0] == 0
                    && ans[4*i+3] == 0 ? 2 : -1) << '\n';
        else
            cout << max(2, min(max(2 * ((ans[4*i+0] + len - 1) / len),
                                   2 * ((ans[4*i+1] + len - 1) / len) + 1),
                               max(2 * ((ans[4*i+2] + len - 1) / len) + 1,
                                   2 * ((ans[4*i+3] + len - 1) / len)))) << '\n';
    }
    
    return 0;
}