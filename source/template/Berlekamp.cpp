vector<int> berlekampMassey(vector<int> s) {
    if (s.size() == 0) return {};
    int n = sz(s), L = 0, m = 0;
    vector<int> C(n), B(n), T;
    C[0] = B[0] = 1;
    int b = 1;
    rep(i,0,n) { 
        ++m;
        int d = s[i] % mod;
        rep(j,1,L+1) d = (d + C[j] * s[i -j]) % mod;
        if (!d) continue;
        T = C; int coef = d * powmod(b, mod-2) % mod;
        rep(j,m,n) C[j] = (C[j] - coef * B[j - m]) % mod;
        if (2 * L > i) continue;
        L = i + 1 - L; B = T; b = d; m = 0;
    }
    C.resize(L + 1); C.erase(C.begin());
    for (int& x : C) x = (mod - x) % mod;
    return C;
}

typedef vector<int> Poly;
int linearRec(Poly a, Poly coef, int k) {
    int n = sz(coef);
    auto combine = [&](Poly a, Poly b) {  //FFT for faster
        Poly res(n * 2 + 1);
        rep(i,0,n+1) rep(j,0,n+1)
        res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
        for (int i = 2 * n; i > n; --i) rep(j,0,n)
        res[i - 1 - j] = (res[i - 1 - j] + res[i] * coef[j]) % mod;
        res.resize(n + 1);
        return res;
    };
    Poly pol(n + 1), e(pol);
    pol[0] = e[1] = 1;
    for (++k; k; k /= 2) {
    if (k % 2) pol = combine(pol, e);
    e = combine(e, e);
    }
    int res = 0;
    rep(i,0,n) res = (res + pol[i + 1] * a[i]) % mod;
    return res;
}
//Taken from KACTL