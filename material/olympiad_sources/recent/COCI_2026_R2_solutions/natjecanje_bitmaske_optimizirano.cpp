#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<pll> vpll;

#define PB push_back
#define PF push_front
#define PPB pop_back
#define PPF pop_front
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

const int mod = 1e9 + 7; //998244353;
const int inf = 1e9 + 7;
const ll INF = (ll)1e18 + 7;
const int logo = 20;
const int MAXN = 507;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int N = 25;

int d[N][MAXN][MAXN], ud[N][N], n, m;
vector<ii> p;
string mat[MAXN];
int dp[1 << N];

void bfs(int id, int r, int s){
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      d[id][i][j] = -1;
    }
  }
  
  d[id][r][s] = 0;
  queue<ii> q;
  q.push({r, s});
  
  while(!q.empty()){
    tie(r, s) = q.front();
    q.pop();
    for(int k = 0; k < 4; ++k){
      int nr = r + dx[k], ns = s + dy[k];
      if(nr < 0 or nr >= n or ns < 0 or ns >= m) continue;
      if(mat[nr][ns] == '#') continue;
      if(d[id][nr][ns] != -1) continue;
      d[id][nr][ns] = d[id][r][s] + 1;
      q.push({nr, ns});
    }
  }
}

int f(int a, int b){
  return d[a][p[b].X][p[b].Y];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  
  int _;
  cin >> n >> m >> _;
  for(int i = 0; i < n; ++i){
    cin >> mat[i];
    for(int j = 0; j < m; ++j){
      if(mat[i][j] == 'S') p.PB({i, j});
    }
  }
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      if(mat[i][j] == 'X') p.PB({i, j});
    }
  }
  
  int ans = 0;
  for(int i = 0; i < (int)p.size(); ++i){
    bfs(i, p[i].X, p[i].Y);
    if(i){
      ans += f(0, i) * 2;
      if(f(0, i) == -1){
        cout << "-1\n";
        return 0;
      }
    }
  }
  
  for(int i = 1; i < (int)p.size(); ++i){
    for(int j = i + 1; j < (int)p.size(); ++j){
      ud[i - 1][j - 1] = ud[j - 1][i - 1] = f(0, i) + f(0, j) - f(i, j);
    }
  }
  n = (int)p.size() - 1;
 
  int ma = 0;
  for(int i = 0; i < (1 << n); ++i){
    for(int j = 0; j < n; j++){
      if(i & (1 << j)) continue;
      for(int k = j + 1; k < n; ++k){
        if(i & (1 << k)) continue;
        if(j == k) continue;
        int ni = i | (1 << j) | (1 << k);
        dp[ni] = max(dp[ni], dp[i] + ud[j][k]);
        ma = max(ma, dp[ni]);
      }
      //prosli smo sva uparivanja prve 0 u maski
      break;
    }
  }
  
  cout << ans - ma << "\n";
  return 0;
}
