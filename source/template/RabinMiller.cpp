//Rabin Miller: Primality Test
using int128 = __int128_t;
int mul(int a, int b, int mod){ return (int128) a * b % mod; }
int binpow(int a, int b, int mod){
    //mod <= 10^18.
    int res = 1;
    for(;b; b>>=1){
        if (b&1) res = mul(res, a, mod);
        a = mul(a, a, mod);
    }
    return res;
}
vector<int> pr = {2, 3, 7, 61};
ii factorize(int x){
    int s = 0, d = x;
    while(d % 2 == 0){
        s++;
        d >>= 1;
    }
    return ii(s, d);
}
bool rabin_test(int a, int n, int s, int d){
    int u = binpow(a, d, n);
    if (u == 1 or u == n - 1) return false;
    for(int i = 1; i < s; i++){
        u = mul(u, u, n);
        if (u == n - 1) return false;
    }
    return true;
}

bool rabin_miller(int n){
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int res = 1;
    int s, d;
    tie(s, d) = factorize(n - 1);
    FOR(i, 0, sz(pr) - 1){
        if (pr[i] == n) 
            return true;
        if (rabin_test(pr[i], n, s, d)){
            return false;
        }
    }
    return true;
}
