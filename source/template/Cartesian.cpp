int ls[MAXN], rs[MAXN];
void Cartesian(int a[], int n){ //1-index array
vector<int> stk;
a[0] = a[n + 1] = -inf;
FOR(i, 1, n){
    while(!stk.empty() and a[stk.back()] > a[i]) stk.pop_back();
    ls[i] = stk.empty() ? 0 : stk.back();
    stk.pb(i);
}
stk.clear(); stk.shrink_to_fit();
FORD(i, n, 1){
    while(!stk.empty() and a[stk.back()] > a[i]) stk.pop_back();
    rs[i] = stk.empty() ? n + 1 : stk.back();
    stk.pb(i);
}
stk.clear(); stk.shrink_to_fit();
FOR(i, 1, n){
    if (ls[i] == 0 and rs[i] == n + 1) cout << i - 1 << ' ';
    else{
        if (a[ls[i]] > a[rs[i]]) cout << ls[i] - 1 << ' ';
        else cout << rs[i] - 1 <<' ';
    }
}
}