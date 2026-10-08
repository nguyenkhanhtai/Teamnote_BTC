// Kamil Szymczak
// Model solution
// O(n log n) queries
#include <cassert>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

int get_n() {
    int n; cin >> n;
    return n;
}

// Makes sure that for each pair [a, b] in the result we have a < b.
vector<pair<int, int>> get_shortest_edges(int a, int b, int c) {
    cout << "? " << a << " " << b << " " << c << "\n" << flush;
    int n; cin >> n;
    vector<pair<int, int>> result(n);
    for (auto &[x, y] : result) {
        cin >> x >> y;
        if (x > y)
            swap(x, y);
    }
    return result;
}

void answer(vector<int> &v) {
    cout << "!";
    for (int x : v) {
        cout << " " << x;
    }
    cout << "\n" << flush;
}

auto create_pair(int a, int b) {
    return pair{min(a, b), max(a, b)};
}

auto solve(vector<int> nodes) {
    if (nodes.size() <= 2)
        return nodes;

    vector<int> left;
    vector<int> right;

    while (true) {
        int a = nodes[rand() % nodes.size()];
        int b = nodes[rand() % nodes.size()];
        while (a == b)
            b = nodes[rand() % nodes.size()];
        left = {a};
        right = {b};
        bool ok = true;
        for (int j : nodes) {
            if (j == a || j == b)
                continue;
            auto v = get_shortest_edges(a, b, j);
            if (find(v.begin(), v.end(), create_pair(a, b)) != v.end()) {
                ok = false;
                break;
            }
            if (find(v.begin(), v.end(), create_pair(a, j)) != v.end()) {
                left.push_back(j);
            } else {
                right.push_back(j);
            }
        }
        if (ok)
            break;
    }
    
    auto result_l = solve(left);
    auto result_r = solve(right);

    if (result_r.size() == 1) {
        swap(result_l, result_r);
    }

    if (result_l.size() == 1) {
        if (result_r.size() == 1) {
            result_l.push_back(result_r[0]);
            return result_l;
        }

        auto v = get_shortest_edges(result_l[0], result_r[0], result_r.back());

        if (find(v.begin(), v.end(), create_pair(result_l[0], result_r[0])) != v.end()) {
            reverse(result_r.begin(), result_r.end());
            result_r.push_back(result_l[0]);
        } else {
            result_r.push_back(result_l[0]);
        }
        return result_r;
    }

    for (int i = 0; i < 4; i++) {

        int p = result_l.back();
        int q = result_r[0];
        int r = result_r[1];

        // We check if p and q are neighbours
        // using the fact that q and r are neighbours

        bool ok = true;

        if (i < 3) { 
            // if i == 3, we don't need to check the neighbours since we know
            // this case will work if the previous ones didn't.
            auto v = get_shortest_edges(p, q, r);
            if (find(v.begin(), v.end(), create_pair(p, q)) == v.end()) {
                ok = false;
            }
        }

        if (ok) {
            for (auto x : result_r)
                result_l.push_back(x);
            return result_l;
        }

        if (i & 1)
            reverse(result_l.begin(), result_l.end());
        else 
            reverse(result_r.begin(), result_r.end());
    }
    
    // This point should never be reached.
    return vector<int>{};
}

void solve_n_squared(int n) {

    vector<int> result;
    vector<bool> taken(n, false);
    taken[0] = true;

    for (int j = 1; j < n; j++) {
        // Look for the immediate neighbours of 0.
        bool ok = true;
        for (int k = 1; k < n; k++) {
            if (k == j)
                continue;
            auto v = get_shortest_edges(0, j, k);
            if (find(v.begin(), v.end(), pair{0, j}) == v.end()) {
                // k is closer to 0 than j.
                ok = false;
                break;
            }
        }
        if (ok) {
            // j is a neighbour of 0.
            taken[j] = true;
            result.push_back(j);
            if (result.size() == 1)
                result.push_back(0);
        }
    }

    assert(result.size() == 3);
    // result should be {first_neighbour of 0, 0, second_neighbour of 0}

    while ((int)result.size() < n) {
        int a = result[result.size() - 2];
        int b = result[result.size() - 1];
        for (int j = 0; j < n; j++) {
            // Find the next node on the cycle.
            if (taken[j])
                continue;
            auto v = get_shortest_edges(a, b, j);
            if (v.size() == 2) {
                taken[j] = true;
                result.push_back(j);
                break;
            }
        }
    }

    answer(result);

}

void test_case() {
    int n = get_n();

    if (n <= 10) {
        solve_n_squared(n);
        return;
    }
    
    int a, b;
    vector<int> div_l;
    vector<int> div_r;
    while (true) {
        a = rand() % n;
        b = rand() % n;
        if (a == b)
            continue;

        div_l = {a};
        div_r = {b};

        bool ok = true;
        
        for (int j = 0; j < n; j++) {
            if (j == a || j == b)
                continue;
            auto v = get_shortest_edges(a, b, j);
            if (find(v.begin(), v.end(), create_pair(a, b)) != v.end()) {
                ok = false;
                break;
            }

            if (find(v.begin(), v.end(), create_pair(a, j)) != v.end()) {
                div_l.push_back(j);
            } else {
                div_r.push_back(j);
            }
        }

        if (!ok)
            continue;

        int min_size = min((int)div_l.size(), (int)div_r.size());

        if (min_size * 3 >= n) {
            break;
        }


    }

    vector<int> result_l = solve(div_l);
    vector<int> result_r = solve(div_r);

    int p = result_l.back();
    int q = result_r[0];
    int r = result_r[1];

    auto v = get_shortest_edges(p, q, r);

    if (find(v.begin(), v.end(), create_pair(p, q)) == v.end()) {
        // p and q are not neighbours.
        reverse(result_l.begin(), result_l.end());
    }
    
    for (int x : result_r)
        result_l.push_back(x);

    answer(result_l);
}

int main() {
    int t, k; cin >> t >> k;
    while (t--)
        test_case();

}
