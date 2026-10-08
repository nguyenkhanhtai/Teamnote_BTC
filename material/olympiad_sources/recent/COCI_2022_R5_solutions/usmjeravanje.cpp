#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ll long long
#define X first
#define Y second

using namespace std;

const int MAXN = 500100;
vector <pair <int, int> > ve[2];
map <pair <int, int>, int> ind;
int sol[MAXN];

int main() {
    ios_base::sync_with_stdio(false);

    int A, B, m;
    cin >> A >> B >> m;

    REP(i, m) {
        int x, y;
        cin >> x >> y;

        ve[0].push_back({x, y});
        ve[1].push_back({y, x});
        ind[{x, y}] = i;
    }

    sort(ve[0].begin(), ve[0].end());
    sort(ve[1].begin(), ve[1].end());

    int x = 0, y = 0;
    int out = A + B;

    while (x < ve[0].size() && y < ve[1].size()) {
        int X = ve[0][x].first, Y = ve[1][y].first;

        int u = ve[1][y].second;
        int d = ve[0][x].second;

        sol[ind[ve[0][x]]] = 1;

        bool flag = true;
        while (flag) {
            flag = false;
            if (x < ve[0].size() && ve[0][x].first <= u) {
                if (d < ve[0][x].second)  sol[ind[ve[0][x]]] = 1;
                d = max(d, ve[0][x].second);
                x++;
                flag = true;
            }
            if (y < ve[1].size() && ve[1][y].first <= d) {
                u = max(u, ve[1][y].second);
                y++;
                flag = true;
            }
        }

        if (u == X && d == Y) continue;
        if (u == X) sol[ind[{X, Y}]] = 0;
        if (d == Y) sol[ind[{X, Y}]] = 1;

        out -= (u - X + 1) + (d - Y + 1) - 1;

        /*cout << X << " " << u << endl;
        cout << Y << " " << d << endl;
        cout << "------\n";*/
    }

    cout << out << "\n";
    REP(i, m) cout << sol[i] << " ";

    return 0;
}