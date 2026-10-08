#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;

int n;
long long sol=0;
char str[2*MAXN];
char s1[MAXN], s2[MAXN];

void make_anagram(){
    int total[26], cnt[26]; 
    fill(cnt, cnt+26, 0);
    fill(total, total+26, 0);
    for(int i=0;i<2*n;i++) total[str[i]-'a']++;
    int s1i=0, s2i=0;
    for(int i=0;i<n;i++){
        int c = str[i]-'a';
        if(cnt[c] >= total[c]/2){
            sol+=(n+s2i)-i;
            s2[s2i++] = str[i];
        }else{
            s1[s1i++] = str[i];
        }
        cnt[c]++;
    }
    int m=n;
    for(int i=n;i<2*n;i++){
        int c = str[i]-'a';
        if(cnt[c] < total[c]/2){
            sol+=i-m;
            m++;
            s1[s1i++] = str[i];
        }else{
            s2[s2i++] = str[i];
        }
        cnt[c]++;
    }
}

long long fen[2][MAXN];

void update(long long * fen, int idx, int val){
    for(idx++;idx<MAXN;idx+=idx&(-idx)){
        fen[idx] += val;
    }
}
long long query(long long * fen, int idx){
    long long res = 0;
    for(idx++;idx>0;idx-=idx&(-idx)){
        res += fen[idx];
    }
    return res;
}

void setup(long long * fen){
    for(int i=1;i<n;i++)
        update(fen, i, 1);
}
void update_after(long long * fen, int idx){
    update(fen, idx+1, -1);
}
int updated_idx(long long * fen, int idx){
    return query(fen, idx);
}

void rearrange(){
    vector<int> idx1[26], idx2[26];
    for(int i=n-1;i>=0;i--){
        idx1[s1[i]-'a'].push_back(i);
        idx2[s2[i]-'a'].push_back(i);
    }
    setup(fen[0]);
    setup(fen[1]);
    auto cost = [&] (int c) -> int {return idx1[c].size()?updated_idx(fen[0], idx1[c].back()) + updated_idx(fen[1], idx2[c].back()):10*MAXN;};
    for(int i=0;i<n;i++){
        int c = 0;
        for(int j=1;j<26;j++){
            if(cost(j) < cost(c)){
                c = j;
            }
        }
        sol += cost(c);
        update_after(fen[0], idx1[c].back());
        update_after(fen[1], idx2[c].back());
        idx1[c].pop_back();
        idx2[c].pop_back();
    }
}

int main(){
    scanf("%d", &n);
    scanf("%s", str);
    make_anagram();
    rearrange();
    printf("%lld\n", sol);
}
