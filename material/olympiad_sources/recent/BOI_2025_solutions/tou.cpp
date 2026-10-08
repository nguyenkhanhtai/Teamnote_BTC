// Arkadiusz Czarkowski
// Time complexity O(m + n), memory O(m + n).
// Model solution.
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,l,r)for(int i=(l);i<=(r);++i)
#define REP(i,n)FOR(i,0,(n)-1)
#define ssize(x)int(x.size())

void solve() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> edges(m);
    for (auto& [a, b, c] : edges) {
        cin >> a >> b >> c;
        --a, --b, --c;
    }

    const int UNVISITED = 0;
    const int ON_STACK = 1;
    const int PROCESSED = 2;
    using State = pair<int, int>; // {color, state}
    vector<vector<State>> state(n);
    REP(i, n) {
        state[i].reserve(3);
    }
    auto get_state = [&](int v, int x) {
        for (auto [a, b] : state[v]) {
            if (a == x) {
                return b;
            }
        }
        return (ssize(state[v]) >= 3 ? PROCESSED : UNVISITED);
    };
    auto set_state = [&](int v, int x, int value) {
        for (auto& [a, b] : state[v]) {
            if (a == x) {
                b = value;
                return;
            }
        }
        if (ssize(state[v]) < 3) {
            state[v].emplace_back(x, value);
        }
    };

    vector<vector<int>> graph(n);
    REP(i, m) {
        const auto [a, _b, _c] = edges[i];
        graph[a].emplace_back(i);
    }

    vector<int> stack, cycle;
    auto dfs = [&](auto&& self, int v, int id) -> bool {
        const int c = get<2>(edges[id]);
        set_state(v, c, ON_STACK);
        for (auto next_id : graph[v]) {
            const auto [_v, x, next_c] = edges[next_id];
            const int next_state = get_state(x, next_c);
            if (c == next_c or next_state == PROCESSED) {
                continue;
            }
            if (next_state == ON_STACK) {
                while (true) {
                    auto [d, _e, f] = edges[stack.back()];
                    cycle.emplace_back(stack.back());
                    stack.pop_back();
                    if (f != next_c and d == x) {
                        break;
                    }
                }
                cycle.emplace_back(next_id);
                reverse(cycle.begin(), cycle.end());
                return true;
            }
            stack.emplace_back(next_id);
            if (self(self, x, next_id))
                return true;
            stack.pop_back();
        }
        set_state(v, c, PROCESSED);
        return false;
    };
    REP(i, m) {
        auto [_a, b, c] = edges[i];
        if (get_state(b, c) == PROCESSED) {
            continue;
        }
        if (dfs(dfs, b, i)) {
            cout << "YES" << '\n';
            cout << ssize(cycle);
            REP(j, ssize(cycle)) {
                cout << ' ' << cycle[j] + 1;
            }
            cout << '\n';
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    REP(tt, t)
        solve();
}
