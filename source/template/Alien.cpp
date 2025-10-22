ii dp[MAXN];
 
ii count(int mid, int pre[]){
    ii best = {-inf, -inf};
    dp[0] = {0, 0};
    FOR(i, 1, n){
        dp[i] = dp[i - 1];

        int j = max(i - l, 0LL);
        int v = dp[j].fi + getRange(j + 1, i, pre) - mid;
        maximize(dp[i], ii(v, dp[j].se - 1));
        maximize(best, dp[i]);
    }
    best.se = -best.se;
    return best;
}

int l = 0, r = 1e9, res = -1;
while(l <= r){
    int mid = (l + r) / 2;
    ii cur = count(mid, preUpper);
    if (cur.se <= k){
        res = mid;
        r = mid - 1;
    }  
    else{
        l = mid + 1;
    }
}