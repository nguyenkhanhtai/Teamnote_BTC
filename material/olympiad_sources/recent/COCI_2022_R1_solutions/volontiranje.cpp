#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 1000005;

int n;
int p[MAXN];
vector <int> v[MAXN], r, st;
vector < vector <int> > out;

void build_LIS_struct () {
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(r.begin(), r.end(), p[i]) - r.begin();
        if (pos == r.size()) {
            r.push_back(p[i]);
        } else {
            r[pos] = p[i];
        }
        v[pos].push_back(i);
    }
    for (int i = 0; i < r.size(); i++) {
        reverse(v[i].begin(), v[i].end());
    }
}

void solve () {
    while (1) {
        if (st.size() == 0) {
            if (v[0].empty()) break;
            int pos = v[0].back();
            v[0].pop_back();
            st.push_back(pos);
        } else if (st.size() == r.size()) {
            out.push_back(st);
            st.clear();
        } else {
            int k = st.size();
            int curr = st.back();
            while (!v[k].empty() && v[k].back() < curr) v[k].pop_back();
            if (v[k].empty() || p[curr] > p[v[k].back()]) {
                st.pop_back();
            } else {
                int pos = v[k].back();
                v[k].pop_back();
                st.push_back(pos);
            }
        }
    }
}

void ispis () {
    cout << out.size() << " " << r.size() << endl;
    for (int i = 0; i < out.size(); i++) {
        for (auto x : out[i]) cout << x << " ";
        cout << '\n';
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    build_LIS_struct();
    solve();
    ispis();
    return 0;
}
