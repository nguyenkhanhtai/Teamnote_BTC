vector<mint> a, b, preA, preB;
int n;
vector<mint> fwht(vector<mint> a){
    vector<mint> res(a.begin(), a.end());
    for(int s = 2, h = 1; s <= (int) a.size(); s <<= 1,  h <<= 1){
        for(int l = 0; l < sz(a); l += s){
            for(int i = 0; i < h; i++){
                mint tmp = res[l + i + h];
                res[l + i + h] = res[l + i] - tmp;
                res[l + i] = res[l + i] + tmp;
            }
        }
    }
    return res;
}
vector<mint> fwht_inv(vector<mint> a){
    mint inv2 = mint(1) / 2;
    vector<mint> res(a.begin(), a.end());
    for(int s = sz(a), h = sz(a) / 2; s >= 2; s >>= 1, h >>= 1){
        for(int l = 0; l < sz(a); l += s){
            for(int i = 0; i < h; i++){
                mint u = (res[l + i]);
                mint v = (res[l + i + h]);
                res[l + i] = (u + v) * inv2; 
                res[l + i + h] = (u - v) * inv2;
            }
        }
    }
    return res;
}
vector<mint> FWHT_A = fwht(a);
vector<mint> FWHT_B = fwht(b);
vector<mint> FWHT_res ((1 << n));
FOR(i, 0, (int) sz(FWHT_A) - 1){
    FWHT_res[i] = FWHT_A[i] * FWHT_B[i];
}
FWHT_res = fwht_inv(FWHT_res);