#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 200;

int move(char c){
    printf("%c\n", c);
    fflush(stdout);
    int x; 
    if(c == 'K') scanf("%d", &x);
    return x;
}

int gdje[N][4], stanje[N], NODE = 1;


void dfs(int cur, int fir = 0){
    move('X'); move('D');
    stanje[cur] = 1;
    for(int k = 0;k < 3 + fir;k++){
        int should = move('K');
        if(!should){
            gdje[cur][k] = NODE++;
            dfs(NODE - 1);    
        }
        else{
            move('L'); move('L');
        }
        move('K'); move('D');
    }
    if(fir) move('L');
}

int cnt[6];

void skuzi_vrh(){
    move('X');
    int deg = 0, lst = 1;
    for(;lst;deg++){
        lst = move('K');
        move('L');
    }
    move('X');
    cnt[deg]++;
}

void skuzi_sve(int cur){
    move('D');
    for(int k = 0;k < 4;k++){
        skuzi_vrh();
        if(gdje[cur][k] != -1){
            move('K');
            skuzi_sve(gdje[cur][k]);
            move('L'); move('L');
            move('K'); move('D');
        }
        else{
            move('L');
        }
    }
    move('L');
}

int main(){
    memset(gdje, -1, sizeof(gdje));
    dfs(0, 1);
    skuzi_sve(0);
    printf("! %d\n", 1 + (NODE - cnt[3] / 3 - cnt[4] / 4 - cnt[5] / 5) / 2);
    fflush(stdout);
    return 0;
}
