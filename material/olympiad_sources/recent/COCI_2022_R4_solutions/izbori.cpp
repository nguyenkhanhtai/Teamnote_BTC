//#include "time_measure.h"
#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef pair <int, int> pii;

const int INF = 0x3f3f3f3f;
const int N = 2e5 + 5;
const int OFF = (1 << 19);

struct Node{
    int sum;
    ll br;
    int cnt;
    int prop;
    Node(int sum_ = 0, ll br_ = 0, int cnt_ = 0, int prop_ = 0) {
        sum = sum_; br = br_; cnt = cnt_; prop = prop_;
    }
};

int n;
int p[N], bio[2*OFF];
Node T[2*OFF];
vector <int> v[N], saz;
ll sol = 0;

Node mrg(Node a, Node b) {
    assert(a.prop == 0 && a.prop == 0);
    return Node(a.sum + b.sum, a.br + b.br + (ll)b.cnt * a.sum, a.cnt + b.cnt);
}

void propag(int pos) {
    bio[pos] = 1;
    if (T[pos].prop == 0) return;
    T[pos].sum += (ll)T[pos].cnt * T[pos].prop;
    T[pos].br += (ll)T[pos].cnt * (T[pos].cnt + 1) / 2 * T[pos].prop;
    if (pos < OFF) {
        T[pos * 2].prop += T[pos].prop;
        T[pos * 2 + 1].prop += T[pos].prop;
        bio[pos * 2] = bio[pos * 2 + 1] = 1;
    }
    T[pos].prop = 0;
}

Node query(int a, int b, int pos = 1, int lo = 0, int hi = OFF) {
    propag(pos);
    if (lo >= b || hi <= a) return Node();
    if (lo >= a && hi <= b) return T[pos];
    int mid = (lo + hi) / 2;
    return mrg(query(a, b, pos * 2, lo, mid), query(a, b, pos * 2 + 1, mid, hi));
}

void update(int a, int b, int pos = 1, int lo = 0, int hi = OFF) {
    propag(pos);
    if (lo >= b || hi <= a) return;
    if (lo >= a && hi <= b) {
        T[pos].prop=1;
        propag(pos);
        return;
    }
    int mid=(lo+hi)/2;
    update(a, b, pos * 2, lo, mid);
    update(a, b, pos * 2 + 1, mid, hi);
    T[pos] = mrg(T[pos * 2], T[pos * 2 + 1]);
}

void reset(int pos) {
    T[pos].br = T[pos].sum = T[pos].prop = 0;
    if (pos >= OFF) return;
    if (bio[pos * 2]) reset(pos * 2);
    if (bio[pos * 2 + 1]) reset(pos * 2 +1);
    bio[pos] = 0;
}

void minus_jedan(int l, int r) {
    sol += query(l, r).br + (ll)query(0, l).sum * (r - l + 1);
    update(l, r + 1);
}

void jedan(int x) {
    sol += query(0, x).sum;
    update(x, x + 1);
}

void solve() {
    for (int i = 0; i < OFF; ++i) T[OFF + i].cnt = 1;
    for (int i = OFF - 1; i > 0; --i) T[i] = mrg(T[i * 2], T[i * 2 + 1]);

    for (int x = 0; x < n; ++x) {
        if (v[x].empty()) continue;

        update(n, n + 1);
        if (v[x][0]) minus_jedan(n - v[x][0], n - 1);
        int pref = n - v[x][0];
        jedan(++pref);

        for (int i = 1; i < v[x].size(); ++i) {
            int raz = v[x][i] - v[x][i - 1] - 1;
            if (raz != 0) minus_jedan(pref - raz, pref - 1);
            pref = pref - raz + 1;
            jedan(pref);
        }
        if (v[x].back() != n - 1) minus_jedan(pref - (n - v[x].back() - 1), pref - 1);
        reset(1);
    }
    printf("%lld\n", sol);
}

void load() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
        saz.pb(p[i]);
    }
    sort(saz.begin(), saz.end());
    saz.erase(unique(saz.begin(), saz.end()), saz.end());
    for (int i = 0; i < n; ++i) {
        p[i] = lower_bound(saz.begin(), saz.end(), p[i]) - saz.begin();
        v[p[i]].pb(i);
    }
}

int main() {
//    auto vrijeme = GetTimeMs64();

    load();
    solve();

//    FILE *fp=fopen("current_time", "w");
//    fprintf(fp, "%lld\n", GetTimeMs64()-vrijeme);
//    fclose(fp);

	return 0;
}
