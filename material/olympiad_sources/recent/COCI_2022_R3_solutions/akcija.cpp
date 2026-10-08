#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 2005;
const int OFS = 1024 * 2;
const llint INF = 1000000000000000000LL;

int n, k, curr_idx;
llint w[MAXN], best_substitute[MAXN];
int d[MAXN], status[MAXN][MAXN], opt[MAXN][MAXN];
priority_queue <pair<pair<int, llint>, pair<int,int> > > pq;

struct node {
    int mn = 0, pos = 0, prop = 0;

    node () {}

    node (int _mn, int _pos, int _prop) {
        mn = _mn; pos = _pos; prop = _prop;
    }
} INF_NODE(2 * OFS, 0, 0);

struct tour {
    node nodes[2 * OFS];

    tour () {}

    node spoji (node a, node b) {
        if (a.mn < b.mn) return a; else return b;
    }

    void init () {
        for (int i = 0; i < OFS; i++) {
            nodes[i + OFS].mn = i;
            nodes[i + OFS].pos = i;
            nodes[i + OFS].prop = 0;
        }
        for (int i = OFS - 1; i > 0; i--) {
            nodes[i] = spoji(nodes[2 * i], nodes[2 * i + 1]);
        }
    }

    void propagate (int x) {
        if (nodes[x].prop == 0) return;

        if (x < OFS) {
            nodes[2 * x].prop += nodes[x].prop;
            nodes[2 * x + 1].prop += nodes[x].prop;
        }

        nodes[x].mn += nodes[x].prop;
        nodes[x].prop = 0;
    }

    void update (int x, int from, int to, int lo, int hi, int val) {
        propagate(x);
        if (from <= lo && hi <= to) {
            nodes[x].prop += val;
            propagate(x);
            return;
        }
        if (to < lo || hi < from) return;
        update(2 * x, from, to, lo, (lo + hi) / 2, val);
        update(2 * x + 1, from, to, (lo + hi) / 2 + 1, hi, val);
        nodes[x] = spoji(nodes[2 * x], nodes[2 * x + 1]);
    }

    void update (int from, int to, int val) {update(1, from, to, 0, OFS - 1, val);}

    node upit (int x, int from, int to, int lo, int hi) {
        propagate(x);
        if (from <= lo && hi <= to) return nodes[x];
        if (to < lo || hi < from) return INF_NODE;
        node lef = upit(2 * x, from, to, lo, (lo + hi) / 2);
        node rig = upit(2 * x + 1, from, to, (lo + hi) / 2 + 1, hi);
        return spoji(lef, rig);
    }

    node upit (int from, int to) {return upit(1, from, to, 0, OFS - 1);}
} t;

void make_sorted () {
    vector < pair <llint, int> > v;
    for (int i = 1; i <= n; i++) {
        v.push_back({w[i], d[i]});
    }
    sort(v.begin(), v.end());
    for (int i = 1; i <= n; i++) {
        w[i] = v[i - 1].first;
        d[i] = v[i - 1].second;
    }
}

void pop_next () {
    pair <int, llint> value = pq.top().first;
    pair <int, int> delta = pq.top().second;
    pq.pop();

    //cout << curr_idx << ":  " << value.first << " " << -value.second << "  " << delta.first << " " << delta.second << endl;
    cout << value.first << " " << -value.second << endl;

    int parent_idx = delta.first;
    int old_pos = delta.second;

    if (parent_idx == -1) return;
    for (int i = 1; i <= n; i++) {
        status[curr_idx][i] = status[parent_idx][i];
        if (status[parent_idx][i] == 0 && opt[parent_idx][i] == 1) {
            if (i  < old_pos) status[curr_idx][i] = 1;
            if (i == old_pos) status[curr_idx][i] = -1;
            if (i  > old_pos) status[curr_idx][i] = 0;
        }
    }
}

pair <int, llint> calc_opt () {
    int br = 0;
    llint sum = 0;
    t.init();

    for (int i = 1; i <= n; i++) {
        opt[curr_idx][i] = 0;

        if (status[curr_idx][i] == 1 || status[curr_idx][i] == 0 && t.upit(d[i], OFS - 1).mn > 0) {
            t.update(d[i], OFS - 1, -1);
            opt[curr_idx][i] = 1;
            br++;
            sum += w[i];
        }
    }

    return {br, sum};
}

void add_neighbours (pair <int, llint> current_value) {
    for (int i = 0; i <= n; i++) {
        best_substitute[i] = INF;
    }
    for (int i = 1; i <= n; i++) {
        if (status[curr_idx][i] == 0 && opt[curr_idx][i] == 0) {
            best_substitute[d[i]] = min(best_substitute[d[i]], w[i]);
        }
    }
    for (int i = n-1; i >= 0; i--) {
        best_substitute[i] = min(best_substitute[i], best_substitute[i + 1]);
    }

    for (int i = 1; i <= n; i++) {
        if (status[curr_idx][i] == 0 && opt[curr_idx][i] == 1) {

            int rightmost_zero = t.upit(0, d[i] - 1).pos;

            llint sum, num;
            if (best_substitute[rightmost_zero + 1] == INF) {
                num = current_value.first - 1;
                sum = current_value.second - w[i];
            } else {
                num = current_value.first;
                sum = current_value.second - w[i] + best_substitute[rightmost_zero + 1];
            }

            //cout << "ubaci sus " << num << " " << sum << "  " << curr_idx << " " << i << endl;
            pq.push({{num, -sum}, {curr_idx, i}});
        }
    }
}

void gen_ranking () {
    pair <int, llint> tmp = calc_opt();
    pq.push({{tmp.first, -tmp.second}, {-1, -1}});

    while (curr_idx < k) {
        if (pq.empty()) {
            cout << "-1 -1" << endl;
            curr_idx++;
        } else {
            pop_next();
            add_neighbours(calc_opt());
            curr_idx++;
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> d[i];
    }
    make_sorted();
    gen_ranking();
    return 0;
}
