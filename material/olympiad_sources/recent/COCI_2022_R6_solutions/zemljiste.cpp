#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF_int = 0x3f3f3f3f;
const ll INF = (ll)INF_int * INF_int;
const int N=505;

int n, m, A, B;
int mat[N][N];
ll red[N][N], pref[N];

ll f(ll x) {
    return abs(x-A) + abs(x-B);
}

void solve() {
    if (A > B) swap(A, B);

    ll sol = INF;
    for (int j1=1; j1<=m; ++j1) {
        for (int j2=j1; j2<=m; ++j2) {
            for (int i=1; i<=n; ++i) pref[i]=pref[i-1] + red[i][j2] - red[i][j1-1];
            pref[n+2] = pref[n+1] = pref[n];

            int l=0;
            for (int i=1; i<=n; ++i) {
                while (pref[i] - pref[l] > B) ++l;

                sol = min(sol, f(pref[i] - pref[l]));
                if (l) sol = min(sol, f(pref[i] - pref[l - 1]));
            }
        }
    }
    printf("%lld\n", sol);
}

void load() {
    scanf("%d %d %d %d", &n, &m, &A, &B);
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            scanf("%d", &mat[i][j]);
            red[i][j] = red[i][j-1] + mat[i][j];
        }
    }
}

int main() {
    load();
    solve();
    return 0;
}
