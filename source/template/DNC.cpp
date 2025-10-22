
//DNC: Condition: opt(l, r) <= opt(l, r + 1)

void compute(int l,int r,int optl,int optr){
    if (l>r) return;
    int mid = (l+r)/2;
    
    ii best = {INF,-1};
    for(int x=optl;x<=min(mid,optr);x++){
        best = min(best, ii(dp_before[x] + Cost(x+1,mid),x));
    }
    
    dp_cur[mid] = best.fi;
    int opt = best.se;
    compute(l,mid-1,optl,opt);
    compute(mid+1,r,opt,optr);
}

//Knuth: Condition: opt(l - 1, r) <= opt(l, r) <= opt(l, r + 1)
for (int i = 0; i < N; i++) {
    opt[i][i] = i;
    ... // Initialize dp[i][i] according to the problem
}
for (int i = N-2; i >= 0; i--) {
    for (int j = i+1; j < N; j++) {
        int mn = INT_MAX;
        int cost = C(i, j);
        for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
            if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                opt[i][j] = k; 
                mn = dp[i][k] + dp[k+1][j] + cost; 
            }
        }
        dp[i][j] = mn; 
    }
}