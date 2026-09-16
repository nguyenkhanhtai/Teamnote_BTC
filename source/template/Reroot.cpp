void dfs(int u, int p){
    for(auto e: g[u]){
        int v = e.fi, w = e.se;
        if (v == p) continue;
        dfs(v, u);
        //dp stuff
    }
}
 
void transition(int u, int v){
    //Detach v from the subtree of u

    //Attach u to the subtree of v
}
void reroot(int u, int p){
    //update answer
    for(auto e: g[u]){
        int v = e.fi, w = e.se;
        if (v == p) continue;
        transition(u, v, w);
        reroot(v, u, ans);
        transition(v, u, w);
    }
}