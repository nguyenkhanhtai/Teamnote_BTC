#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef long long llint;

const int maxn = 2010;
const int base = 31337;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
const int logo = 20;
const int off = 1 << logo;
const int treesiz = off << 1;

int n, m;
bool red[maxn], stupac[maxn];
bool glavna[maxn], sporedna[maxn];
bool bio[maxn][maxn];

int main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        char t;
        int x, y;
        scanf(" %c%d%d", &t, &x, &y); x--, y--;

        if (t == 'R' || t == 'Q') red[x] = stupac[y] = true;
        if (t == 'B' || t == 'Q') glavna[x - y + n] = sporedna[x + y] = true;
        if (t == 'K') {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    int tx = x + i;
                    int ty = y + j;
                    if (tx < 0 || tx >= n || ty < 0 || ty >= n) continue;
                    bio[tx][ty] = true;
                }
            }
        }
        if (t == 'N') {
            bio[x][y] = true;
            for (int i = -2; i < 3; i++) {
                for (int j = -2; j < 3; j++) {
                    int tx = x + i;
                    int ty = y + j;
                    if (abs(i * j) != 2) continue;
                    if (tx < 0 || tx >= n || ty < 0 || ty >= n) continue;
                    bio[tx][ty] = true;
                }
            }
        }
    }

    int sol = 0;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            if (red[i] || stupac[j] || glavna[i - j + n] || sporedna[i + j] || bio[i][j]) sol++;
    printf("%d\n", sol);
	return 0;
}

