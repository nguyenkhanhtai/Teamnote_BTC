namespace BabyStepGiantStep{
    map<int, int> mp;
    int gcd(int a,int b){
        if (a == 0) return b;
        else return gcd(b % a, a);
    }
    int mul(int a,int b,int mod){
        return (1LL * a * b) % mod;
    }
    int solve(int a,int b,int m){
        int g, add = 0, k = 1;
        mp.clear();
        while((g = gcd(a, m)) > 1){
            if (k == b){
                return add;
            }
            if (b % g != 0){
                return INF;
            }
            add++;
            k = mul(k, a / g, m);
            m /= g; b /= g;
        }
        if (k == b) return add;
        int block = sqrt(m) + 1, OneBlock = 1;
        int cur = b; 
        for(int i = 1; i <= block; i++){
            cur = mul(cur, a, m);
            OneBlock = mul(OneBlock, a, m);
            mp[cur] = i;
        } 
        cur = k;
        for(int i = 1; i <= block; i++){
            cur = mul(cur, OneBlock, m);
            if (mp.find(cur) != mp.end()){
                return i * block - mp[cur] + add;
            }
        }
        return INF;
    }