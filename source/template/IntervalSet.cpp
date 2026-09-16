struct Node {
    int l, r; char c;
    bool operator<(const Node& o) const { return l < o.l; }
};
struct IntervalSet : set<Node> {
    bool can_merge(char a, char b) const { return a == b; }

    auto assign(int l, int r, char c) {
        vector<Node> rem, add;

        // 1. Find first interval intersecting with [l, r]
        auto it = upper_bound({l, (int)2e9, 0});
        if (it != begin() && prev(it)->r >= l) --it;

        // 2. Erase intersecting intervals & preserve leftovers at both ends
        while (it != end() && it->l <= r) {
            auto [L, R, C] = *it;
            rem.push_back(*it);
            it = erase(it);
            if (L < l) add.push_back(*insert({L, l - 1, C}).first);
            if (R > r) add.push_back(*insert({r + 1, R, C}).first);
        }

        // 3. Merge with neighbors if can_merge holds
        it = lower_bound({l, 0, 0});
        if (it != begin() && prev(it)->r == l - 1 && can_merge(prev(it)->c, c)) {
            l = prev(it)->l; rem.push_back(*prev(it)); erase(prev(it));
        }
        if (it != end() && it->l == r + 1 && can_merge(it->c, c)) {
            r = it->r; rem.push_back(*it); erase(it);
        }

        // 4. Insert new interval
        add.push_back(*insert({l, r, c}).first);
        return pair{rem, add};
    }
};