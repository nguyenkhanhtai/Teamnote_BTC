#include<bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for(int i = a; i >= b; i--)
#define endl '\n'
#define pb push_back
#define pf push_front
#define fastio ios_base::sync_with_stdio(NULL); cin.tie(NULL); cout.tie(NULL);

//Data structure
#define vi vector<int>
#define int long long
#define ii pair<int, int>
#define iii pair<int, ii>

//Bitmask (absolutely have a () outside of every thing)
#define LSB(x) (x & (-x))
#define ON(x, i) ((x >> i)&1)
#define OFF(x, i) !ON(x, i)
#define SET(x, i) (x | (1LL << i))
#define UNSET(x, i) (SET(x, i) ^ (1LL << i))

#define TASKNAME "test"

template<typename T> bool maximize(T &a, T b){    if (a < b){ a = b;  return true; }  return false; }
template<typename T> bool minimize(T &a, T b){    if (a > b){ a = b;  return true; }  return false; }
using namespace std;

  // Use: auto ans = hungarian({{3,1},{2,4}}); // ans.cost, ans.column
  struct Assignment { int cost; vector<int> column; };
  // Minimum rectangular assignment, rows<=columns; costs may be negative.
  Assignment hungarian(const vector<vector<int>>& a) {
    int n = a.size();
    if (!n) return {
      0, {}
    }; int m=a[0].size(); assert(n<=m); vector<int>u(n+1),v(m+1);
    vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
      p[0]=i; int j0=0; vector<int>best(m+1,1LL<<60); vector<bool>used(m+1);
      do {
        used[j0]=true; int row=p[j0],j1=0; int delta=1LL<<60;
        for (int j = 1; j <= m; ++j) if (!used[j]) {
          int value = a[row - 1][j - 1] - u[row] - v[j];
          if (value < best[j]) { best[j] = value; way[j] = j0; }
          if (best[j] < delta) { delta = best[j]; j1 = j; }
        }
        for (int j = 0; j <= m; ++j) if (used[j]) {
          u[p[j]] += delta; v[j] -= delta;
        } else best[j] -= delta;
        j0 = j1;
      }
      while (p[j0]);
      do { int previous = way[j0]; p[j0] = p[previous]; j0 = previous; }
      while (j0);
    }
    vector<int> column(n);
    for (int j = 1; j <= m; ++j) if (p[j]) column[p[j] - 1] = j - 1;
    return {-v[0], column};
  }

// Input: n, then an n x n cost matrix. One test case.
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> cost(n, vector<int>(n));
    for (auto& row : cost) for (int& x : row) cin >> x;
    auto ans = hungarian(cost);
    cout << ans.cost << endl;
    // column[i] is the job assigned to person i; indices start at 0.
    for (int j : ans.column) cout << j << ' ';
    cout << endl;
}
signed main() {
    fastio;
    solve();
}
