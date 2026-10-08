#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 100005;

int n, tc;
int lef[MAXN], rig[MAXN], sol[MAXN];
string s;
set <int> st;
set <pi> pq;
vector <int> tmp;
vector <pi> v;

bool makni (int pos) {
    auto it = st.lower_bound(pos);
    if (it == st.end()) return 0;
    st.erase(it);
    return 1;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> tc;
    for (int t = 0; t < tc; t++) {
        st.clear(); pq.clear(); tmp.clear(); v.clear();
        bool rip = 0;

        cin >> n >> s;
        s = "." + s;
        for (int i = 1; i <= n; i++) {
            cin >> lef[i] >> rig[i];
            if (s[lef[i]] == '(' && s[rig[i]] == '(') {
                tmp.push_back(lef[i]);
                sol[i] = 0;
            } else if (s[lef[i]] == ')' && s[rig[i]] == ')') {
                st.insert(rig[i]);
                sol[i] = 1;
            } else if (s[lef[i]] == '(' && s[rig[i]] == ')') {
                st.insert(rig[i]);
                v.push_back({lef[i], i});
                sol[i] = 1;
            } else {
                st.insert(lef[i]);
                v.push_back({lef[i], i});
                sol[i] = 0;
            }
        }
        for (auto pos : tmp) {
            if (!makni(pos)) {
                cout << -1 << '\n';
                rip = 1;
                break;
            }
        }
        if (rip) continue;

        sort(v.begin(), v.end());
        int p = -1;
        while (!st.empty()) {
            int lim = *st.begin();
            while (p + 1 < v.size() && v[p + 1].first <= lim) {
                p++;
                int ind = v[p].second;
                pq.insert({rig[ind], ind});
            }
            bool ok = 1;
            if (pq.empty()) {
                ok = 0;
            } else {
                int ind = pq.begin() -> second;
                pq.erase(pq.begin());
                sol[ind] = !sol[ind];
                if (!makni(lef[ind])) ok = 0;
                if (!makni(rig[ind])) ok = 0;
            }
            if (!ok) {
                cout << -1 << '\n';
                rip = 1;
                break;
            }
        }
        if (rip) continue;

        for (int i = 1; i <= n; i++) {
            cout << sol[i] << " ";
        }
        cout << '\n';
    }
    return 0;
}
