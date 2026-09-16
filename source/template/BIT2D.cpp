int BIT2D[1003][1003];
void update(int x, int y, int val){
    for(int i = x; i <= n; i += i & (-i)){
        for(int j = y; j <= m; j += j & (-j)){
            BIT2D[i][j] += val;
        }
    }
}
 
int get(int x, int y){
    int res = 0;
   for(int i = x; i > 0; i -= i & (-i)){
        for(int j = y; j > 0; j -= j & (-j)){
            res += BIT2D[i][j];
        }
    }
    return res;
}