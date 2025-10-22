
template<int32_t MOD> 
struct modint{
    int32_t value;
    // modint() = default;
    modint(int32_t value_ = 0): value(value_) {} 
    inline modint<MOD> operator + (const modint<MOD> &other) const { int32_t c = this->value + other.value; return modint<MOD>((c >= MOD) ? (c - MOD) : c); }
    inline modint<MOD> operator - (const modint<MOD> &other) const { int32_t c = this->value - other.value; return modint<MOD>((c < 0) ? (c + MOD) : c); }
    inline modint<MOD> operator * (const modint<MOD> &other) const { int32_t c = (int64_t) this->value * other.value % MOD; return modint<MOD>((c < 0) ? (c + MOD) : c);  }
    inline modint<MOD> & operator += (const modint<MOD> &other){ this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
    inline modint<MOD> & operator -= (const modint<MOD> &other){ this->value -= other.value; if (this->value < 0) this->value += MOD; return *this; }
    inline modint<MOD> & operator *= (const modint<MOD> &other){ this->value = (int64_t) this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this;}
    inline modint<MOD> operator - () const { return modint<MOD> ((this->value) ? (MOD - this->value) : 0);    }
    modint<MOD> pow(uint64_t k) const{
        modint<MOD> x = *this, y = 1;
        for(;k; k>>=1){
            if(k&1) y = y * x;
            x = x * x; 
        }
        return y;
    }

    inline modint<MOD> inv() const{       return pow(MOD - 2);     } //for prime modulo only.
    inline modint<MOD> operator / (const modint<MOD> &other) const { return ((*this) * other.inv()); }
    inline modint<MOD> operator /= (const modint<MOD> &other) {  return ((*this) *= other.inv);}
    inline bool operator == (const modint<MOD> &other) const {  return this->value == other.value;  }
    inline bool operator < (const modint<MOD> &other) const  { return this->value < other.value; }
    inline bool operator > (const modint<MOD> &other) const  { return this->value > other.value; }
    inline bool operator <= (const modint<MOD> &other) const { return this->value <= other.value; }
    inline bool operator >= (const modint<MOD> &other) const { return this->value >= other.value; }
    inline bool operator != (const modint<MOD> &other) const { return this->value != other.value; }
    friend ostream& operator << (ostream &out, modint<MOD> a) {
        out << a.value;
        return out;
    }
};
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value) * n; }

using mint = modint<MODULO>;
typedef complex<double> cd;

namespace FFT{
    vector<vector<cd>> w(21);
    vector<vector<cd>> inv_w(21);

    int done = 0, mxLvl = 0;
    void precalc(int lvl){
        if (lvl <= mxLvl) return;

        w[0].resize(1);
        inv_w[0].resize(1);

        w[0][0] = 1;
        inv_w[0][0] = 1;
        FOR(i, mxLvl, lvl - 1){
            w[i + 1].resize((1 << i + 1) + 2);
            inv_w[i + 1].resize((1 << i + 1) + 2);

            cd unit = polar(1.0, 1.0 * acos(-1.0) / (1 << i)) ; //e^(i * phi)
            cd inv_unit = polar(1.0, -1.0 * acos(-1.0) / (1 << i));

            FOR(j, 0, (1 << i) - 1){
                w[i + 1][j * 2] = w[i][j];
                w[i + 1][j * 2 + 1] = w[i][j] * unit;

                inv_w[i + 1][j * 2] = inv_w[i][j];
                inv_w[i + 1][j * 2 + 1] = inv_w[i][j] * inv_unit;            
            }
        }
        mxLvl = lvl;

    }
    vector<cd> DFT(vector<cd> a, int inv){
        int n = sz(a);
        vector<int> rev(n);
        FOR(i, 0, n - 1){
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) ? (n / 2) : 0);
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }

        for(int h = 1, l = 2, lvl = 1; l <= n; l <<= 1, h <<= 1, lvl++){
            for(int i = 0; i < n; i += l){
                for(int j = 0; j < h; j++){
                    cd u = a[i + j];
                    cd v = a[i + j + h];

                    if (inv){
                        a[i + j] = u + v * w[lvl][j];
                        a[i + j + h] = u - v * w[lvl][j];
                    }
                    else{
                        a[i + j] = u + v * inv_w[lvl][j];
                        a[i + j + h] = u - v * inv_w[lvl][j];
                    }


                    if (inv){
                        a[i + j] /= 2.0;
                        a[i + j + h] /= 2.0;
                    }
                }


            }
        }
        return a;
    }
    vector<int> FFT(vector<int> a, vector<int> b){
        int n = 1, taken = sz(a) + sz(b), lvl = 0;
        while(n < (int) a.size() + b.size()) {
            n <<= 1;
            lvl++;
        }
        precalc(lvl);

        vector<cd> c(n), fc(n);
        if (sz(a) < n) a.resize(n);
        if (sz(b) < n) b.resize(n);

        FOR(i, 0, n - 1){
            c[i] = cd(a[i], b[i]);
        }
        c = DFT(c, 0);
        FOR(i, 0, n - 1){
            c[i] = c[i] * c[i];
        }
        FOR(i, 0, n - 1){
            fc[i] = (c[i] - conj(c[(n - i) % n])) / cd(0, 4);
        }
        fc = DFT(fc, 1);
        vector<int> res(taken - 1);
        FOR(i, 0, taken - 2){
            res[i] = real(fc[i] + 0.5);
        }
        
        return res;
    }

    vector<int> multiply(vector<int> a, vector<int> b, int MOD){
        int n = 1, taken = sz(a) + sz(b);
        while(n < taken) n <<= 1;
        vector<int> a0(sz(a)), a1(sz(a));
        vector<int> b0(sz(b)), b1(sz(b));
        int base = sqrt(MOD);

        FOR(i, 0, sz(a) - 1){
            a0[i] = a[i] >> 15;
            a1[i] = a[i] & ((1 << 15) - 1);

        }
        FOR(i, 0, sz(b) - 1){
            b0[i] = b[i] >> 15;
            b1[i] = b[i] & ((1 << 15) - 1);

        }

        vector<int> X1 = FFT(a0, b0);
        vector<int> X2 = FFT(a0, b1);
        vector<int> X3 = FFT(a1, b0);
        vector<int> X4 = FFT(a1, b1);
        vector<int> res(taken - 1);

        FOR(i, 0, taken - 2){
            X1[i] %= MOD; X2[i] %= MOD; X3[i] %= MOD; X4[i] %= MOD;
            int base2 = (1 << 30);
            int base1 = (1 << 15);
            int base0 = 1;
            res[i] = ((X1[i] << 30) + ((X2[i] + X3[i]) << 15) + X4[i]) % MOD;
        }
        return res;
    }

}

namespace NTT{

    vector<int> w(25);
    vector<int> inv_w(25);

    vector<int> rev;

    int add(int u, int v){ return ((u + v >= MODULO) ? (u + v - MODULO) : u + v); }

    int sub(int u, int v){ return ((u - v < 0) ? (u - v + MODULO) : (u - v)); }

    int mul(int u, int v){ return (1LL * u * v % MODULO);     }
    int binpow(int a,int b) {
        int res = 1;
        for(;b; b >>= 1){
            if(b&1) res = mul(res, a);
            a = mul(a, a);
        }
        return res;
    }

    int invmod(int x){
        return binpow(x, MODULO - 2);
    }

    vector<int> NTT(vector<int> a, int inv){
        int n = sz(a);
        rev.resize(n);
        FOR(i, 0, n - 1){
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) ? (n / 2) : 0);
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }

        w[23] = binpow(3, 119);
        inv_w[23] = invmod(w[23]);

        FORD(i, 22, 0){
            w[i] = mul(w[i + 1], w[i + 1]);
            inv_w[i] = mul(inv_w[i + 1], inv_w[i + 1]);
        } 

        int inv2 = invmod(2);

        for(int half = 1, len = 2, lvl = 1; len <= n; half <<= 1, len <<= 1, lvl++){
            for(int i = 0; i < n; i += len){
                int curW = 1;
                for(int j = 0; j < half; j++){
                    int u = a[i + j];
                    int v = a[i + j + half];
                    a[i + j] = add(u, mul(v, curW));
                    a[i + j + half] = sub(u, mul(v, curW));

                    curW = mul(curW, ((inv) ? inv_w[lvl] : w[lvl]));
                    if (inv){
                        a[i + j] = mul(a[i + j], inv2);
                        a[i + j + half] = mul(a[i + j + half], inv2); 
                    }

                }
            }
        }
        return a;
    }
    vector<int> multiply(vector<int> a, vector<int> b){ //FOR 998244353
        int n = 1, lvl = 0, taken = sz(a) + sz(b);
        while(n < (int) sz(a) + sz(b)){
            n <<= 1;
            lvl++;
        }

        a.resize(n);
        b.resize(n);

        a = NTT(a, 0);
        b = NTT(b, 0);
        vector<int>c(n);

        FOR(i, 0, n - 1){
            c[i] = mul(a[i], b[i]);
        }

        c = NTT(c, 1);
        vector<int> res(taken - 1);
        FOR(i, 0, taken - 2) res[i] = c[i];
        return res; 
    }

    void test(){
        vector<int> a = {1, 2, 3, 4};
        vector<int> b = {1, 2, 3, 4, 5};
        vector<int> res = multiply(a, b);
        for(int i = 0; i < res.size(); i++){
            cout << res[i] << ' ';
        }
        cout << endl;
    }
}
struct Poly{
    vector<mint> c;

    inline void normalize(){
        while(c.size() and c.back() == 0) c.pop_back();
    }

    template <class...Args>
    Poly(Args...args): c(args...) {}
    
    Poly(const initializer_list<mint> &x): c(x.begin(), x.end()) {}
    
    inline int size() const{ return c.size(); }
    
    inline mint coef(int i) const { return ((i < sz(c) and i >= 0) ? c[i] : 0); }
    
    mint operator [](const int i) const { return ((i < sz(c) && i >= 0) ? c[i] : 0);  }
    
    bool is_zero() const { for(int i = 0; i < size(); i++) if (c[i] != 0) return false; return true;}

    int trailing_xk(){
        //count number of trailing zeros.
        if (is_zero()) return -1;
        int res = 0;
        while(res < size() and c[res] == 0){
            res++;
        }
        return res;
    }
    
    Poly xk(int k, int n) const{
        Poly ans(n, 0);
        if (k < n){
            ans.c[k] = 1;
        }
        return ans;
    }

    Poly operator + (const Poly &other) const {
        int n = max(size(), other.size());
        vector<mint> ans(n);
        for(int i = 0; i < n; i++) ans[i] = coef(i) + other.coef(i);
        while((int) ans.size() and ans.back() == 0) ans.pop_back();
        return ans;
    }
    Poly operator - (const Poly &other) const {
        int n = max(size(), other.size());
        vector<mint> ans(n);
        for(int i = 0; i < n; i++) ans[i] = coef(i) - other.coef(i);
        while((int) ans.size() and ans.back() == 0) ans.pop_back();
        return ans;
    }


    Poly operator * (const Poly &other) const{
        if (is_zero() or other.is_zero()) return {};
        vector<int> A, B;
        for(int i = 0; i < size(); i++) A.push_back(c[i].value);
        for(int i = 0; i < other.size(); i++) B.push_back(other.c[i].value);

        vector<int> res;
        if (MODULO == 998244353) res = NTT::multiply(A, B);
        else res = FFT::multiply(A, B, MODULO);

        vector<mint> ans;
        for(auto x: res) ans.pb((mint) x);
        while((int) ans.size() and ans.back() == 0) ans.pop_back();
        return ans;
    }

    Poly operator * (const mint &other) const{
        int n = size();
        vector<mint> ans(n);
        for(int i = 0; i < n; i++) ans[i] = c[i] * other;
        return ans;
    }

    Poly& operator += (const Poly &other) { return *this = (*this) + other; }
    Poly& operator -= (const Poly &other) { return *this = (*this) - other; }
    Poly& operator *= (const Poly &other) { return *this = (*this) * other; }
    Poly operator / (const mint &other) {  return (*this) * other.inv();  }
    Poly& operator /= (const mint &other) { return (*this) = (*this) * other.inv(); }

    Poly mod_xk(int k) const{ return vector<mint>(c.begin(), c.begin() + min(k, (int) c.size())); }
    Poly mul_xk(int k) const{
        Poly ans(*this);
        ans.c.insert(ans.c.begin(), k, 0);
        return ans;
    }
    Poly div_xk(int k) const{ return vector<mint>(c.begin() + min(k, (int) c.size()), c.end());    }
    Poly substr(int l,int r) const { 
        l = min(l, size());
        r = min(r, size());
        return vector<mint>(c.begin() + l, c.begin() + r);
    }
    Poly differentiate() const {
        int n = size();
        vector<mint> ans(n);
        for(int i = 1; i < size(); i++) ans[i - 1] = coef(i) * i;
        return ans;
    }

    Poly integrate() const{
        int n = size(); 
        vector<mint> ans(n + 1);
        for(int i = 0; i < size(); i++) ans[i + 1] = coef(i) / (i + 1);
        return ans;
    }

    Poly inverse(int n) const {
        assert(!is_zero()); assert(c[0] != 0);
        Poly ans{mint(1) / c[0]};
        for(int i = 1; i < n; i <<= 1){
            ans = (ans * mint(2) - ans * ans * mod_xk(2 * i)).mod_xk(2 * i);
        }
        return ans.mod_xk(n);
    }

    Poly log(int n) const {
        assert(c[0] == 1);
        Poly ans = (differentiate() * inverse(n)).integrate();
        return ans.mod_xk(n);
        return {};
    }

    Poly exp(int n) const{
        Poly ans{1};
        for(int i = 1; i < n; i <<= 1){
            Poly P = (Poly{1} + mod_xk(2 * i) - ans.log(2 * i));
            ans = ans * P;
        }
        return ans.mod_xk(n);
    }

    Poly reverse() const{
        vector<mint> rev(c.begin(), c.end());
        std::reverse(rev.begin(), rev.end());
        return Poly(rev);
    }

    Poly operator / (const Poly &other) const{
        int n = sz(c);
        int m = sz(other);
        if (n < m) return {};
        else{
            Poly Q = ((reverse() * (other.reverse()).inverse(n - m + 1)).mod_xk(n - m + 1)).reverse();
            Q.normalize();
            return Q;
        }
    }

    Poly operator % (const Poly &other) const{
        int n = sz(c);
        int m = sz(other);
        if (n < m) return (*this);
        else{
            Poly ans = (*this) - ((*this) / other) * other;
            ans.normalize();
            return ans;
        }
    }
    Poly pow(uint64_t k, int n){
        if (k == 0) return {1};
        
        if (is_zero()) return (*this);
        int t = trailing_xk();

        

        Poly T = div_xk(t);
        
        mint j = T[0];
        T = T / j;

        int ok = true;
        if (t > n / k) ok = false; 

        return  (xk( ((ok) ? (t * k) : n + 1), n) * j.pow(k)) * (T.log(n) * mint(k % MODULO)).exp(n); 
    }
};


