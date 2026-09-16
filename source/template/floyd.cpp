for(int i = 1; i <= n; i++){
    dist[i][i] = 0;
}

for(int k = 1; k <= n; k++){
    for(int u = 1; u <= n; u++){
        for(int v = 1; v <= n; v++){
            minimize(dist[u][v], dist[u][k] + dist[k][v]);
        }
    }
}