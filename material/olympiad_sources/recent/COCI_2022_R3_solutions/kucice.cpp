#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <llint, llint> pi;

const int MAXN = 1005;
const int MOD = 1000000007;

int n, pivot_idx;
int x[MAXN], y[MAXN];
int pot[MAXN];

llint ccw (pi a, pi b, pi c) {
    return a.first * (b.second - c.second) + b.first * (c.second - a.second) + c.first * (a.second - b.second);
}

int add (int x, int y) {x += y; if (x >= MOD) return x - MOD; return x;}
int sub (int x, int y) {x -= y; if (x < 0) return x + MOD; return x;}
int mul (int x, int y) {return (llint) x * y % MOD;}

int halfplane (int i) {
    if (y[i] > y[pivot_idx]) return 1;
    if (y[i] < y[pivot_idx]) return -1;
    if (x[i] > x[pivot_idx]) return 1;
    if (x[i] < x[pivot_idx]) return -1;
    return 0;
}

bool cmp (int i, int j) {
    int hi = halfplane(i);
    int hj = halfplane(j);
    if (hi != hj) return hi > hj;
    return ccw({x[i], y[i]}, {x[pivot_idx], y[pivot_idx]}, {x[j], y[j]}) < 0;
}

void precompute () {
    pot[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pot[i] = mul(pot[i - 1], 2);
    }
}

int calc_sol_for_pivot () {
    vector <int> v;
    for (int i = 0; i < n; i++) {
        if (i == pivot_idx) continue;
        v.push_back(i);
    }
    sort(v.begin(), v.end(), cmp);

    int res = 1;

    int j = 0, cnt = 1;
    for (int i = 0; i < v.size(); i++) {
        while (1) {
            int nxt_j = (j + 1) % (n - 1);
            if (nxt_j == i) break;
            if (ccw({x[v[i]], y[v[i]]}, {x[v[nxt_j]], y[v[nxt_j]]}, {x[pivot_idx], y[pivot_idx]}) < 0) break;
            j = nxt_j;
            cnt++;
        }

        res = add(res, pot[cnt - 1]);

        if (j == i) {
            cnt = 1;
            j = (j + 1) % (n - 1);
        } else {
            cnt--;
        }
    }

    return res;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    precompute();
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    if (n == 1) {
        cout << 1;
        return 0;
    }

    int sol = 0;
    for (pivot_idx = 0; pivot_idx < n; pivot_idx++) {
        sol = add(sol, calc_sol_for_pivot());
    }

    sol = sub(mul(n, pot[n]), sol);

    cout << sol;
    return 0;
}
