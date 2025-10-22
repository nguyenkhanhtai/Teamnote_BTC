const int alphabet = 26;
void buildKMP(string str){
    int len = str.length();
    str = '#' + str + '#';

    FOR(i, 2, len){
        int j = lps[i - 1];
        while(j > 0 and str[j + 1] != str[i]) j = lps[j];

        if (str[j + 1] == str[i]) lps[i] = j + 1;
    }

    FOR(i, 0, len){
        FOR(c, 0, alphabet - 1){
            if (anti[i + 1] - '0' == c) automata[i][c] = i + 1;
            else automata[i][c] = automata[lps[i]][c];
        }
    }
}