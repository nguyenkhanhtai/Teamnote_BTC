void dfs(){
    map<vector<int>, int> mp;
    FORD(i, n - 1, 0){
        vector<int> res(g[i].size());
        for(int j = 0; j < g[i].size(); j++){
            res[j] = answer[g[i][j]];
        }
        sort(res.begin(), res.end());
        if (!mp.count(res)) mp.insert(make_pair(res, mp.size()));
        answer[i] = mp[res];
    }
    cout << mp.size() << endl;
    FOR(i, 0, n - 1){
        cout << answer[i] << ' ';
    }
    cout << endl;
}