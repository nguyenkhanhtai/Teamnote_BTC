const int MAXM = 3e4;
const int MAXN = 1e5 + 9;
int st[MAXN<<4],mn[MAXN<<4],lazy[MAXN<<4];
int n;
void update(int node,int l,int r,int u,int v,int x){
    if (l>=u and r<=v){
        mn[node] += x;
        if (mn[node] != 0) {
            st[node] = r - l + 1;
        }
        else if (l!=r) st[node] = st[node<<1] + st[node<<1|1];
        else st[node] = 0;
        return;
    }
    if (l>v or r<u){
        return;
    }
    int mid = (l+r)>>1;
    update(node<<1,l,mid,u,v,x);
    update(node<<1|1,mid+1,r,u,v,x);
    if (mn[node] != 0) st[node] = r - l + 1;
    else st[node] = st[node<<1] + st[node<<1|1];
}
struct verticalline{
    int x,y1,y2,type;
    verticalline(){
       x = y1 = y2 = 0;
       type = 0;
    }
    verticalline(int _x,int _y1,int _y2,int _t){
       x = _x;  type = _t;
       y1 = _y1;  y2 = _y2;
    }
    bool operator < (const verticalline &a){
       return x < a.x;
    }
};

verticalline r[MAXN];
cin>>n;
for(int i=1;i<=n;i++){
    int x1, y1, x2, y2;
    cin>>x1>>y1>>x2>>y2;
    r[i*2-1] = verticalline(x1,y1,y2,1);
    r[i*2] = verticalline(x2,y1,y2,-1);
}
sort(r+1,r+1+2*n);
int ptr1 = 1, ans = 0;
for(int i=1;i<=2*n-1;i++){
    update(1,0,MAXM,r[i].y1,r[i].y2-1,r[i].type);
    ans += (r[i+1].x - r[i].x) * st[1];
}
cout<<ans<<endl;
