#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;

    vector<int> v(n), where(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> v[i]; where[v[i]] = i;
    }

    int wrong = 0;
    for (int i = 0; i < n; ++i) {
        if (v[i] > v[(i + 1) % n]) wrong ++;
    }

    for (int i = 0; i < q; ++i) {
        int x, y; cin >> x >> y;

        auto f = [&v, &n](int index) {
            int ret = 0;
            if (v[(index - 1 + n) % n] > v[index]) ret ++;
            if (v[index] > v[(index + 1 + n) % n]) ret ++;
            return ret;
        };

        int posX = where[x];
        int posY = where[y];
        swap(where[x], where[y]);

        wrong -= f(posX);
        v[posX] = y;
        wrong += f(posX);
        wrong -= f(posY);
        v[posY] = x;
        wrong += f(posY);

        if (wrong == 1) {
            cout << "DA";
        }
        else {
            cout << "NE";
        }

        cout << '\n';
    }
}
