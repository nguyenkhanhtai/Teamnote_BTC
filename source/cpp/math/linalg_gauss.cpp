#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto sol = gauss({{1,2,3},{2,1,3}},2,1000000007);
// All arithmetic is modulo a prime mod. Matrix rows contain m coefficients and RHS.
struct LinearSolution {
    int rank; bool consistent; vector<int> particular; vector<vector<int>> nullspace;
};
LinearSolution gauss(vector<vector<int>> a, int m, int mod = 1000000007) {
    assert(m >= 0 && mod > 1); int n = a.size(), r = 0; vector<int> where(m, -1);
    for (auto& row : a) {
        assert((int)row.size() == m + 1); for (int& x : row) { x %= mod; if (x < 0) x += mod; } }
    for (int c = 0; c < m && r < n; ++c) {
        int pivot = r; while (pivot < n && a[pivot][c] == 0) ++pivot; if (pivot == n) continue;
        swap(a[pivot], a[r]); int inv = pow_mod(a[r][c], mod - 2, mod);
        for (int j = c; j <= m; ++j) a[r][j] = mul_mod(a[r][j], inv, mod);
        for (int i = 0; i < n; ++i) if (i != r) {
            int factor = a[i][c]; for (int j = c; j <= m; ++j) {
                a[i][j] -= mul_mod(factor, a[r][j], mod); if (a[i][j] < 0) a[i][j] += mod; } }
        where[c] = r++; }
    LinearSolution out{r, true, vector<int>(m), {}}; for (int i = r; i < n; ++i) if (a[i][m] != 0) {
        out.consistent = false; return out; }
    for (int c = 0; c < m; ++c) {
        if (where[c] != -1) out.particular[c] = a[where[c]][m]; else {
            vector<int> v(m); v[c] = 1; for (int j = 0; j < m; ++j) if (where[j] != -1) {
                int x = a[where[j]][c]; v[j] = x ? mod - x : 0; }
            out.nullspace.push_back(v); } }
    return out; }
// Square matrix; mod must be prime. O(n^3 + n log mod).
int determinant_mod(vector<vector<int>> a, int mod = 1000000007) {
    assert(mod > 1); int n = a.size(), ans = 1; for (auto& row : a) {
        assert((int)row.size() == n); for (int& x : row) { x %= mod; if (x < 0) x += mod; } }
    for (int c = 0; c < n; ++c) {
        int pivot_row = c; while (pivot_row < n && a[pivot_row][c] == 0) ++pivot_row;
        if (pivot_row == n) return 0; if (pivot_row != c) {
            swap(a[pivot_row], a[c]); ans = ans ? mod - ans : 0; }
        int pivot = a[c][c]; ans = mul_mod(ans, pivot, mod); int inv_pivot = pow_mod(pivot, mod - 2, mod);
        for (int i = c + 1; i < n; ++i) {
            int factor = mul_mod(a[i][c], inv_pivot, mod); a[i][c] = 0;
            for (int j = c + 1; j < n; ++j) {
                a[i][j] -= mul_mod(factor, a[c][j], mod); if (a[i][j] < 0) a[i][j] += mod; } } }
    return ans; }
//NOTEBOOK_END
}
