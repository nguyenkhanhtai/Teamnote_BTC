#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

const int maxn = 105;

const int xp[] = {1, 0, -1, 0};
const int yp[] = {0, 1, 0, -1};

int n, m;
int col[maxn][maxn][4];
map < char, int > boja;

void precompute() {
  boja['Z'] = 0;
  boja['P'] = 1;
  boja['C'] = 2;
  boja['N'] = 3;
}

int mask;
int cx, cy;
bool bio[maxn][maxn];

bool dfs(int x, int y) {
  if(x == cx && y == cy) {
    return 1;
  }
  bio[x][y] = 1;
  int xs, ys;
  for(int i = 0; i < 4; i++) {
    xs = x + xp[i];
    ys = y + yp[i];
    if(xs > -1 && ys > -1 && xs < n && ys < m && !bio[xs][ys] && ((1 << col[x][y][i]) & mask)) {
      if(dfs(xs, ys)){
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  precompute();
  char a;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m - 1; j++) {
      cin >> a;
      col[i][j][1] = boja[a];
      col[i][j + 1][3] = boja[a];
    }
  }
  for(int i = 0; i < n - 1; i++) {
    for(int j = 0; j < m; j++) {
      cin >> a;
      col[i][j][0] = boja[a];
      col[i + 1][j][2] = boja[a];
    }
  }
  int q;
  cin >> q;
  int x, y;
  int sol;
  for(int i = 0; i < q; i++) {
    cin >> x >> y >> cx >> cy;
    x--; y--;
    cx--; cy--;
    sol = 4;
    for(int j = 1; j < 16; j++) {
      mask = j;
      if(dfs(x, y)) {
        sol = min(sol, __builtin_popcount(j));
      }
      memset(bio, 0, sizeof(bio));
    }
    cout << sol << '\n';
  }
  return 0;
}
