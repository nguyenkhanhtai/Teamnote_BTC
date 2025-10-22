namespace lagrage{
    int f[1000004];
    void prep(int k,int d){
        f[0] = 0;
        for(int i = 1; i <= d + 1; i++){
            f[i] = cong(f[i-1], binpow(i, k));
        }
    }
    int gcded(int a,int b,int &x,int &y){
        if (a == 0){
            x = 0, y = 1;
            return b;
        }
        int g, x1, y1;
        g = gcded(b % a, a, x1, y1);
        y = x1;
        x = y1 - (b / a) * x1;
        return g;
    }

    int inv(int a,int m){
        int g, x, y;
        g = gcded(a, m, x, y);
        return x;
    }

    int refine(int a){
        return ((a % MOD) + MOD) % MOD;
    }
    int solve(int n,int k){ //calc 1^k + 2^k + ... + n^k --> k + 2 diem
//        if (k == 0) return n % MOD;
//        if (k == 1) return (nhan(n, nhan(n + 1, binpow(2, MOD - 2) )));
        prep(k, k + 1);
        int res = 0;
        int numerator = 1;
        int denumerator = 1;
        if (n <= k + 2) {
            return f[n];
        }
        for(int i = 2; i <= k + 2; i++){
            numerator = nhan(numerator, refine(n - i));
            denumerator = nhan(denumerator, refine(1 - i));
        }
        for(int i = 1; i <= k + 2; i++){
            int bonus = f[i];
            res = cong(res, nhan(bonus, nhan( numerator, inv(denumerator, MOD)  )  )   );

            numerator = nhan(numerator, refine(n - i));
            numerator = nhan(numerator, refine(inv(refine(n - i - 1), MOD))  );

            denumerator = nhan(denumerator, refine(inv(refine(i - k - 2), MOD))  );
            denumerator = nhan(denumerator, i);
        }
        return res;
    }
}