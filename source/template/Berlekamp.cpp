// Berlekamp-Massey: Finds shortest linear recurrence C: s[i] = \sum_{j=0}^{L-1} C[j] * s[i-1-j]
// linearRec: Computes K-th term (0-indexed) in O(N^2 log K) via x^K mod P(x)
vector<int> berlekampMassey(const vector<int>& s) {
    int n = s.size(), L = 0, m = 0;
    vector<int> C(n, 0), B(n, 0), T;
    C[0] = B[0] = 1;
    long long b = 1;
    for (int i = 0; i < n; ++i) {
        ++m;
        long long d = s[i] % MOD;
        for (int j = 1; j <= L; ++j) d = (d + 1LL * C[j] * s[i - j]) % MOD;
        if (!d) continue;
        T = C;
        long long coef = d * power(b, MOD - 2) % MOD;
        for (int j = m; j < n; ++j) C[j] = (C[j] - coef * B[j - m] % MOD + MOD) % MOD;
        if (2 * L > i) continue;
        L = i + 1 - L; B = T; b = d; m = 0;
    }
    C.resize(L + 1); C.erase(C.begin());
    for (int& x : C) x = (MOD - x) % MOD;
    return C; // recurrence coefficients
}

int linearRec(const vector<int>& S, const vector<int>& tr, long long k) {
    int n = tr.size();
    if (n == 0) return 0;
    if (k < (int)S.size()) return (S[k] % MOD + MOD) % MOD;
    auto combine = [&](const vector<int>& a, const vector<int>& b) {
        vector<int> res(2 * n + 1, 0);
        for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++)
            res[i + j] = (res[i + j] + 1LL * a[i] * b[j]) % MOD;
        for (int i = 2 * n; i > n; --i) for (int j = 0; j < n; j++)
            res[i - 1 - j] = (res[i - 1 - j] + 1LL * res[i] * tr[j]) % MOD;
        res.resize(n + 1);
        return res;
    };
    vector<int> pol(n + 1, 0), e(n + 1, 0);
    pol[0] = e[1] = 1;
    for (++k; k; k /= 2) {
        if (k % 2) pol = combine(pol, e);
        e = combine(e, e);
    }
    long long res = 0;
    for (int i = 0; i < n; i++) res = (res + 1LL * pol[i + 1] * S[i]) % MOD;
    return (res + MOD) % MOD;
}