#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ll long long
#define X first
#define Y second

using namespace std;

const int MAXN = 201000;

vector <pair <int, int> > ve[MAXN];
ll mid;
int uk;
bool flag[MAXN];
int marked[MAXN];

ll dfs(int x, int par) {
    if (ve[x].size() == 1 && x != 0) return 0;

    ll mi = (1LL << 60), ma = -(1LL << 60);
    for (auto tr : ve[x]) {
        int y = tr.X;
        ll d = tr.Y;
        if (y == par) continue;

        ll a = dfs(y, x);
        if (a == 0 && flag[y] == 1) {
            mi = min(mi, 0LL);
            ma = max(ma, 0LL);
            continue;
        }

        if (a < 0 && a + d <= 0) flag[x] = 1;

        if (a < 0 && a + d > 0) a = 0;
        else a += d;

        if (a > mid) {
            uk++;
            marked[y] = 1;
            //cout << y << " ";
            a = min(-mid + d, 0LL);
            if (-mid + d <= 0) flag[x] = 1;
            flag[y] = 1;
            //cout << y + 1 << endl;
        }

        //cout << x + 1 << " " << y + 1 << " " << a << endl;

        ma = max(ma, a);
        mi = min(mi, a);
    }
    //cout << x + 1 << ": " << mi << " " << ma << endl;
    if (-mi >= ma/* && mi != 0*/) {
        //flag[x] = 1;
        return mi;
    }
    return ma;
}

int main() {
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    REP(i, n - 1) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        ve[a].push_back({b, c});
        ve[b].push_back({a, c});
    }

    ll lo = 0, hi = (1LL << 60);
    while (lo < hi) {
        mid = (lo + hi) / 2;
        uk = 0;
        memset(flag, 0, sizeof flag);
        memset(marked, 0, sizeof marked);
        if (dfs(0, 0) > 0) marked[0] = 1, uk++;
        else if (flag[0] == 0) marked[0] = 1, uk++;

        //cout << endl << uk << endl;
        //cout << mid << " " << uk << endl;

        if (uk <= k) hi = mid;
        else         lo = mid + 1;
    }

    mid = lo;
    uk = 0;
    memset(flag, 0, sizeof flag);
    memset(marked, 0, sizeof marked);
    if (dfs(0, 0) > 0) marked[0] = 1, uk++;
    else if (flag[0] == 0) marked[0] = 1, uk++;

    cout << lo << "\n";
    vector <int> out;
    REP(i, n) if (marked[i] == 1) out.push_back(i + 1);
    REP(i, n) if (out.size() < k && marked[i] == 0) out.push_back(i + 1);
    for (int x : out) cout << x << " "; cout << "\n";

    return 0;
}