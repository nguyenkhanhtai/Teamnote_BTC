// Polynomial / FPS for MOD = 998244353 (primitive root = 3).
// Coefficient i of Poly p is p[i].  All operations are truncated to n when needed.
const int MOD = 998244353;

struct mint {
    int v;
    mint(long long x = 0) : v(int((x % MOD + MOD) % MOD)) {}
    mint pow(long long e) const {
        mint a = *this, r = 1;
        for (; e; e >>= 1, a *= a) if (e & 1) r *= a;
        return r;
    }
    mint inv() const { return pow(MOD - 2); }
    mint& operator += (mint o) { return v = (v += o.v) >= MOD ? v - MOD : v, *this; }
    mint& operator -= (mint o) { return v = (v -= o.v) < 0 ? v + MOD : v, *this; }
    mint& operator *= (mint o) { return v = 1LL * v * o.v % MOD, *this; }
    mint& operator /= (mint o) { return *this *= o.inv(); }
    friend mint operator + (mint a, mint b) { return a += b; }
    friend mint operator - (mint a, mint b) { return a -= b; }
    friend mint operator * (mint a, mint b) { return a *= b; }
    friend mint operator / (mint a, mint b) { return a /= b; }
    friend bool operator == (mint a, mint b) { return a.v == b.v; }
    friend bool operator != (mint a, mint b) { return a.v != b.v; }
};

using Poly = vector<mint>;

void ntt(Poly& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        mint wlen = mint(3).pow((MOD - 1) / len);
        if (invert) wlen = wlen.inv();
        for (int i = 0; i < n; i += len) {
            mint w = 1;
            for (int j = 0; j < len / 2; ++j, w *= wlen) {
                mint u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
            }
        }
    }
    if (invert) {
        mint inv_n = mint(n).inv();
        for (mint& x : a) x *= inv_n;
    }
}

Poly operator * (Poly a, Poly b) {
    if (a.empty() || b.empty()) return {};
    int need = (int)a.size() + (int)b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    ntt(a, true); a.resize(need);
    return a;
}

void norm(Poly& a) { while (!a.empty() && a.back() == 0) a.pop_back(); }
Poly cut(Poly a, int n) { a.resize(min((int)a.size(), n)); return a; }

Poly operator + (Poly a, const Poly& b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < (int)b.size(); ++i) a[i] += b[i];
    return a;
}
Poly operator - (Poly a, const Poly& b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < (int)b.size(); ++i) a[i] -= b[i];
    return a;
}
Poly operator * (Poly a, mint k) { for (mint& x : a) x *= k; return a; }
Poly operator * (mint k, Poly a) { return a * k; }

Poly derivative(const Poly& a) {
    Poly r(max(0, (int)a.size() - 1));
    for (int i = 1; i < (int)a.size(); ++i) r[i - 1] = a[i] * i;
    return r;
}
Poly integral(const Poly& a) {
    Poly r(a.size() + 1);
    for (int i = 0; i < (int)a.size(); ++i) r[i + 1] = a[i] / (i + 1);
    return r;
}

Poly inverse(const Poly& a, int n) { // requires a[0] != 0
    Poly r{a[0].inv()};
    for (int m = 1; m < n; m <<= 1) {
        Poly f = cut(a, 2 * m);
        r = cut(r * (Poly{2} - cut(f * r, 2 * m)), 2 * m);
    }
    return cut(r, n);
}

Poly logarithm(const Poly& a, int n) { // requires a[0] == 1
    return cut(integral(cut(derivative(a) * inverse(a, n), n - 1)), n);
}

Poly exponential(const Poly& a, int n) { // requires a[0] == 0
    Poly r{1};
    for (int m = 1; m < n; m <<= 1) {
        Poly q = cut(a, 2 * m) - logarithm(r, 2 * m);
        q[0] += 1;
        r = cut(r * q, 2 * m);
    }
    return cut(r, n);
}

Poly power(Poly a, long long k, int n) {
    if (k == 0) return Poly{1};
    int shift = 0;
    while (shift < (int)a.size() && a[shift] == 0) ++shift;
    if (shift == (int)a.size() || 1LL * shift * k >= n) return Poly(n);
    mint lead = a[shift];
    a.erase(a.begin(), a.begin() + shift);
    for (mint& x : a) x /= lead;
    Poly r = exponential(logarithm(a, n - shift * k) * mint(k), n - shift * k);
    r.insert(r.begin(), shift * k, 0);
    return cut(r * lead.pow(k), n);
}

Poly divide(Poly a, Poly b) { // quotient; b != 0
    norm(a); norm(b);
    if (a.size() < b.size()) return {};
    int n = (int)a.size() - (int)b.size() + 1;
    reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
    Poly q = cut(a * inverse(b, n), n);
    reverse(q.begin(), q.end());
    return q;
}
Poly modulo(Poly a, const Poly& b) {
    Poly q = divide(a, b);
    Poly r = a - q * b;
    r.resize(min((int)r.size(), max(0, (int)b.size() - 1)));
    norm(r); return r;
}
