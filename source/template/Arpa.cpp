int lab[MAXN], stk[MAXN], sz_stk = 0, newLeader;
inline int root(int u){
    return (lab[u] < 0) ? u : lab[u] = root(lab[u]);
}

inline int getMin(int id){
    return root(id);
}

vector<int> Query[10000007];
 void addQuery(int l, int r, int id){
        Query[r].pb(l);
}
void go(){
    FOR(i, 1, n){
        if (sz_stk == 0) {  stk[sz_stk++] = i;  }
        else{
            while(sz_stk > 0 and a[stk[sz_stk-1]] <= a[i]) {
                lab[stk[sz_stk - 1]] = i;
                sz_stk--;
            }
            stk[sz_stk++] = i;
        }

        for(auto q: Query[i]){
            ans  = (ans + a[getMin(q)]) % M;
        }
    }
}