#include <bits/stdc++.h>
using namespace std;

struct Occurrences {
    vector<int> prev, next;
    int maxGap = 1;

    explicit Occurrences(int n) : prev(n + 1), next(n + 1) {
        for (int i = 0; i <= n; ++i) {
            prev[i] = i - 1;
            next[i] = i + 1;
        }
    }

    bool alive(int p) const { return next[p] != -1; }

    void erase(int p) {
        int a = prev[p], b = next[p];
        // Position 0 always matches the prefix we are constructing.
        assert(a >= 0);
        next[a] = b;
        prev[b] = a;
        next[p] = -1;
        maxGap = max(maxGap, b - a);
    }
};

struct Solver {
    string text, pattern, answer;
    int n;
    vector<int> pref;
    vector<int> nextEvent;
    vector<int> nextLength;
    vector<vector<int>> expires;

    static bool compatible(char a, char b) {
        return a == '*' || b == '*' || a == b;
    }

    void search(int pos, Occurrences& occ) {
        while (pos < n / 2 && pos + 1 < int(answer.size())) {
            // Extending a stamp only removes occurrences, so maxGap
            // cannot decrease. No descendant can cover with a shorter
            // length than this gap.
            if (nextLength[max(pos + 1, occ.maxGap)] >
                min(n / 2, int(answer.size()) - 1))
                break;
            if (text[pos] == '*') {
                for (char color : string("RGB")) {
                    Occurrences child = occ;
                    for (int p = child.next[0]; p < n;) {
                        int following = child.next[p];
                        if (p + pos >= n ||
                            !compatible(color, text[p + pos]))
                            child.erase(p);
                        p = following;
                    }
                    pattern[pos] = color;
                    if (child.maxGap <= pos + 1)
                        answer = pattern.substr(0, pos + 1);
                    else
                        search(pos + 1, child);
                    if (int(answer.size()) <= pos + 1) break;
                }
                return;
            }

            // These starts first conflict with the original prefix here,
            // or their occurrence would extend beyond the text.
            for (int p : expires[pos])
                if (occ.alive(p)) occ.erase(p);
            if (nextLength[max(pos + 1, occ.maxGap)] >
                min(n / 2, int(answer.size()) - 1))
                break;
            if (occ.maxGap <= pos + 1) {
                answer = pattern.substr(0, pos + 1);
                break;
            }
            // Until the next event, occurrences do not change. Jump to
            // the first length that could cover, or to that event.
            pos = min(nextEvent[pos + 1],
                      nextLength[max(pos + 2, occ.maxGap)] - 1);
        }
    }

    string solve(string input) {
        text = move(input);
        n = int(text.size());
        int half = n / 2;
        bool reversed = count(text.begin(), text.begin() + half, '*') >
                        count(text.end() - half, text.end(), '*');
        if (reversed) reverse(text.begin(), text.end());

        pref.assign(n, 0);
        expires.assign(n + 1, {});
        for (int p = 0; p < n; ++p) {
            while (p + pref[p] < n &&
                   compatible(text[pref[p]], text[p + pref[p]]))
                ++pref[p];
            expires[pref[p]].push_back(p);
        }
        nextEvent.assign(n + 1, n);
        for (int i = n - 1; i >= 0; --i)
            nextEvent[i] = text[i] == '*' || !expires[i].empty()
                         ? i : nextEvent[i + 1];
        // Every possible answer must match both ends of the paper.
        nextLength.assign(n + 2, n + 1);
        for (int length = n; length >= 1; --length)
            nextLength[length] = pref[n - length] >= length
                               ? length : nextLength[length + 1];

        // Long stamps: the first and last occurrences cover everything.
        int length = (n + 1) / 2;
        while (pref[n - length] < length) ++length;
        answer.resize(length);
        for (int j = 0; j < length; ++j) {
            char a = text[j], b = text[n - length + j];
            answer[j] = a != '*' ? a : (b != '*' ? b : 'R');
        }

        Occurrences occ(n);
        for (int p : expires[0]) occ.erase(p);
        pattern = text;
        search(0, occ);
        if (reversed) reverse(answer.begin(), answer.end());
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        string text;
        cin >> text;
        cout << Solver().solve(text) << '\n';
    }
}
