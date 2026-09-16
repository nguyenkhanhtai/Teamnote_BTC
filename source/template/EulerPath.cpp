const int MAXN = 5e5 + 9;
int t, n, m, start, ending;
ii edge[MAXN];
vector<int> g[MAXN];
/**
This is the code for eulerian path in directed graph.
For undirected, minor adjustments could be done for use.
**/
int degOut[MAXN], degIn[MAXN], visEdge[MAXN], visNode[MAXN];
vector<int> ansV, ansE; 
//AnsV: Eulerian Path
//AnsE: Edges of the Path
void dfs(int u, int par){
    while(g[u].size() > 0){
        int id = g[u].back();
        int v = edge[id].fi + edge[id].se - u;
        g[u].pop_back();
        dfs(v, id);
    }
    ansV.pb(u);
    if (par != -1) ansE.pb(par);
}
bool valid(){
    bool ch = true;
    start = -1, ending = -1;
    int num1 = 0, num2 = 0;
    FOR(i, 0, n - 1){
        if (degOut[i] > degIn[i]) {
            start = i;
            num1++;
        }
        if (degIn[i] > degOut[i]) {
            ending = i;
            num2++;
        }
        if (abs(degOut[i] - degIn[i]) >= 2 or num1 > 1 or num2 > 1) return false;
    }

    return (num1 == num2);
}
if (!valid()){
    cout << "No" << endl;
}
else{
    if (start != -1) {
        dfs(start, -1);
        reverse(ansE.begin(), ansE.end());
        reverse(ansV.begin(), ansV.end());

        if (ansE.size() == m){
            cout << "Yes" << endl;
            for(auto v: ansV){
                cout <<v  << ' ';
            }
            cout << endl;
            for(auto e: ansE){
                cout << e << ' ';
            }
            cout << endl;
        }
        else cout << "No" << endl;

    }
    else{
        FOR(i, 0, n - 1){
            if (g[i].size() > 0) {  //Find the first Edge
                dfs(i, -1);
                start = i;
                break;
            }
        }
        reverse(ansE.begin(), ansE.end());
        reverse(ansV.begin(), ansV.end());
        if (ansE.size() == m){
            cout << "Yes" << endl;
            if (ansV.size() == 0) cout << 0;

            FOR(i, 0, (int) ansV.size() - 1){
                cout << ansV[i] << ' ';
            }
            cout << endl;
            FOR(i, 0, (int) ansE.size() - 1){
                cout << ansE[i] << ' ';
            }
            cout << endl;
        }
        else cout << "No" << endl;
    }


}
FOR(i, 0, n - 1){
    g[i].clear();
    degIn[i] = degOut[i] = 0;
}
ansV.clear();
ansE.clear();