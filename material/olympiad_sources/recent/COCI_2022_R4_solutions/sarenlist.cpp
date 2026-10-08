#include <cstdio>
#include <vector>


using namespace std;


const int MAXN = 61;
const int MAXM = 16;
const int MOD = 1000000007;

int n,m,k;
vector<int> graph[MAXN];
int depth[MAXN];
int parent[MAXN];
long long path[MAXM];

int popcount(long long x){
    int res=0;
    for(;x;x>>=1){
        if(x&1) res++;
    }
    return res;
}

int ADD(long long a, long long b){
    return (a+b)%MOD;
}
int SUB(long long a, long long b){
    return (a+MOD-b)%MOD;
}
int MUL(long long a, long long b){
    return a*b%MOD;
}
int EXP(long long a, long long b){
    if(b==0) return 1;
    if(b%2==1) return MUL(a, EXP(a, b-1));
    else return EXP(MUL(a, a), b/2);
}

void dfs(int node, int p=-1, int d=0){
    parent[node] = p;
    depth[node] = d;
    for(int i:graph[node]){
        if(i != p) dfs(i, node, d+1);
    }
}
void mark_path(int idx, int u, int v){
    if(depth[u] < depth[v]) swap(u, v);
    for(;depth[u] > depth[v];u = parent[u]){
        path[idx] |= (1LL<<u);
    }
    for(;u != v;u=parent[u],v=parent[v]){
        path[idx] |= (1LL<<v);
        path[idx] |= (1LL<<u);
    }
}

int uf[MAXM];
long long union_mask[MAXM];
int fnd(int a){
    return uf[a]=(uf[a]==a?a:fnd(uf[a]));
}
void un(int a, int b){
    a=fnd(a);
    b=fnd(b);
    uf[a]=b;
    union_mask[b] |= union_mask[a];
}
void reset_uf(){
    for(int i=0;i<m;i++) uf[i] = i;
    for(int i=0;i<m;i++) union_mask[i] = path[i];
}

int compute(int mask){
    reset_uf();
    for(int i=0;i<m;i++){
        if(!(mask & (1<<i))) continue;
        for(int j=i+1;j<m;j++){
            if(!(mask & (1<<j))) continue;
            if(path[i] & path[j]){
                un(i, j);
            }
        }
    }
    int cnt = 0;
    int not_on_paths=n-1;
    for(int i=0;i<m;i++){
        if(!(mask & (1<<i))) continue;
        if(i != uf[i]) continue;
        cnt++;
        not_on_paths -= popcount(union_mask[i]);
    }
    //printf("%d %d %d\n", mask, cnt, not_on_paths);
    return EXP(k, cnt+not_on_paths);
}

int main(){
    scanf("%d%d%d", &n, &m, &k);
    for(int i=0;i<n-1;i++){
        int a,b;
        scanf("%d%d", &a, &b);
//        a--;b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1);
    for(int i=0;i<m;i++){
        int c,d;
        scanf("%d%d", &c, &d);
//        c--;d--;
        mark_path(i, c, d);
    }
    int res=0;
    for(int mask=0;mask<(1<<m);mask++){
        int popcount = __builtin_popcount(mask);
        if(popcount % 2 == 0){
            res=ADD(res, compute(mask));
            //printf("%d +%d\n", mask, compute(mask));
        }else{
            res=SUB(res, compute(mask));
            //printf("%d -%d\n", mask, compute(mask));
        }
    }
    printf("%d\n", res);
}
