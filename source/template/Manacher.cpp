int countEven(int l, int r){
    if (l&1) l++;
    if (r&1) r--;
    if (l > r) return 0;
    return (r - l + 1) / 2 + 1;
}
vector<int> manacher(string str){

    n = str.size();
    vector<char> temp(2 * n - 1);
    vector<int> f(2 * n - 1), ans(2 * n - 1);

    for(int i = 0; i < 2 * n - 1; i++){
        if(i&1) temp[i] = '.';
        else temp[i] = str[i / 2];
    }
    str.resize(n * 2 - 1);
    FOR(i, 0, 2 * n - 2){
        str[i] = temp[i];
    }

    n = 2 * n - 1;
    int l = 0, r = -1;

    // cout << str << endl;

    for(int i = 0; i < n; i++){
        int j = 0;
        if (i <= r) {
            j = min(f[l + r - i], r - i + 1);
        }
        while(i - j >= 0 and i + j < n and str[i - j] == str[i + j]) j++;
        f[i] = j - 1;

        if (i + f[i] > r){
            r = i + f[i];
            l = i - f[i];
        }
        ans[i] = countEven(i - f[i], i + f[i]);
        // cout << i << ' ' << j << ' ' << ans[i] << endl;
    }
    return ans;
}