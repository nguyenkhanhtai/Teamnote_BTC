#include<bits/stdc++.h>

using namespace std;

struct edge {
    int to;
    int back_idx;
    int who;
};

vector<vector<edge>> g;
vector<int> act;
unordered_set<int> ids;

void add_euler(int a, int b, int who) {
    g[a].push_back({b, g[b].size(), who});
    g[b].push_back({a, g[a].size() - 1, who});
    ids.insert(a);
    ids.insert(b);
}

void visit(int v) {
    while(not g[v].empty()) {
        auto e = g[v].back(); g[v].pop_back();
        if(e.back_idx == -1) continue;
        g[e.to][e.back_idx].back_idx = -1;
        visit(e.to);
        if(e.who >= 0) act[e.who] = v;
    }
}

void cleanup() {
    for(int x : ids) g[x].clear();
    ids.clear();
}

vector<int> merge(const vector<pair<int, int>> &v) {
    cleanup();
    act.resize(v.size());

    for(int i = 0; i < v.size(); ++i)
        add_euler(v[i].first, v[i].second, i);
    for(int x : ids)
        if(g[x].size() % 2)
            add_euler(x, 0, -1);
    for(int x : ids)
        visit(x);

    return act;
}

void solve(vector<vector<int>> &choices) {
    int T = choices[0].size();
    if(T == 1) return;

    vector<vector<int>> L(choices.size()), R(choices.size());
    for(int i = 0; i < choices.size(); ++i) {
        for(int j = 0; j < T / 2; ++j)
            L[i].push_back(choices[i][j]);
        for(int j = 0; j < T / 2; ++j)
            R[i].push_back(choices[i][j + T/2]);
    }

    vector<vector<int>> v = L;
    for(auto r : R) v.push_back(r);
    solve(v);
    for(int i = 0; i < L.size(); ++i) L[i] = v[i];
    for(int i = 0; i < R.size(); ++i) R[i] = v[i + L.size()];

    for(int i = 0; i < T/2; ++i) {
        vector<pair<int, int>> v;
        for(int j = 0; j < R.size(); ++j)
            v.emplace_back(L[j][i], R[j][i]);
        vector<int> a = merge(v);

        for(int j = 0; j < R.size(); ++j)
            if(a[j] != L[j][i]) swap(L[j][i], R[j][i]);
    }

    choices.assign(choices.size(), {});
    for(int i = 0; i < choices.size(); ++i) {
        for(int x : L[i]) choices[i].push_back(x);
        for(int x : R[i]) choices[i].push_back(x);
    }
}

int main() {
    int N, T, K; scanf("%d %d %d", &N, &T, &K);
    g.resize(K + 1);
    vector<vector<int>> choices(N);

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < T; ++j) {
            int a; scanf("%d", &a);
            choices[i].push_back(a);
        }
    }

    solve(choices);

    for(const auto &c : choices) {
        for(int x : c) printf("%d ", x);
        printf("\n");
    }

    return 0;
}