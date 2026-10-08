#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

llint n, mn = 1e9, sol;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        llint x;
        cin >> x;
        sol += x;
        mn = min(mn, x);
    }
    cout << sol + (n-2) * mn;
    return 0;
}
