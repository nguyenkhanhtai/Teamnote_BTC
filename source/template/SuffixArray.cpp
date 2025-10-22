int c[MAXN], cnt[MAXN], classes[MAXN];
int next_c[MAXN], next_classes[MAXN];
int lcp[MAXN], rk[MAXN];
//classes[i]: equivalent class that the ith suffix belongs to
//c[i]: the sorting of the suffixs
//lcp[i]: longest common prefix between suffix ith and (i+1)th.
//Remember that in suffix array, we jump backward to compare.
int curClass = 256;
for(int len = 1; len <= n * 2; len <<= 1){
    FOR(i, 0, curClass) cnt[i] = 0;
    if (len == 1){
        FOR(i, 0, n - 1) cnt[str[i]]++;
        FOR(i, 1, curClass) cnt[i] += cnt[i - 1];
        FORD(i, n - 1, 0) c[--cnt[str[i]]] = i; 

        int numClass = 0;
        FOR(i, 0, n - 1){
            if (i == 0) classes[c[i]] = numClass;
            else {
                if (str[c[i]] != str[c[i - 1]]) numClass++;
                classes[c[i]] = numClass;
            }
        }
        curClass = numClass;
    }
    else{
        FOR(i, 0, n - 1){
            int prv = ((c[i] - len / 2 + n) % n);
            cnt[classes[prv]]++;
        }

        FOR(i, 1, curClass) cnt[i] += cnt[i - 1];

        FORD(i, n - 1, 0){ 
            int prv = (c[i] - len / 2 + n) % n;
            next_c[--cnt[classes[prv]]] = prv;
        }
        FOR(i, 0, n - 1) c[i] = next_c[i];

        int numClass = 0;
        FOR(i, 0, n - 1){
            if (i == 0) next_classes[c[i]] = numClass;
            else {
                ii p1 = ii(classes[c[i]], classes[(c[i] + len / 2) % n]);
                ii p2 = ii(classes[c[i - 1]], classes[(c[i - 1] + len / 2) % n]);
                if (p1 != p2) numClass++;
                next_classes[c[i]] = numClass;
            }
        }    
        curClass = numClass;
        FOR(i, 0, n - 1) classes[i] = next_classes[i];    
    }        
}

for(int i = 0; i < n; i++){
    rk[c[i]] = i;
}

int k = 0;
FOR(i, 0, n - 1){
    if (rk[i] == n - 1){
        k = 0;
        continue;
    }
    int j = c[rk[i] + 1];
    while(i + k < n and j + k < n and str[i + k] == str[j + k]) k++;
    lcp[rk[i]] = k;

    if (k)
        k--;    
}