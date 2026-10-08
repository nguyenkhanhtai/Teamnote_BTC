#include <bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define eb emplace_back
#define popcnt __builtin_popcount
#define popcntll __builtin_popcountll
#define all(a) begin(a), end(a)

using namespace std;


int n, m;
vector<vector<int>> unori, ori;
vector<int> deg;



vector<int> cycle;
vector<bool> bio;
int flag = 0;
void findCycle(int v, int p) {
  if (bio[v]) {
    flag = 1;
    cycle.pb(v);
    return;
  }
  bio[v] = true;
  for (auto u : unori[v]) if (u != p) {
    findCycle(u, v);
    if (flag == 1) {
      if (v == cycle[0]) {
        flag = 2;
      } else {
        cycle.pb(v);
      }
      return;
    } else if (flag == 2) {
      return;
    }
  }
}

bool good = true;

int ans = 0;
void dp(int v, int p) {
  int tv = p == -1 ? cycle[v] : v;
  for (auto u : unori[tv]) {
    if (p == -1 && (u == cycle[(v + 1) % size(cycle)] || u == cycle[(v + size(cycle) - 1) % size(cycle)])) {
      continue;
    } else if (u == p) {
      continue;
    }
    dp(u, tv);

    if (abs(deg[u]) > 1) good = false;
    else if (deg[u] != 0) {
      ans++;
      ori[u].pb(tv);
      ori[tv].pb(u);
      deg[tv] += deg[u];
      deg[u] -= deg[u];
    }
  }
}

vector<vector<int>> ned;

void dfs(int v) {
  if (bio[v]) return;
  bio[v] = true;
  for (auto a : ori[v]) {
    dfs(a);
  }
  for (auto a : ned[v]) {
    dfs(a);
  }
}

bool checkInvalid() {
  bio.clear();
  bio.resize(n);
  for (int i = 0; i < n; ++i) {
    if (!ori[i].empty()) {
      dfs(i);
      break;
    }
  }
  for (int i = 0; i < n; ++i) {
    if (!ori[i].empty() && !bio[i]) {
      return true;
    }
  }
  
  return false;
}

int solveCycle(int t, int ci) {
  int i = ci;
  int added = 0;
  vector<int> tdeg = deg;
  auto pned = ned;
  ned.resize(n);
  do {
    int nxt = (i + t + size(cycle)) % size(cycle);
    int d = tdeg[cycle[i]] > 0 ? 1 : -1;
    if (tdeg[cycle[i]] != 0) {
      added++;
      tdeg[cycle[nxt]] += d;
      tdeg[cycle[i]] -= d;
      ned[cycle[i]].pb(cycle[nxt]);
      ned[cycle[nxt]].pb(cycle[i]);
    }
    i = nxt;
  } while (i != ci);
  int mx = 0;
  for (auto a : cycle) mx = max(abs(tdeg[a]), mx);
  mx += checkInvalid();
  ned = pned;
  return mx == 0 ? added : n + 1;
}

void solve() {
  cin >> n >> m;
  unori.resize(n);
  ori.resize(n);
  deg.resize(n);
  bio.resize(n);
  for (int i = 0; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    unori[u].pb(v);
    unori[v].pb(u);
  }
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    ori[u].pb(v);
    ori[v].pb(u);
    deg[v]++;
    deg[u]--;
  }

  findCycle(0, -1);
  for (int i = 0; i < (int)size(cycle); ++i) {
    dp(i, -1);
  }
  if (!good) {
    cerr << "bad1" << endl;
    cout << "-1\n";
    return;
  }
  int mx = 0;
  int ci = 0;
  for (int i = 0; i < (int)cycle.size(); ++i) {
    if (abs(deg[cycle[i]]) > mx) {
      mx = abs(deg[cycle[i]]);
      ci = i;
    }
  }
  if (mx > 2) {
    cerr << "bad2" << endl;
    cout << "-1\n";
    return;
  } else if (mx == 0) {
    ned.resize(n);
    if (checkInvalid()) {
      ans += size(cycle);
      for (int i = 0; i < (int)size(cycle); ++i) {
        ned[cycle[i]].pb(cycle[(i+1) % size(cycle)]);
        ned[cycle[(i+1)%size(cycle)]].pb(cycle[i]);
      }
      if (checkInvalid()) {
        cerr << "bad3" << endl;
        cout << "-1\n";
        return;
      } else {
        cerr << "good2" << endl;
      }
    } else {
      cerr << "good1" << endl;
    }
    cout << ans + m << '\n';
    return;
  } else {
    cerr << "mx: " << mx << endl;
    int a1 = solveCycle(1, ci);
    int a2 = solveCycle(-1, ci);
    ans += min(a1, a2);
    if (ans > n) {
      cerr << "bad4" << endl;
      cout << "-1\n";
      return;
    } else {
      cerr << "good3" << endl;
      cout << ans + m<< '\n';
      return;
    }
  }
  
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

  solve();
  

	return 0;
}


