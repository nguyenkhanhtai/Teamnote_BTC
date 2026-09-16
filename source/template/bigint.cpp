using bignum = vector<int>;

bignum operator + (const bignum &a, const bignum &b){
    bignum res;
    int carry = 0;
    for(int i = 0; i < max(b.size(), a.size()); i++){
        int c1 = (i < sz(a)) ? a[i] : 0;
        int c2 = (i < sz(b)) ? b[i] : 0;
        int c = (c1 + c2 + carry);
        res.pb(c % 10);
        carry = c / 10;
    }
    while(carry) {
        res.pb(carry % 10);
        carry /= 10;
    }
    return res;
}
bignum operator * (const bignum &a, int k){
    bignum res;
    int carry = 0;
    for(int i = 0; i < a.size(); i++){
        int c = (a[i] * k + carry);
        res.pb(c % 10);
        carry = c / 10;
    }
    while(carry) {
        res.pb(carry % 10);
        carry /= 10;
    }
    return res;
}