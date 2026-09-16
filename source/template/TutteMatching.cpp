// Tutte Matrix & Rabin-Vazirani Maximum Matching on General Graphs
// Time: O(V^3) | Space: O(V^2)
const int MOD = 1e9 + 7;

long long qpow(long long a, long long b) {
    long long res = 1;
    for (a %= MOD; b > 0; b >>= 1, a = a * a % MOD)
        if (b & 1) res = res * a % MOD;
    return res;
}
long long minv(long long a) { return qpow(a, MOD - 2); }

struct TutteMatching {
    int n;
    vector<vector<int>> adj;
    mt19937 rng;

    TutteMatching(int n) : n(n), adj(n, vector<int>(n, 0)), rng(1337) {}
    void add_edge(int u, int v) { adj[u][v] = adj[v][u] = 1; }

    vector<vector<long long>> invert(vector<vector<long long>> M) {
        int k = M.size();
        vector<vector<long long>> inv(k, vector<long long>(k, 0));
        for (int i = 0; i < k; ++i) inv[i][i] = 1;
        for (int i = 0; i < k; ++i) {
            int p = i;
            while (p < k && M[p][i] == 0) p++;
            if (p == k) return {};
            if (p != i) { swap(M[i], M[p]); swap(inv[i], inv[p]); }
            long long inv_p = minv(M[i][i]);
            for (int j = 0; j < k; ++j) {
                M[i][j] = M[i][j] * inv_p % MOD;
                inv[i][j] = inv[i][j] * inv_p % MOD;
            }
            for (int r = 0; r < k; ++r) {
                if (r == i || M[r][i] == 0) continue;
                long long factor = M[r][i];
                for (int c = 0; c < k; ++c) {
                    M[r][c] = (M[r][c] - factor * M[i][c]) % MOD;
                    if (M[r][c] < 0) M[r][c] += MOD;
                    inv[r][c] = (inv[r][c] - factor * inv[i][c]) % MOD;
                    if (inv[r][c] < 0) inv[r][c] += MOD;
                }
            }
        }
        return inv;
    }

    vector<pair<int, int>> max_matching() {
        vector<vector<long long>> T(n, vector<long long>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (adj[i][j]) {
                    long long r = (rng() % (MOD - 1)) + 1;
                    T[i][j] = r; T[j][i] = (MOD - r) % MOD;
                }
            }
        }
        // Symmetric Gaussian Elimination -> Find basis S of size 2K
        vector<vector<long long>> M = T;
        vector<int> S;
        vector<bool> in_S(n, false);
        for (int i = 0; i < n; ++i) {
            if (in_S[i]) continue;
            int pivot = -1;
            for (int j = i + 1; j < n; ++j)
                if (!in_S[j] && M[i][j] != 0) { pivot = j; break; }
            if (pivot == -1) continue;
            int u = i, v = pivot;
            in_S[u] = in_S[v] = true;
            S.push_back(u); S.push_back(v);
            long long inv_val = minv(M[u][v]);
            for (int j = 0; j < n; ++j) {
                if (in_S[j]) continue;
                long long cu = M[u][j] * inv_val % MOD, cv = M[v][j] * inv_val % MOD;
                for (int k = 0; k < n; ++k) {
                    if (in_S[k]) continue;
                    M[j][k] = (M[j][k] - cu * M[v][k] + cv * M[u][k]) % MOD;
                    if (M[j][k] < 0) M[j][k] += MOD;
                }
            }
        }
        int K = S.size() / 2, sz = S.size();
        if (K == 0) return {};
        vector<vector<long long>> subT(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j) subT[i][j] = T[S[i]][S[j]];
        vector<vector<long long>> A = invert(subT);
        // Rabin-Vazirani Matching Extraction
        vector<pair<int, int>> matching;
        vector<bool> matched(sz, false);
        for (int step = 0; step < K; ++step) {
            int u = -1, v = -1;
            for (int i = 0; i < sz; ++i) if (!matched[i]) { u = i; break; }
            for (int j = 0; j < sz; ++j) {
                if (!matched[j] && adj[S[u]][S[j]] && A[u][j] != 0) { v = j; break; }
            }
            matched[u] = matched[v] = true;
            matching.push_back({S[u], S[v]});
            if (step + 1 == K) break;
            long long inv_Auv = minv(A[u][v]);
            for (int x = 0; x < sz; ++x) {
                if (matched[x]) continue;
                for (int y = 0; y < sz; ++y) {
                    if (matched[y]) continue;
                    long long delta = (A[x][u] * A[y][v] - A[x][v] * A[y][u]) % MOD;
                    if (delta < 0) delta += MOD;
                    A[x][y] = (A[x][y] + delta * inv_Auv) % MOD;
                }
            }
        }
        return matching;
    }
};
