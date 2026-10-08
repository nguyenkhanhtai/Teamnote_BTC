#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 2005;

int n, m, sol;
char c[MAXN][MAXN];
bool bio[MAXN][MAXN];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int mn_sum, mx_sum, mn_dif, mx_dif, ok, cnt;

void dfs (int x, int y) {
    if (x == 0 || x == n + 1 || y == 0 || y == m + 1) {
        ok = 0;
        return;
    }
    if (bio[x][y] || c[x][y] == '#') return;
    bio[x][y] = 1;
    cnt++;

    mn_sum = min(mn_sum, x + y);
    mx_sum = max(mx_sum, x + y);
    mn_dif = min(mn_dif, x - y);
    mx_dif = max(mx_dif, x - y);

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        dfs(nx, ny);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> c[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (bio[i][j] || c[i][j] == '#') continue;

            mn_sum = mn_dif = 1e9;
            mx_sum = mx_dif = -1e9;
            ok = 1;
            cnt = 0;

            dfs(i, j);

            if (mx_sum - mn_sum == mx_dif - mn_dif && (mx_sum - mn_sum) % 2 == 0 && ok) {
                int d = (mx_sum - mn_sum) / 2 + 1;
                if (cnt == 2 * d * d - 2 * d + 1) sol++;
            }
        }
    }
    cout << sol;
    return 0;
}
