#include <bits/stdc++.h>
using namespace std;

vector<int> load() {
    int n; cin >> n;

    vector<int> ret(n + 1);
    for (int i = 0; i < n; ++i)
        cin >> ret[i + 1];

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    vector<int> v[2];
    v[0] = load();
    v[1] = load();

    int n = v[0].size() - 1;
    int m = v[1].size() - 1;
    int inf = (n + m) * 33;

    vector<vector<int>> dp[2];
    dp[0] = vector<vector<int>>(n + 1, vector<int>(m + 1));
    dp[1] = vector<vector<int>>(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {

            if (!i && !j) continue;

            for (int k = 0; k < 2; ++k) {

                dp[k][i][j] = inf;
                if (i - (1 - k) < 0) continue;
                if (j - k < 0) continue;

                for (int l = 0; l < 2; ++l) {
                    int add = 1;
                    if (v[k][i * (1 - k) + j * k] == v[l][(i - (1 - k)) * (1 - l) + (j - k) * l]) add ++;
                    dp[k][i][j] = min(dp[k][i][j], dp[l][i - (1 - k)][j - k] + add);
                }
            }
        }
    }

    cout << min(dp[0][n][m], dp[1][n][m]) << endl;
}
