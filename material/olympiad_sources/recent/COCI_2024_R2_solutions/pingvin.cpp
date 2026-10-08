#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

const int dx[] = {-1, 1, 0, 0, 0, 0};
const int dy[] = {0, 0, -1, 1, 0, 0};
const int dz[] = {0, 0, 0, 0, -1, 1};

int n;
bool space[MAXN][MAXN][MAXN];
int dist[MAXN][MAXN][MAXN];

void bfs(int x, int y, int z) {
  memset(dist, -1, sizeof(dist));

  queue<tuple<int, int, int>> q;
  q.emplace(x, y, z);
  dist[x][y][z] = 0;

  while (!q.empty()) {
    tie(x, y, z) = q.front();
    q.pop();

    for (int i = 0; i < 6; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      int nz = z + dz[i];

      if (nx < 0 || nx >= n) continue;
      if (ny < 0 || ny >= n) continue;
      if (nz < 0 || nz >= n) continue;

      if (space[nx][ny][nz]) continue;
      if (dist[nx][ny][nz] != -1) continue;

      dist[nx][ny][nz] = dist[x][y][z] + 1;
      q.emplace(nx, ny, nz);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  int xs, ys, zs, xe, ye, ze;

  cin >> xs >> ys >> zs;
  cin >> xe >> ye >> ze;

  --xs; --ys; --zs;
  --xe; --ye; --ze;

  for (int z = 0; z < n; z++) {
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++) {
        char c; cin >> c;
        space[x][y][z] = (c == '1');
      }
    }
  }

  bfs(xs, ys, zs);
  cout << dist[xe][ye][ze] << '\n';

  return 0;
}
