#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#define _ << " _ " <<

template<class> struct is_container : false_type {};
template<class... Ts> struct is_container<vector<Ts...>> : true_type {};
template<class... Ts> struct is_container<map<Ts...>> : true_type {};
template<class... Ts> struct is_container<unordered_map<Ts...>> : true_type {};
template<class... Ts> struct is_container<set<Ts...>> : true_type {};
template<class... Ts> struct is_container<unordered_set<Ts...>> : true_type {};
template<class... Ts> struct is_container<multiset<Ts...>> : true_type {};
template<class... Ts> struct is_container<unordered_multiset<Ts...>> : true_type {};
template<class T, class = typename enable_if<is_container<T>::value>::type>
ostream& operator<<(ostream &o, T x) {
  int f = 1;
  o << "{";
  for (auto y : x) {
    o << (f ? "" : ", ") << y;
    f = 0;
  }
  return o << "}";
}
template<class T, class U>
ostream& operator<<(ostream &o, pair<T, U> x) {
  return o << "(" << x.first << ", " << x.second << ")";
}

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vi> e(n, vi(n, INF));
    for (int i = 0; i < n; i++) e[i][i] = 0;
    while (m--) {
        int x, y, w;
        cin >> x >> y >> w;
        x--; y--;
        e[x][y] = min(e[x][y], w);
    }

    int k;
    cin >> k;
    k = min(k, n);
    auto sol = e;
    while (--k) {
        auto new_sol = sol; 
        for (int x = 0; x < n; x++)
            for (int y = 0; y < n; y++)
                for (int z = 0; z < n; z++)
                    new_sol[x][y] = min(new_sol[x][y], sol[x][z] + e[z][y]);
        sol = new_sol;
    }

    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (sol[x][y] == INF) sol[x][y] = -1;
        cout << sol[x][y] << '\n';
    }

    return 0;
}

