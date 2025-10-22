const int MAXN = 2e5 + 9;
int n,q;
vector<int> listval;
vector<int> Wavelet[MAXN<<2],position[200005];
// vector<int> Wavelet[MAXN<<2];
vector<int> a,tmp;
void merge(int node){
    int id1=0;
    int id2=0;
    while(id1 < Wavelet[node<<1].size() or id2 < Wavelet[node<<1|1].size()){
        if (id1 == Wavelet[node<<1].size()) Wavelet[node].pb(Wavelet[node<<1|1][id2++]);
        else if (id2 == Wavelet[node<<1|1].size()) Wavelet[node].pb(Wavelet[node<<1][id1++]);
        else{
            if (Wavelet[node<<1][id1] > Wavelet[node<<1|1][id2]) Wavelet[node].pb(Wavelet[node<<1|1][id2++]);
            else Wavelet[node].pb(Wavelet[node<<1][id1++]);
        }
    }
}
void build(int node,int l,int r){
    if (l==r){
        Wavelet[node] = position[l];
        return;
    }
    int mid = (l+r)>>1;
    build(node<<1,l,mid);
    build(node<<1|1,mid+1,r);
    merge(node);
}
int getkth(int node,int l,int r,int u,int v,int k){
    if (l==r) return l;
    else{
        int cnt = upper_bound(Wavelet[node<<1].begin(),Wavelet[node<<1].end(),v) - 
                  lower_bound(Wavelet[node<<1].begin(),Wavelet[node<<1].end(),u);
        int mid = (l+r)>>1;
        // if (u==1 and v==2) cout<<node<<' '<<cnt<<endl;
        if (k<=cnt) return getkth(node<<1,l,mid,u,v,k);
        else return getkth(node<<1|1,mid+1,r,u,v,k-cnt);
    }
}