
random_shuffle(a + 1, a + 1 + n);
FOR(i, 1, n){
    int ii = i&1;
    int exp_u = (u * i) / n;
    int exp_v = (v * i) / n;
    FOR(cur_u, max(0LL, exp_u - SQRT), min(u, exp_u + SQRT)){
        FOR(cur_v, max(0LL, exp_v - SQRT), min(v, exp_v + SQRT)){

            FOR(taken_u, 0, min(1LL, cur_u)){
                FOR(taken_v, 0, min(1LL, cur_v)){
                    double prob = taken_u * a[i].fi + taken_v * a[i].se - (taken_u and taken_v) * a[i].fi * a[i].se;
                    maximize(dp[ii][cur_u][cur_v], (1 - prob) * dp[!ii][cur_u - taken_u][cur_v - taken_v] +                                                                     prob * (1 + dp[!ii][cur_u - taken_u][cur_v - taken_v]));
                }
            }
        }
    }
}
cout << setprecision(6) << fixed << dp[n&1][u][v] << endl;
