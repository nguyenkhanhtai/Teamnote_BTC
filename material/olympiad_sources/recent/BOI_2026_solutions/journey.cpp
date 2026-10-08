#include <iostream>
#include <vector>
#include <array>
#include <cassert>

using namespace std;

const long M = 1e9+7;

int main(int argc, char **argv) {
    int n, m, k;
    cin >> n >> m >> k;
    struct E {
        int u, v, w, del, acti = -1;
        int other(int i) {
            return i == u ? v : u;
        }
        int dir(int from) {
            return from == v;
        }
    };
    vector<E> es;
    vector<vector<int>> adj(n+1);
    vector<int> deg(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(es.size());
        adj[v].push_back(es.size());
        es.emplace_back(u, v, 1, 0);
        deg[u]++;
        deg[v]++;
    }

    vector<int> z(n+1);
    vector<int> q;
    for (int i = 2; i < n; ++i) if (deg[i] <= 2) {
        q.push_back(i);
        z[i] = 1;
    }
    for (int qi = 0; qi < (int)q.size(); ++qi) {
        int i = q[qi];
        erase_if(adj[i], [&](int ei) { return es[ei].del; });
        if (deg[i] == 1) {
            auto &e = es[adj[i][0]];
            e.del = 1;
            deg[e.u]--;
            deg[e.v]--;
            int o = e.other(i);
            if (o != 1 && o != n && !z[o] && deg[o] <= 2) {
                q.push_back(o);
                z[o] = 1;
            }
        } else if (deg[i] == 2) {
            int ia = adj[i][0];
            auto &ea = es[adj[i][0]];
            auto &eb = es[adj[i][1]];
            int oa = ea.other(i);
            int ob = eb.other(i);
            if (oa == ob) continue; // no self-loops
            eb.del = 1;
            adj[ob].push_back(ia);
            ea.w += eb.w;
            if (ea.u == i) ea.u = ob;
            else ea.v = ob;
        }
    }

    erase_if(es, [](auto e) { return e.del; });
    int nm = es.size();

    for (int ei = 0; ei < nm; ++ei) {
        es[ei].acti = ei;
    }

    vector<vector<array<long, 2>>> dp(k+1, vector(nm, array<long, 2>{}));
    // for (auto e : es) {
    //     cerr << e.acti << ": " << e.u << " " << e.v << " " << e.w << endl;
    // }
    for (auto e : es) {
        if (e.w > k) continue;
        if (e.u == 1 || e.v == 1) {
            dp[e.w][e.acti][e.dir(1)]++;
        }
    }
    for (int d = 1; d < k; ++d) {
        for (int ei1 = 0; ei1 < nm; ++ei1) {
            for (int dir1 = 0; dir1 < 2; ++dir1) {
                int i = dir1 ? es[ei1].u : es[ei1].v;
                for (int ei2 = 0; ei2 < nm; ++ei2) {
                    if (ei1 == ei2) continue;
                    if (es[ei2].u == i || es[ei2].v == i) {
                        int dir2 = es[ei2].dir(i);
                        if (d + es[ei2].w > k) continue;
                        dp[d + es[ei2].w][ei2][dir2] += dp[d][ei1][dir1];
                        dp[d + es[ei2].w][ei2][dir2] %= M;
                    }
                }
            }
        }
        // cerr << d << endl;
        // for (int ei = 0; ei < nm; ++ei) {
        //     cerr << dp[d][ei][0] << ":" << dp[d][ei][1] << " ";
        // }
        // cerr << endl;
    }

    long res = 0;
    for (auto e : es) {
        if (e.u == n || e.v == n) {
            res += dp[k][e.acti][!e.dir(n)];
            res %= M;
        }
    }
    cout << res << endl;

    // Check answer is as expected
    if (argc >= 6) {
        long ans = atol(argv[5]);
        if (ans != -1 && ans != res) {
            cerr << "answer " << res << " not expected" << endl;
            throw;
        }
    }
}
