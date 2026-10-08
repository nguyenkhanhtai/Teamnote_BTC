#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef long long llint;

const int maxn = 2e5+10;
const int base = 31337;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
const int logo = 20;
const int off = 1 << logo;
const int treesiz = off << 1;

int n;
vector< pair<int, int> > a, b;
char s[maxn];

int conv(int h, int m) {
    return h * 60 + m;
}

int len(int a, int b) {
    if (b < a) return b - a + 1 + 24 * 60;
    return b - a + 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int h1, m1, h2, m2;
        scanf("%s %d:%d--%d:%d", s, &h1, &m1, &h2, &m2);
        pair<int, int> tr = {conv(h1, m1), conv(h2, m2)};
        if (s[0] == 'Z') a.push_back(tr);
        else b.push_back(tr);
    }

    int sol = inf;
    for (auto x : a) {
        for (auto y : b) {
            int tren = len(x.X, x.Y);
            int tl = y.X - x.Y - 1;
            if (tl < 0) tl += 24 * 60;
            tren += tl;
            tren += len(y.X, y.Y);
            sol = min(sol, tren);
        }
    }
    if (sol == inf) printf("NEMOGUCE\n");
    else printf("%d:%02d\n", sol / 60, sol % 60);
	return 0;
}

