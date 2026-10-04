const int MOD = 998244353, G = 3;
long long power(long long a, long long b) {
    long long res = 1;
    for (a %= MOD; b; b >>= 1, a = a * a % MOD) if (b & 1) res = res * a % MOD;
    return res;
}
long long modInverse(long long n) { return power(n, MOD - 2); }

void ntt(vector<int>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = power(G, (MOD - 1) / len);
        if (invert) wlen = modInverse(wlen);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v >= MOD ? u + v - MOD : u + v);
                a[i + j + len / 2] = (u - v < 0 ? u - v + MOD : u - v);
                w = w * wlen % MOD;
            }
        }
    }
    if (invert) {
        long long inv_n = modInverse(n);
        for (int& x : a) x = x * inv_n % MOD;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int sz = 1, need = a.size() + b.size() - 1;
    while (sz < need) sz <<= 1;
    a.resize(sz); b.resize(sz);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < sz; i++) a[i] = 1LL * a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(need);
    return a;
}
