// Kamil Dębowski
// Time Complexity O(n^2)
// Space Complexity O(n^2)

#include <bits/stdc++.h>
using namespace std;

void solve(int n, vector<vector<int>>& most) {
    int first = 0;
    while (first < n - 1 && most[first][n-1] == most[first+1][n-1]) {
        first++;
    }
    int last = n - 1;
    while (last > 0 && most[0][last] == most[0][last-1]) {
        last--;
    }
    string ans(n, '?');
    ans[first] = ans[last] = 'A';
    for (int i = first + 1; i < last; i++) {
        if (i == first + 1 || most[first][i-1] != most[first+1][i-1]) {
            // 'A' is most common
            if (most[first][i] != most[first][i-1]) {
                ans[i] = 'A';
            }
            continue;
        }
        if (i == last - 1 || most[i+1][last] != most[i+1][last-1]) {
            // 'A' is most common
            if (most[i][last] != most[i+1][last]) {
                ans[i] = 'A';
            }
            continue;
        }
        // 'A' is not most common in [first+1][i-1] and in [i+1][last-1]
        if (most[first+1][i] != most[first+1][i-1] || most[i][last-1] != most[i+1][last-1]) {
            ans[i] = '?'; // obvious
        }
        else {
            ans[i] = 'A'; // not obvious (needs proof)
        }
    }
    vector<int> res;
    for (int i = 0; i < n; i++) {
        if (ans[i] == 'A') {
            res.push_back(i + 1);
        }
    }

    for (int i = 0; i < (int) res.size(); i++) {
        cout << res[i] << " \n"[i == (int) res.size() - 1];
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> data(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cin >> data[i][j];
        }
    }

    solve(n, data);
}
