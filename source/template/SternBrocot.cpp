vector<pair<char, int>> ENCODE_PATH(int p, int q, bool skip = true){
    vector<pair<char,int>> res;
    int right = 1;
    while(q){
        if (p/q or !skip) res.pb({(right ? 'R' : 'L'), p / q});
        tie(p, q) = ii(q, p % q);
        right ^= 1;
    }
    res.back().se--;
    if (res.back().se == 0) res.pop_back();
    return res;
}

ii DECODE_PATH(int k, vector<pair<char,int>> path){
    if (k == 0) return {1, 1};

    if (sz(path) and path[0].fi == 'L') path.insert(path.begin(), ii('R', 0LL));

    vector<int> p = {0, 1};
    vector<int> q = {1, 0};
    path.back().se++;
    FOR(i, 0, sz(path) - 1){
        p.pb(p.back() * path[i].se + p[sz(p) - 2]);
        q.pb(q.back() * path[i].se + q[sz(q) - 2]);
    }
    return {p.back(), q.back()};
}

ii LCA(int p1, int q1, int p2, int q2){
    if (ii(p1, q1) == ii(1, 1) or ii(p2, q2) == ii(1, 1)) {
        return ii(1, 1);
    }

    vector<pair<char, int>> path1 = ENCODE_PATH(p1, q1, false);
    vector<pair<char, int>> path2 = ENCODE_PATH(p2, q2, false);

    vector<pair<char, int>> common;
    FOR(i, 0, min(sz(path1), sz(path2)) - 1){
        if (path1[i].se != path2[i].se){
            common.pb({path1[i].fi, min(path1[i].se, path2[i].se)});
            break;
        }
        else common.pb({path1[i].fi, path1[i].se});
    }

    ii frac = DECODE_PATH(sz(common), common);
    return frac;
}

ii ANCESTOR(int k, int p, int q){
    if (p == 1 and q == 1){
        return {-1, -1};
    }
    vector<pair<char, int>> path = ENCODE_PATH(p, q);

    vector<pair<char,int>> apcs;

    int depth = 0, reached = false;
    FOR(i, 0, sz(path) - 1){
        if (depth + path[i].se < k){
            depth += path[i].se;
            apcs.pb(path[i]);
        }
        else{
            apcs.pb({path[i].fi, k - depth});
            reached = true;
            break;
        }
    }

    if (reached) {
        return DECODE_PATH(sz(apcs), apcs);
    }
    else{
        return {-1, -1};
    }

}

pair<ii, ii> RANGE(int p, int q){
    vector<pair<char, int>> path = ENCODE_PATH(p, q);
    int pL = 0, pR = 1;
    int qL = 1, qR = 0;
    FOR(i, 0, sz(path) - 1){
        int c = path[i].se;
        char dir = path[i].fi;
        if (dir == 'R'){
            pL = pL + pR * c;
            qL = qL + qR * c;
        }
        else{
            pR = pR + pL * c;
            qR = qR + qL * c;
        }
    } 
    return {{pL, qL}, {pR, qR}};
}