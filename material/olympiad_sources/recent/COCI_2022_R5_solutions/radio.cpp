#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
typedef pair<int,int> ii;

const int MAXN = 1<<20;

int n, q;

int sieve[MAXN];
void init_sieve(){
    for(int i=2;i<MAXN;i++){
        if(sieve[i]==0){
            for(int j=i;j<MAXN;j+=i){
                sieve[j] = i;
            }
        }
    }
}

bool on[MAXN];
unordered_map<int, set<int>> transmitting;

int seg[2*MAXN][2];
void init_segtree(){
    for(int i=0;i<2*MAXN;i++){
        seg[i][0] = -1;
        seg[i][1] = MAXN;
    }
}

void update_segtree(int idx, int vl, int vr){
    idx+=MAXN;
    seg[idx][0] = vl;
    seg[idx][1] = vr;
    for(idx/=2;idx>0;idx/=2){
        seg[idx][0] = max(seg[2*idx][0], seg[2*idx+1][0]);
        seg[idx][1] = min(seg[2*idx][1], seg[2*idx+1][1]);
    }
}
ii query_segtree(int left, int right, int node=1, int nl=0, int nr=MAXN-1){
    if(left > nr || right<nl) return ii(-1, MAXN);
    if(left<=nl && nr<=right) return ii(seg[node][0], seg[node][1]);
    ii a = query_segtree(left, right, 2*node, nl, nl+(nr-nl)/2);
    ii b = query_segtree(left, right, 2*node+1, nl+(nr-nl)/2+1, nr);
    return ii(max(a.first, b.first), min(a.second, b.second));
}

void fixup_segtree(int x){
    //printf("fixup %d\n", x);
    int left=-1, right=MAXN;
    for(int p=sieve[x], tmp=x;tmp != 1;){
        auto& ps = transmitting[p];
        
        auto lit = ps.lower_bound(x);
        if(lit != ps.begin()){
            lit--;
            left = max(left, *lit);
        }

        auto rit = ps.upper_bound(x);
        if(rit != ps.end()) right = min(right, *rit);

        while(tmp % p == 0){
            tmp /= p;
        }
        p = sieve[tmp];
    }
    //printf("%d %d\n", left, right);
    update_segtree(x, left, right);
}
int get_left(int x){
    return seg[MAXN+x][0];
}
int get_right(int x){
    return seg[MAXN+x][1];
}

void switch_station(int x){
    if(x == 1) return;
    vector<int> changed;
    int left=-1, right=MAXN;
    for(int p=sieve[x], tmp=x;tmp != 1;){ 
        auto& ps = transmitting[p];

        auto lit = ps.lower_bound(x);
        if(lit != ps.begin()){
            lit--;
            if(!on[x] && get_right(*lit)>x){
                update_segtree(*lit, get_left(*lit), x);
            }else if(on[x] && get_right(*lit) == x){
                changed.push_back(*lit);
            }
            left = max(*lit, left);
        }

        auto rit = ps.upper_bound(x);
        if(rit != ps.end()){
            if(!on[x] && get_left(*rit)<x){
                update_segtree(*rit, x, get_right(*rit));
            }else if(on[x] && get_left(*rit) == x){
                changed.push_back(*rit);
            }
            right = min(*rit, right);
        }
        if(!on[x]) ps.insert(x);
        else ps.erase(x);

        while(tmp % p == 0){
            tmp /= p;
        }
        p = sieve[tmp];
    }
    if(on[x]){
        update_segtree(x, -1, MAXN);
        on[x] = false;
    }else{
        update_segtree(x, left, right);
        on[x] = true;
    }
    sort(changed.begin(), changed.end());
    changed.erase(unique(changed.begin(), changed.end()), changed.end());
    for(int i:changed){
        fixup_segtree(i);
    }
}

bool noisy(int l, int r){
    ii x = query_segtree(l, r);
    //printf("%d %d\n", x.first, x.second);
    return x.first >= l || x.second <= r;
}

int main(){
    init_sieve();
    init_segtree();
    scanf("%d%d", &n, &q);
    for(int i=0;i<q;i++){
        char s[20];
        scanf("%s", s);
        if(s[0] == 'S'){
            int x;
            scanf("%d", &x);
            switch_station(x);
        }else if(s[0] == 'C'){
            int l, r;
            scanf("%d%d", &l, &r);
            if(noisy(l, r)){
                puts("DA");
            }else{
                puts("NE");
            }
        }
        //for(int i=1;i<=n;i++){
        //    ii x = query_segtree(i, i);
        //    printf("%d %d", x.first, x.second);
        //    printf(" -> %d %d\n", seg[MAXN+i][0], seg[MAXN+i][1]);
        //}
    }
}
